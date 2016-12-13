package com.fusaimoe.smart_car;

import android.app.Activity;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.graphics.drawable.Drawable;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.annotation.ColorRes;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.graphics.drawable.DrawableCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.fusaimoe.smart_car.bt.BluetoothConnectionManager;
import com.fusaimoe.smart_car.bt.BluetoothConnectionTask;
import com.fusaimoe.smart_car.bt.BluetoothUtils;
import com.fusaimoe.smart_car.bt.MsgTooBigException;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.common.api.GoogleApiClient.ConnectionCallbacks;
import com.google.android.gms.common.api.GoogleApiClient.OnConnectionFailedListener;
import com.google.android.gms.common.api.ResultCallback;
import com.google.android.gms.common.api.Status;
import com.google.android.gms.location.ActivityRecognition;
import com.google.android.gms.location.DetectedActivity;

import org.json.JSONObject;

import java.lang.ref.WeakReference;
import java.util.UUID;

public class MainActivity extends AppCompatActivity implements ConnectionCallbacks, OnConnectionFailedListener, ResultCallback<Status> {

    /**
     * Provides the entry point to Google Play services.
     */
    protected GoogleApiClient mGoogleApiClient;

    private BluetoothAdapter btAdapter;
    private BluetoothDevice targetDevice;

    private SensorManager sm;
    private Sensor accelerometer;
    private AccelerometerListener accListener;


    private ToggleButton switchOn, switchPark;
    private TextView movingLabel;

    private static MainActivityHandler uiHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        setContentView(R.layout.activity_main);

        sm = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        accelerometer = sm.getDefaultSensor(Sensor.TYPE_LINEAR_ACCELERATION);
        if (accelerometer != null){
            accListener = new AccelerometerListener();
        }

        initUI();

        uiHandler = new MainActivityHandler(this);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        MenuItem settingsItem = menu.findItem(R.id.settings);
        MenuItem mapItem = menu.findItem(R.id.collision);

        if (mapItem!=null && settingsItem!=null) {
            tintMenuIcon(MainActivity.this, settingsItem, R.color.white);
            tintMenuIcon(MainActivity.this, mapItem, R.color.white);
        }
        return true;
    }

    //Change color to toolbar icons
    public static void tintMenuIcon(Context context, MenuItem item, @ColorRes int color) {
        Drawable normalDrawable = item.getIcon();
        Drawable wrapDrawable = DrawableCompat.wrap(normalDrawable);
        DrawableCompat.setTint(wrapDrawable, context.getResources().getColor(color));

        item.setIcon(wrapDrawable);
    }

    @Override
    protected void onStart() {
        super.onStart();
        mGoogleApiClient.connect();

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
        mGoogleApiClient.disconnect();

        BluetoothConnectionManager.getInstance().cancel();
    }

    @Override
    protected void onResume() {
        super.onResume();

        if (accelerometer != null){
            sm.registerListener(accListener, accelerometer, SensorManager.SENSOR_DELAY_NORMAL);
        }
    }

    @Override
    public void onConnected(@Nullable Bundle bundle) {

    }

    @Override
    public void onConnectionSuspended(int i) {

    }
    
    @Override
    public void onConnectionFailed(@NonNull ConnectionResult connectionResult) {

    }

    @Override
    public void onResult(@NonNull Status status) {

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
     * Builds a GoogleApiClient. Uses the {@code #addApi} method to request the
     * ActivityRecognition API.
     */
    protected synchronized void buildGoogleApiClient() {
        mGoogleApiClient = new GoogleApiClient.Builder(this)
                .addConnectionCallbacks(this)
                .addOnConnectionFailedListener(this)
                .addApi(ActivityRecognition.API)
                .build();
    }

    private void initUI() {

        switchOn = (ToggleButton) findViewById(R.id.onButton);
        switchPark = (ToggleButton) findViewById(R.id.parkButton);
        movingLabel = (TextView) findViewById(R.id.movingLabel);

        switchOn.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    switchPark.setEnabled(false);
                    setOn(true);
                } else {
                    switchPark.setEnabled(true);
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

    private void setMoving(boolean moving) {
        try {
            if(moving){
                BluetoothConnectionManager.getInstance().sendMsg("moving");
                movingLabel.setText("The car is moving");
            }else{
                BluetoothConnectionManager.getInstance().sendMsg("notMoving");
                movingLabel.setText("The car is not moving");
            }
        } catch (MsgTooBigException e) {
            e.printStackTrace();
        }
    }

    private void requestTempValue() {
        try {
            BluetoothConnectionManager.getInstance().sendMsg(C.READ_TEMP_MESSAGE);
        } catch (MsgTooBigException e) {
            e.printStackTrace();
        }
    }

    /*private void showTempValue(double value) {
        temperatureLabel.setText(getString(R.string.tempLabelPrefix) + " " + value);
    }*/

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
                        //context.get().turnOnVirtualLed();
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

    public  class  AccelerometerListener  implements SensorEventListener {
        private  static  final  String  LOG_TAG = "app -tag";
        @Override
        public  void  onSensorChanged(SensorEvent event) {
            boolean moving = false;
            for(float f : event.values){
                if(f>0.02){
                    moving=true;
                }
            }
            setMoving(moving);
        }
        @Override
        public  void  onAccuracyChanged(Sensor  sensor , int  accuracy) {

        }
    }

}
