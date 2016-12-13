package com.fusaimoe.smart_car.bt;

import android.bluetooth.BluetoothSocket;
import android.os.Message;
import android.util.Log;

import org.json.JSONObject;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import com.fusaimoe.smart_car.C;
import com.fusaimoe.smart_car.MainActivity;

public class BluetoothConnectionManager extends Thread {
    private BluetoothSocket btSocket;
    private InputStream btInStream;
    private OutputStream btOutStream;

    private volatile boolean stop = true;

    private static BluetoothConnectionManager instance = new BluetoothConnectionManager();

    public static BluetoothConnectionManager getInstance() {
        return instance;
    }

    public void setChannel(BluetoothSocket socket) {
        btSocket = socket;

        try {
            btInStream = socket.getInputStream();
            btOutStream = socket.getOutputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }

        stop = false;
    }

    public void run() {
        while (!stop) {
            try {
                int size = btInStream.read();
                int i = 0;
                StringBuffer buf = new StringBuffer("");

                while (i < size) {
                    int data = btInStream.read();
                    buf.append((char) data);
                    i++;
                }

                Log.d(C.LOG_TAG, "> rec done: " + buf);

                dispatchMsg(buf.toString());
            } catch (Exception e) {
                System.err.println(e.toString());
            }
        }
    }

    public boolean sendMsg(String msg) throws MsgTooBigException {
        if (btOutStream == null)
            return false;

        if (msg.length() > 255) {
            throw new MsgTooBigException();
        }

        char[] array = msg.toCharArray();
        byte[] bytes = new byte[array.length + 1];

        bytes[0] = (byte) msg.length();

        for (int i = 0; i < array.length; i++) {
            bytes[i + 1] = (byte) array[i];
        }

        try {
            btOutStream.write(bytes);
            btOutStream.flush();
        } catch (IOException ex) {
            ex.printStackTrace();
            return false;
        }

        return true;
    }

    public void sendMsg(JSONObject msg) throws MsgTooBigException {
        sendMsg(msg.toString());
    }

    public void cancel() {
        try {
            btSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void dispatchMsg(String msg){
        Message m = new Message();
        m.obj = msg;
        MainActivity.getHandler().sendMessage(m);
    }

    private void dispatchMsg(JSONObject msg){
        Message m = new Message();
        m.obj = msg;
        MainActivity.getHandler().sendMessage(m);
    }
}
