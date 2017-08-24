package com.fusaimoe.event_tracker;

import android.animation.AnimatorInflater;
import android.animation.AnimatorSet;
import android.app.Activity;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.animation.AccelerateDecelerateInterpolator;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import com.airbnb.lottie.LottieAnimationView;
import com.fusaimoe.event_tracker.bt.BluetoothConnectionManager;
import com.fusaimoe.event_tracker.bt.BluetoothConnectionTask;
import com.fusaimoe.event_tracker.bt.BluetoothUtils;
import com.fusaimoe.event_tracker.bt.MsgTooBigException;

import org.json.JSONObject;

import java.lang.ref.WeakReference;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    private BluetoothAdapter btAdapter;
    private BluetoothDevice targetDevice;

    private AlertDialog presenceDialog;
    private TextView timerLabel;

    private LottieAnimationView whale;
    private View circle;
    private boolean lost=false;

    private static MainActivityHandler uiHandler;

    /**
     * todo
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        setContentView(R.layout.activity_main);

        initUI();

        uiHandler = new MainActivityHandler(this);
    }

    /**
     * todo
     */
    @Override
    protected void onStart() {
        super.onStart();

        btAdapter = BluetoothAdapter.getDefaultAdapter();

        if(btAdapter != null){
            if(btAdapter.isEnabled()){
                targetDevice = BluetoothUtils.findPairedDevice(C.TARGET_BT_DEVICE_NAME, btAdapter);

                if(targetDevice != null){
                    ((TextView) findViewById(R.id.btFoundFlagLabel)).setText(getString(R.string.btDeviceFound) + " " + targetDevice.getName());
                    if(!BluetoothConnectionManager.getInstance().isAlive()) {
                        connectToTargetBtDevice();
                    }
                }
            } else {
                startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), C.ENABLE_BT_REQUEST);
            }
        } else {
            showBluetoothUnavailableAlert();
        }
    }

    /**
     * todo
     */
    @Override
    protected void onStop() {
        super.onStop();
        /*if(BluetoothConnectionManager.getInstance().isAlive()){
            BluetoothConnectionManager.getInstance().cancel();
        }*/
    }

    /**
     * Add an event to the action bar buttons
     * @param item
     * @return
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch(item.getItemId()) {

            default:
                return super.onOptionsItemSelected(item);

        }
    }

    /**
     * todo
     */
    @Override
    public void onActivityResult (int reqID , int res , Intent data ){

        if(reqID == C.ENABLE_BT_REQUEST && res == Activity.RESULT_OK){
            targetDevice = BluetoothUtils.findPairedDevice(C.TARGET_BT_DEVICE_NAME, btAdapter);

            if(targetDevice != null){
                ((TextView) findViewById(R.id.btFoundFlagLabel)).setText(R.string.btDeviceFound + targetDevice.getName());
                connectToTargetBtDevice();
            }
        }

        if(reqID == C.ENABLE_BT_REQUEST && res == Activity.RESULT_CANCELED ){
            // BT enabling process aborted
        }
    }

    // --------------------------- Initializations --------------------------- //

    /**
     * Initialize UI Buttons and Labels
     */
    private void initUI() {

        whale = (LottieAnimationView) findViewById(R.id.animation_view);

        whale.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showPresenceAlert();
            }
        });

        circle = findViewById(R.id.circle_view);
        circle.setVisibility(View.INVISIBLE);

    }

    private void whaleLost(){
        lost=(!lost);
        if(lost){
            whale.setVisibility(View.INVISIBLE);
            circle.setVisibility(View.VISIBLE);
            AnimatorSet set = (AnimatorSet) AnimatorInflater.loadAnimator(this, R.animator.lost);
            set.setTarget(circle);
            set.start();
        } else {
            whale.setVisibility(View.VISIBLE);
            circle.setVisibility(View.INVISIBLE);
        }
    }

    /**
     * Alert Arduino when the car is on or not
     * @param deactivated
     */
    private void deactivateAlarm(boolean deactivated) {
        try {
            if(deactivated){
                BluetoothConnectionManager.getInstance().sendMsg(C.ARDUINO_ALARM_ON);
            }else{
                BluetoothConnectionManager.getInstance().sendMsg(C.ARDUINO_ALARM_NOT_ON);
            }
        } catch (MsgTooBigException e) {
            e.printStackTrace();
        }
    }

    // --------------------------- Bluetooth Methods --------------------------- //

    /**
     * Alert to show the Bluetooth is unavailable on this device
     */
    private void showBluetoothUnavailableAlert(){
        final AlertDialog dialog = new AlertDialog.Builder(this)
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


    // --------------------------- Other Methods --------------------------- //

    /**
     *
     */
    private void showPresenceAlert(){
        LayoutInflater inflater = this.getLayoutInflater();
        View v = inflater.inflate(R.layout.alert_timer, null);

        presenceDialog = new AlertDialog.Builder(this)
                .setView(v)
                .setTitle(R.string.timerAlertTitle)
                .setMessage(R.string.timerAlertMessage)
                .setPositiveButton(R.string.timerAlertButton, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        presenceDialog.dismiss();
                        deactivateAlarm(true);
                    }
                })
                .setCancelable(false)
                .create();

        timerLabel = (TextView)v.findViewById(R.id.timer_label);

        presenceDialog.show();

        CountDownTimer timer = new CountDownTimer(C.TIMER_VALUE, 1000) {

            public void onTick(long millisUntilFinished) {
                timerLabel.setText(Long.toString(millisUntilFinished / 1000));
            }

            public void onFinish() {
                whaleLost();
                deactivateAlarm(false);
                presenceDialog.dismiss();
            }
        };

        timer.start();
    }

    // --------------------------- Inner Classes --------------------------- //

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

                if (message==C.ARDUINO_PRESENCE){
                    context.get().showPresenceAlert();
                }
            }

            if(obj instanceof JSONObject){

            }
        }
    }

    /**
     * Getter for the MainActivityHandler
     */
    public static MainActivityHandler getHandler(){
        return uiHandler;
    }

}
