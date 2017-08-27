
import java.util.Calendar;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.HttpClientBuilder;

import com.google.gson.Gson;

public class MessageHandler extends Thread {
	SerialCommChannel channel;
	
	public MessageHandler(SerialCommChannel channel){
		this.channel=channel;
	}
	
	public void run(){
		
		while(true){		

			
			String msg;
			try {
				if(channel.isMsgAvailable()){
					
					msg = channel.receiveMsg();
					
					System.out.println(msg);
					
					Gson gson = new Gson();
					
					Message message = gson.fromJson(msg, Message.class);
					
					Calendar cal = Calendar.getInstance();
					message.setTime(cal.getTime().toString());
					
					post(gson.toJson(message));
					
				}
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	private void post(String message) {
	

		HttpClient httpClient = HttpClientBuilder.create().build();
		
		try {
		
		    HttpPost request = new HttpPost("http://localhost:3000/messages");
		    StringEntity params =new StringEntity("details=" + message);
		    request.addHeader("content-type", "application/json");
		    request.setEntity(params);
		    
		    HttpResponse response = httpClient.execute(request);
		    System.out.println(response);
		
		} catch (Exception ex) {
		
		    ex.printStackTrace();
		
		}
		
	}
}
