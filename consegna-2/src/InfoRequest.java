import java.util.Scanner;

public class InfoRequest extends Thread{
	
	SerialCommChannel channel;
	Scanner keyboard = new Scanner(System.in);

	
	public InfoRequest(SerialCommChannel channel){
		this.channel=channel;
	}
	
	public void run(){
		
		while(true){

			try {
				
				System.out.println("Press S for status or N for total users number, the press Enter");
				
				String input = keyboard.nextLine();
				if(input!=null){
					if("s".equals(input.toLowerCase())){
						channel.sendMsg("status");
						System.out.print("Stato corrente: ");
					}
					if("n".equals(input.toLowerCase())){
						channel.sendMsg("users");
						System.out.print("Totale utenti: ");
					}
				}
				
				Thread.sleep(500);
				
			} catch (Exception e) {
				
			}

		}
	}
}
