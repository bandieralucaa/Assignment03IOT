package backend2.serial.main;

import backend2.controller.ControllerObs;
import backend2.controller.ValveType;
import backend2.serial.comm.CommChannel;
import backend2.serial.comm.SerialCommChannel;

public class ServoController {

    private final boolean SERIAL_D = true;

    private CommChannel commChannel;
    private final ControllerObs obs;

    public ServoController(String portName, int baudRate, ControllerObs obs) throws Exception{
        commChannel = new SerialCommChannel(portName, baudRate);
        this.obs = obs;
    }

    public void moveServo(int degrees) {
        String command = "_v:" + degrees;
        if (SERIAL_D) {
            log("MANDO nuova apertura valvola : " + degrees);
        }
        commChannel.sendMsg(command);
    }
   
    public void exec() {
        if (commChannel.isMsgAvailable()){
            String tmp = "";
            try {
                tmp = commChannel.receiveMsg();
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            execCommand(tmp.charAt(1), tmp.split(":")[1]);
            System.out.println(tmp);
        }
    }

    private void execCommand(char command, String value) {

        if(SERIAL_D){
            log("RICEVUTO Comando: " + command + " valore : " + value);
        }

        switch (command) {
            case 'v':
                this.obs.setActValveOp(Integer.parseInt(value));
                break;

            case 's':
                ValveType tmp = ValveType.UNKNOW;
                switch (value.charAt(0)) {
                    case 'A':
                        tmp = ValveType.AUTOMATIC;
                        break;

                    case 'M':
                        tmp = ValveType.MANUAL;
                        break;
                
                    default:
                        break;
                }
                this.obs.setNewValveType(tmp);
                break;
        
            default:
                break;
        }

    }

    private void log(String toLog){
        System.out.println("[SERIAL] " + toLog);
    }
}
 