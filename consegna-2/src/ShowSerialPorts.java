import gnu.io.CommPortIdentifier;

import java.util.Enumeration;

/**
 * Show the serial ports available on the PC
 * 
 * @author aricci
 *
 */
public class ShowSerialPorts {

	public static void main(String[] args) throws Exception {

		Enumeration<?> portEnum = CommPortIdentifier.getPortIdentifiers();
		while (portEnum.hasMoreElements()) {
			CommPortIdentifier currPortId = (CommPortIdentifier) portEnum
					.nextElement();
			System.out.println(currPortId.getName());
		}

	}
}