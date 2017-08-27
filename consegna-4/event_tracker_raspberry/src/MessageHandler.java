
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.HttpClientBuilder;

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
					
					post(msg);
					
					System.out.println(msg);
				}
			} catch (InterruptedException e) {
				
			}
		}
	}
	
	private void post(String msg) {
	

		HttpClient httpClient = HttpClientBuilder.create().build(); //Use this instead 
		
		try {
		
		    HttpPost request = new HttpPost("http://localhost:3000/messages");
		    StringEntity params =new StringEntity("details={\"time\":\"1503842245\",\"temperature\":\"31.0\",\"presence\":\"false\",\"alarm\":\"false\"} ");
		    request.addHeader("content-type", "application/json");
		    request.setEntity(params);
		    
		    HttpResponse response = httpClient.execute(request);
		    System.out.println(response);
		
		}catch (Exception ex) {
		
		    //handle exception here
		
		} finally {
		    //Deprecated
		    //httpClient.getConnectionManager().shutdown(); 
		}
		
	}
}
