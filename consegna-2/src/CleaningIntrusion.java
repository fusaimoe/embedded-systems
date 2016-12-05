
public class CleaningIntrusion extends Thread {
	SerialCommChannel channel;
	
	public CleaningIntrusion(SerialCommChannel channel){
		this.channel=channel;
	}
	
	public void run(){
		
		while(true){
			String msg;
			try {
				if(channel.isMsgAvailable()){
					msg = channel.receiveMsg();
					System.out.println(msg);
				}
			} catch (InterruptedException e) {
				
			}
		}
	}
}
