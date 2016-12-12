package com.example.giulia.smartcar_consegna3;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.util.ArrayList;

/**
 * Created by Giulia on 11/12/2016.
 */

public class BluetoothFragment extends Fragment{
    /** List view Elements */
    private ArrayList<String> array = new ArrayList<>();
    private ArrayAdapter<String> adapter;
    private ListView devicesList;
    private View myInflatedView;

     /** Tramite l'istanza del BluetoothAdapter è possibile avviare ed interrompere la procedura di discovery di altri dispositivi
     nel raggio di visibilità. STARTDISCOVERY() -- CANCELDISCOVERY e memorizzarli in un set di BluetoothDevice
     */
    private BluetoothAdapter btAdapter;

    public BluetoothFragment() {
        // Required empty public constructor
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

    }

    @Override
    public void onStart(){
        super.onStart();
        btAdapter.startDiscovery();

    }

    @Override
    public void onStop(){
        super.onStop();
        btAdapter.cancelDiscovery();

    }

    @Override
    public  void  onPause (){
        super.onPause ();
        btAdapter.cancelDiscovery();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        myInflatedView = inflater.inflate(R.layout.fragment_bluetooth, container,false);
        devicesList = (ListView)myInflatedView.findViewById(R.id.devices);

        /**Add the toolbar to the fragment*/
        AppCompatActivity activity = (AppCompatActivity) getActivity();
        Toolbar toolbar = (Toolbar) activity.findViewById(R.id.toolbar);
        activity.setSupportActionBar(toolbar);

        activity.registerReceiver(br, new IntentFilter(BluetoothDevice.
                ACTION_FOUND));

        /** Bluetooth */
        btAdapter = BluetoothAdapter.getDefaultAdapter ();
        btAdapter.startDiscovery();

        return myInflatedView;

    }

    /**
     Per poter ricevere le informazioni dei dispositivi identificati è
     necessario registrare un B33roadcastReceiver abilitato ad intercettare
     ogni IntentFilter di tipo BluetoothDevice.ACTION_FOUND
    */
    private BroadcastReceiver br = new  BroadcastReceiver(){

        /**
        Il device identificato è passato mediante un Intent, dal quale
        è possibile recuperare l'istanza del device mediante la funzione getParcelableExtra()
        con lo specico parametro
        */

        @Override
        public  void  onReceive(Context context , Intent intent){
            refreshBluetooth(intent);

        }
    };

    private void refreshBluetooth(Intent intent){
        BluetoothDevice  device = null;
        if(BluetoothDevice.ACTION_FOUND.equals(intent.getAction ())) {

            device = intent.getParcelableExtra(BluetoothDevice.
                    EXTRA_DEVICE);
            array.add(device.getName());

        }
        adapter=new ArrayAdapter<>(getActivity(), R.layout.row, R.id.textViewList, array);
        devicesList.setAdapter(adapter);
    }
}
