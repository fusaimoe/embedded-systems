package com.fusaimoe.event_tracker.devices.p4j_impl;

import com.pi4j.io.gpio.*;

public class GPIOBox  {

	private Pin[] pinsDesc = {
			RaspiPin.GPIO_00,RaspiPin.GPIO_01,RaspiPin.GPIO_02,RaspiPin.GPIO_03,
			RaspiPin.GPIO_04,RaspiPin.GPIO_05,RaspiPin.GPIO_06,RaspiPin.GPIO_07,
			RaspiPin.GPIO_08,RaspiPin.GPIO_09,RaspiPin.GPIO_10,RaspiPin.GPIO_11,
			RaspiPin.GPIO_12,RaspiPin.GPIO_13,RaspiPin.GPIO_14,RaspiPin.GPIO_15,
			RaspiPin.GPIO_16,RaspiPin.GPIO_17,RaspiPin.GPIO_18,RaspiPin.GPIO_19,
			RaspiPin.GPIO_20 };

	private GpioPinDigitalInput[] pins;
	
	
	public GPIOBox(){
	    GpioController gpio = GpioFactory.getInstance();
	    pins = new GpioPinDigitalInput[pinsDesc.length];
		for (int i = 0; i < pinsDesc.length; i++){
			pins[i] = gpio.provisionDigitalInputPin(pinsDesc[i]);
		}
	}
	
	public void printState(){
		for (int i = 0; i < pins.length; i++){
			System.out.print(""+i+":"+pins[i].getState().getValue()+" ");
		}
		System.out.println(".");
	}
}
