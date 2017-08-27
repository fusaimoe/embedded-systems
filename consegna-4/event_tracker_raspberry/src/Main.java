public class Main extends Thread {
	
	public static void main(String[] args) throws Exception {

		SerialCommChannel channel = SerialCommChannel.getInstance(args[0], 9600);
		
		System.out.println("Waiting Arduino for rebooting...");
		Thread.sleep(4000);
		System.out.println("Ready.");
		
		MessageHandler cleaning = new MessageHandler(channel);
		cleaning.start();
		
	}
}