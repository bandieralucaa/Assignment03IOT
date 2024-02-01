package backend2.serial.main;

import backend2.controller.ControllerObs;
import backend2.controller.ValveType;
import backend2.serial.comm.CommChannel;
import backend2.serial.comm.SerialCommChannel;
import java.util.Arrays;


public class ServoControllerImpl implements ServoController{

    private final boolean SERIAL_D = false;
    private final static boolean SHOW = false;

    private CommChannel commChannel;
    private final ControllerObs obs;

    public ServoControllerImpl(String portName, int baudRate, ControllerObs obs) throws Exception{
        commChannel = new SerialCommChannel(portName, baudRate);
        this.obs = obs;
    }

    @Override
    public void moveServo(int degrees) {
        String command = "_v:" + degrees;
        if (SERIAL_D) {
            log("MANDO nuova apertura valvola : " + degrees);
        }
        commChannel.sendMsg(command);
    }
   
    @Override
    public void exec() {
        if (commChannel.isMsgAvailable()){
            String tmp = "";
            try {
                tmp = commChannel.receiveMsg();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if (SERIAL_D){
                log("--> " + tmp + "<---");
            }
            
            Arrays.stream(tmp.split("_"))
                .parallel()
                .peek(s -> {
                    if (SERIAL_D) {
                        System.out.println("-> " + s);
                    }
                })
                .filter(s -> !s.isEmpty())
                .forEach(s -> {
                    String[] pairKV = s.split(":");

                    if (pairKV.length == 2){
                        execCommand(pairKV[0].charAt(0), pairKV[1]);
                    }
                    
                });
        }
    }

    private void execCommand(char command, String value) {

        if(SERIAL_D){
            log("RICEVUTO Comando: " + command + " valore : " + value);
        }

        switch (command) {
            case 'v':
                try {
                    int a = Integer.parseInt(value);
                    this.obs.setActValveOp(a);
                } catch (Exception e) {
                }
                
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
 