public class SmartToiletDisplay extends Thread {
	
	public static void main(String[] args) throws Exception {

		SerialCommChannel channel = SerialCommChannel.getInstance(args[0], 9600);
		
		System.out.println("Waiting Arduino for rebooting...");
		Thread.sleep(4000);
		System.out.println("Ready.");
		
		CleaningIntrusion cleaning = new CleaningIntrusion(channel);
		cleaning.start();
		
		InfoRequest info = new InfoRequest(channel);
		info.start();
	}
}
