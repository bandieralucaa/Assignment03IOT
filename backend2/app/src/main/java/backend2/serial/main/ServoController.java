package backend2.serial.main;

import backend2.serial.comm.CommChannel;
import backend2.serial.comm.SerialCommChannel;

public class ServoController {

    private CommChannel commChannel;

    public ServoController(String portName, int baudRate) throws Exception{
        commChannel = new SerialCommChannel(portName, baudRate);
    }

    public void moveServo(int degrees) {
        String command = "" + degrees;
        commChannel.sendMsg(command);
    } 
   
}
 