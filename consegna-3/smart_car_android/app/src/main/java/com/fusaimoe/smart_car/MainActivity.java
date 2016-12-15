package com.fusaimoe.smart_car;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.DialogFragment;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import com.fusaimoe.smart_car.bt.BluetoothConnectionManager;
import com.fusaimoe.smart_car.bt.BluetoothConnectionTask;
import com.fusaimoe.smart_car.bt.BluetoothUtils;
import com.fusaimoe.smart_car.bt.MsgTooBigException;
import com.fusaimoe.smart_car.email.GMailSender;

import org.json.JSONObject;

import java.lang.ref.WeakReference;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    private BluetoothAdapter btAdapter;
    private BluetoothDevice targetDevice;

    private SensorManager sm;
    private Sensor accelerometer;
    private AccelerometerListener accListener;
    private boolean sensorFlag;

    private String receiverEmail = "giulia.cecchetti96@gmail.com";

    private LocationManager lm;
    private LocationListener locListener;
    private Location lastContactLocation;

    private ToggleButton switchOn, switchPark;
    private TextView movingLabel, distanceLabel;
    private AlertDialog sliderDialog;
    private SeekBar seekBar;

    private static MainActivityHandler uiHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        setContentView(R.layout.activity_main);

        /**Receive new Email if changed*/
        Bundle extras = getIntent().getExtras();
        if(extras != null){
            receiverEmail = (String)extras.get("receiverEmail");
        }

        initSensors();

        initUI();

        uiHandler = new MainActivityHandler(this);
    }

    @Override
    protected void onStart() {
        super.onStart();

        btAdapter = BluetoothAdapter.getDefaultAdapter();

        if(btAdapter != null){
            if(btAdapter.isEnabled()){
                targetDevice = BluetoothUtils.findPairedDevice(C.TARGET_BT_DEVICE_NAME, btAdapter);

                if(targetDevice != null){
                    ((TextView) findViewById(R.id.btFoundFlagLabel)).setText("Target BT Device: Found " + targetDevice.getName());
                    connectToTargetBtDevice();
                }
            } else {
                startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), C.ENABLE_BT_REQUEST);
            }
        } else {
            showBluetoothUnavailableAlert();
        }
    }

    @Override
    protected void onStop() {
        super.onStop();
        if(BluetoothConnectionManager.getInstance().isAlive()){
            BluetoothConnectionManager.getInstance().cancel();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    /**
     * Add settings and maps action buttons to the top bar
     * @return
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu. This adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    /**
     * Add an event to the action bar buttons
     * @param item
     * @return
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch(item.getItemId()) {

            case R.id.settings:
                Intent settingsIntent = new Intent(this, SettingsActivity.class);
                if(receiverEmail!=null){
                    settingsIntent.putExtra("receiverEmail", receiverEmail);
                }
                this.startActivity(settingsIntent);
                return true;

            case R.id.maps:
                Intent mapsIntent = new Intent(this, MapsActivity.class);
                if(lastContactLocation!=null){
                    mapsIntent.putExtra("lastContact", lastContactLocation);
                }
                this.startActivity(mapsIntent);
                return true;

            default:
                return super.onOptionsItemSelected(item);

        }
    }

    @Override
    public void onActivityResult (int reqID , int res , Intent data ){

        if(reqID == C.ENABLE_BT_REQUEST && res == Activity.RESULT_OK){
            targetDevice = BluetoothUtils.findPairedDevice(C.TARGET_BT_DEVICE_NAME, btAdapter);

            if(targetDevice != null){
                ((TextView) findViewById(R.id.btFoundFlagLabel)).setText("Target BT Device: Found " + targetDevice.getName());
                connectToTargetBtDevice();
            }
        }

        if(reqID == C.ENABLE_BT_REQUEST && res == Activity.RESULT_CANCELED ){
            // BT enabling process aborted
        }
    }

    /**
     * Initialize Accelerometer and Locator
     */
    private void initSensors() {
        lm = (LocationManager) getSystemService(Context.LOCATION_SERVICE);

        sm = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        accelerometer = sm.getDefaultSensor(Sensor.TYPE_LINEAR_ACCELERATION);
        if (accelerometer != null) {
            accListener = new AccelerometerListener();
        }
    }

    /**
     * Initialize UI Buttons and Labels
     */
    private void initUI() {

        switchOn = (ToggleButton) findViewById(R.id.onButton);
        switchPark = (ToggleButton) findViewById(R.id.parkButton);
        movingLabel = (TextView) findViewById(R.id.movingLabel);
        distanceLabel = (TextView) findViewById(R.id.movingLabel);

        switchOn.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    if (accelerometer != null) sm.registerListener(accListener, accelerometer, SensorManager.SENSOR_DELAY_NORMAL); //Enable AccListener
                    switchPark.setEnabled(false);
                    movingLabel.setVisibility(View.VISIBLE);
                    distanceLabel.setVisibility(View.VISIBLE);

                    contactWhileOn();

                    setOn(true);
                } else {
                    if (accelerometer != null) sm.unregisterListener(accListener); //Disable AccListener

                    switchPark.setEnabled(true);
                    movingLabel.setVisibility(View.INVISIBLE);
                    distanceLabel.setVisibility(View.INVISIBLE);
                    setOn(false);
                }
            }
        });

        switchPark.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    switchOn.setEnabled(false);
                    setPark(true);
                } else {
                    switchOn.setEnabled(true);
                    setPark(false);
                }
            }
        });


       /* virtualLed = (TextView) findViewById(R.id.virtualLed);
        turnOffVirtualLed();

        Button turnOnButton = (Button) findViewById(R.id.turnOnButton);
        turnOnButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                turnOnArduinoLed();
            }
        });

        Button turnOffButton = (Button) findViewById(R.id.turnOffButton);
        turnOffButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                turnOffArduinoLed();
            }
        });

        Button readTempButton = (Button) findViewById(R.id.readTempButton);
        readTempButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                requestTempValue();
            }
        });

        temperatureLabel = (TextView) findViewById(R.id.tempLabel);
        showTempValue(0);*/
    }

    /**
     * Contact when the car is on
     */
    private void contactWhileOn(){

        // Briefly notify the user with a toast that the contact happened
        Toast.makeText(getApplicationContext(), "Contact! (ON)", Toast.LENGTH_SHORT).show();

        LayoutInflater inflater = this.getLayoutInflater();
        View v = inflater.inflate(R.layout.alert_slider, null);

        sliderDialog = new AlertDialog.Builder(this)
                .setView(v)
                .setTitle("Contact!")
                .setMessage("Spigni")
                .setCancelable(false)
                .create();

        seekBar = (SeekBar)v.findViewById(R.id.slider);
        seekBar.setMax(180);

        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
               @Override
               public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                    if(progress==seekBar.getMax()){
                        sliderDialog.dismiss();
                    }
               }
               @Override
               public void onStartTrackingTouch(SeekBar seekBar) {
               }
               @Override
               public void onStopTrackingTouch(SeekBar seekBar) {
               }
           }
        );

        sliderDialog.create();
        sliderDialog.show();

    }

    /**
     * Contact when the car is off
     */
    private void contactWhileOff(){

        // Briefly notify the user with a toast that the contact happened
        Toast.makeText(getApplicationContext(), "Contact! (OFF)", Toast.LENGTH_SHORT).show();

        // Permission checks for location
        final  int  ACCESS_FINE_LOCATION_REQUEST = 1234;
        int  permission = ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION);
        if (permission  !=  PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{
                    Manifest.permission.ACCESS_FINE_LOCATION
            }, ACCESS_FINE_LOCATION_REQUEST);
        }

        // Get current position using GPS
        lastContactLocation = lm.getLastKnownLocation(LocationManager.GPS_PROVIDER);
        // If GPS isn't returning a position, get current position using Network
        if(lastContactLocation==null){
            lastContactLocation = lm.getLastKnownLocation(LocationManager.NETWORK_PROVIDER);
            if(lastContactLocation==null){
                Toast.makeText(getApplicationContext(), "Your location can't be retrieved!", Toast.LENGTH_SHORT).show();
            }
        }

        // Sending the email notification
        new SendMailTask(MainActivity.this).execute(
                "carcontactemergency@gmail.com",
                "ContactService1",
                receiverEmail,
                "Contatto",
                "Attenzione, la tua macchina ha appena subito un contatto. Verifica dove è avvenuto."
        );

    }

    /**
     * Alert Arduino when the car is on or off
     * @param on
     */
    private void setOn(boolean on) {
        try {
            if(on){
                BluetoothConnectionManager.getInstance().sendMsg("on");

            }else{
                BluetoothConnectionManager.getInstance().sendMsg("off");
            }
        } catch (MsgTooBigException e) {
            e.printStackTrace();
        }
    }

    /**
     * Alert Arduino when the car is parking or notParking
     * @param park
     */
    private void setPark(boolean park) {
        try {
            if(park){
                BluetoothConnectionManager.getInstance().sendMsg("park");

            }else{
                BluetoothConnectionManager.getInstance().sendMsg("notPark");
            }
        } catch (MsgTooBigException e) {
            e.printStackTrace();
        }
    }

    /**
     * Alert Arduino when the car is moving or stopping
     * @param moving
     */
    private void setMoving(boolean moving) {
        try {
            if (moving) {
                BluetoothConnectionManager.getInstance().sendMsg("moving");
                movingLabel.setText("The car is moving");
            } else {
                BluetoothConnectionManager.getInstance().sendMsg("notMoving");
                movingLabel.setText("The car is not moving");


            }
        } catch (MsgTooBigException e) {
            e.printStackTrace();
        }
    }

    /**
     * Alert to show the Bluetooth is unavailable on this device
     */
    private void showBluetoothUnavailableAlert(){
        AlertDialog dialog = new AlertDialog.Builder(this)
            .setTitle(getString(R.string.btUnavailableAlertTitle))
            .setMessage(getString(R.string.btUnavailableAlertMessage))
            .setCancelable(false)
            .setNeutralButton(getString(R.string.btUnavailableAlertBtnText), new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int id) {
                    dialog.dismiss();
                    MainActivity.this.finish();
                }
            })
            .create();

        dialog.show();
    }

    /**
     * Method to connect the Target Bluetooth Device
     */
    private void connectToTargetBtDevice(){
        UUID uuid = UUID.fromString(C.TARGET_BT_DEVICE_UUID);

        BluetoothConnectionTask task = new BluetoothConnectionTask(this, targetDevice, uuid);
        task.execute();
    }

    public static MainActivityHandler getHandler(){
        return uiHandler;
    }

    /**
     * The Handler Associated to the MainActivity Class
     */
    public static class MainActivityHandler extends Handler {
        private final WeakReference<MainActivity> context;

        MainActivityHandler(MainActivity context){
            this.context = new WeakReference<>(context);
        }

        public void handleMessage(Message msg) {

            Object obj = msg.obj;

            if(obj instanceof String){
                String message = obj.toString();

                switch (message){
                    case C.BUTTON_PRESSED_MESSAGE:
                        //context.get().setContactWhileOff();
                        break;

                    case C.BUTTON_RELEASED_MESSAGE:
                        //context.get().turnOffVirtualLed();
                        break;

                    default:
                        /*if(message.contains(C.TEMP_ANSWER_PREFIX)) {
                            context.get().showTempValue(Double.parseDouble(message.replace(C.TEMP_ANSWER_PREFIX, "")));
                        }*/
                        break;
                }
            }

            if(obj instanceof JSONObject){
                //TODO
            }
        }
    }

    /**
     * Accelerometer Listener
     */
    public  class  AccelerometerListener  implements SensorEventListener {
        private  static  final  String  LOG_TAG = "app -tag";

        @Override
        public  void  onSensorChanged(SensorEvent event) {
            boolean otherFlag = false;
            if(!sensorFlag){
                for(float f : event.values){
                    if(f>2){
                        otherFlag=true;
                        setMoving(true);
                        sensorFlag=true;
                    }
                }
                if(otherFlag) {
                    final Handler handler = new Handler();
                    handler.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            sensorFlag = false;

                            setMoving(false);
                        }
                    }, 10000);
                }
            }
        }

        @Override
        public  void  onAccuracyChanged(Sensor  sensor , int  accuracy) {}
    }

    /**
     * Task to send the email
     */
    public class SendMailTask extends AsyncTask {

        private ProgressDialog statusDialog;
        private Activity sendMailActivity;

        public SendMailTask(Activity activity) {
            sendMailActivity = activity;

        }

        protected void onPreExecute() {
            statusDialog = new ProgressDialog(sendMailActivity);
            statusDialog.setMessage("Getting ready...");
            statusDialog.setIndeterminate(false);
            statusDialog.setCancelable(false);
            statusDialog.show();
        }

        @Override
        protected Object doInBackground(Object... args) {
            try {
                Log.i("SendMailTask", "About to instantiate GMail...");
                publishProgress("Processing input....");
                GMailSender androidEmail = new GMailSender(args[0].toString(),
                        args[1].toString(), args[2].toString(), args[3].toString(),
                        args[4].toString());
                publishProgress("Preparing mail message....");
                androidEmail.createEmailMessage();
                publishProgress("Sending email....");
                androidEmail.sendEmail();
                publishProgress("Email Sent.");
                Log.i("SendMailTask", "Mail Sent.");
            } catch (Exception e) {
                publishProgress(e.getMessage());
                Log.e("SendMailTask", e.getMessage(), e);
            }
            return null;
        }

        @Override
        public void onProgressUpdate(Object... values) {statusDialog.setMessage(values[0].toString());}

        @Override
        public void onPostExecute(Object result) {
            statusDialog.dismiss();
        }
    }

    /*
    private void requestTempValue() {
        try {
            BluetoothConnectionManager.getInstance().sendMsg(C.READ_TEMP_MESSAGE);
        } catch (MsgTooBigException e) {
            e.printStackTrace();
        }
    }

    private void showTempValue(double value) {
        temperatureLabel.setText(getString(R.string.tempLabelPrefix) + " " + value);
    }*/

}
