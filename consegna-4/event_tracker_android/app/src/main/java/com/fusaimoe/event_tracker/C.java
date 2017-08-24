package com.fusaimoe.event_tracker;

public class C {

    public static final String LOG_TAG = "smart_car_android";

    static final String TARGET_BT_DEVICE_NAME = "HTC One M7";
    static final String TARGET_BT_DEVICE_UUID = "00001101-0000-1000-8000-00805F9B34FB";

    static final String INTENT_EMAIL = "receiverEmail";
    static final String SAVE_EMAIL = "receiverEmail";
    static final String INTENT_MAP = "lastContact";

    static final String CAR_ON = "on";
    static final String CAR_NOT_ON = "notOn";
    static final String CAR_PARK = "park";
    static final String CAR_NOT_PARK = "notPark";
    static final String CAR_MOVING = "moving";
    static final String CAR_NOT_MOVING = "notMoving";

    static final String ARDUINO_PRESENCE = "risk";
    static final String ARDUINO_ALARM_ON = "risk";
    static final String ARDUINO_ALARM_NOT_ON = "risk";

    static final String DISTANCE_PREFIX = "Distance:";
    static final String SLIDER_PREFIX = "Slider:";

    static final int TIMER_VALUE = 10000; //10 seconds, in milliseconds


    static final int ENABLE_BT_REQUEST = 1;

}