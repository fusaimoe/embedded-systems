package com.fusaimoe.event_tracker;

import java.util.Calendar;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.HttpClientBuilder;
import org.apache.http.util.EntityUtils;

import com.google.gson.Gson;

public class JSONServer {
	
	private final HttpClient httpClient;
	private static final String URL = "http://localhost:3000/messages";
	
	public JSONServer(){
		httpClient = HttpClientBuilder.create().build();
	}
	
	public void post(ArduinoMessage msg) {
		
		Gson gson = new Gson();
		
		post(gson.toJson(msg));
	}
	
	public void post(String message) {
		
		try {
		
		    HttpPost request = new HttpPost(URL);
		    StringEntity params =new StringEntity(message);
		    request.addHeader("content-type", "application/json");
		    request.setEntity(params);
		    
		    HttpResponse response = httpClient.execute(request);
		    System.out.println(response);
		    
		    EntityUtils.consume(response.getEntity());
		
		} catch (Exception ex) {
		
		    ex.printStackTrace();
		
		}
		
	}

}
