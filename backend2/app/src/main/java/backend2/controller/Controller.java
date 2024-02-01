package backend2.controller;

import java.util.List;

import backend2.HTTP.HTTPComponent;
import backend2.HTTP.HTTPComponentImpl;
import backend2.HTTP.RemoteValveSetting;
import backend2.HTTP.Sample;
import backend2.MQTT.MQTTComponent;
import backend2.MQTT.MQTTComponentImpl;
import backend2.serial.main.ServoController;
import backend2.serial.main.ServoControllerImpl;
import io.vertx.core.Vertx;


public class Controller implements ControllerObs {

    private final static boolean CONTROLLER_D = false;
    private final static boolean SHOW = true;

    /**
     * Server constanst: system depend on them
     */
    private final static double D1 = 0.15;
    private final static double D2 = 0.25;
    private final static double D3 = 0.35;
    private final static double D4 = 0.45;
    private final static List<Double> DD = List.of(D1, D2, D3, D4);
    private final static List<Integer> VALVES_OP_STATE = List.of(0, 25, 25, 50, 100);
    private final static int FNormal = 2500;//5000;
    private final static int FDanger = 1000;//1000;

    /**
     * Little useful enum to storage Dam and Valve state
     */
    private DamState actDamState;
    private ValveType valveConfig = ValveType.UNKNOW;
    private int actLev = -1;

    /**
     * Obj rappresentation of other part of system
     */
    private Vertx vertx = Vertx.vertx();
    private MQTTComponent mqtt;
    private HTTPComponent http;
    private ServoController servoController;

    private boolean waitACK = true;
    private long lastACK = 0;


    public Controller() {
        http = new HTTPComponentImpl(8080, this, vertx);
        http.startComponent();
        mqtt = new MQTTComponentImpl(vertx, this);
        mqtt.startComponent();

        try {
            this.servoController = new ServoControllerImpl("COM4", 9600, this);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void go() {
        this.keepMeAlive();
    }

    private void keepMeAlive(){
        while (true) {
            this.servoController.exec();

            if(!this.mqtt.isMQTTConnected()){
                this.mqtt.reconnectIfNot();
            }

            //////////////////////////////
            // set a default freq to remote sensor if it not setted
            if (waitACK) {
                this.mqtt.sendNewFreq(FDanger);
            }

            if (System.currentTimeMillis() > (lastACK + 2 * FNormal)){
                this.waitACK = true;
            }
            //////////////////////////////

            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }



    @Override
    public void setSample(double newSample) {
        if (CONTROLLER_D) {
            log("Receiver new sample: " + newSample);
        }
        this.http.pushNewSample(new Sample(newSample, System.currentTimeMillis()));
        this.startDamPolicy(newSample);
        this.waitACK = false;
        this.lastACK = System.currentTimeMillis();
        
    }

    
    private void startDamPolicy(double sampledMeasure) {
        int newLev = 0;
        boolean mustExit = false;
        while(newLev < DD.size() && !(mustExit)) {
            if (newLev != 0) { //solo per rispettare strettamente le richieste
                mustExit = (sampledMeasure <= DD.get(newLev));
            } else {
                mustExit = (sampledMeasure < DD.get(newLev));
            }
            if (!mustExit){
                newLev = newLev + 1;
            }
        }

        if (CONTROLLER_D) {
            log("NEW LEVEL STATUS: " + actLev);
        }

        if (actLev != newLev) {
            actLev = newLev;  
            applyPolicy();
        }
    }

    private int getActFreqToConsider(int actState){
        if (actState < 2) {
            return FNormal;
        } else {
            return FDanger;
        }
    }

    private void applyPolicy() {
        if (actLev < 0 || actLev > DD.size()) {
            return;
        }
        int freqToSet = getActFreqToConsider(actLev);
        actDamState = DamState.values()[actLev];
        this.http.sendDamState(actDamState.byDSToString(), freqToSet);

        if (CONTROLLER_D || SHOW) {
            log("");
            log("POLICY REFRESH: act state -> " + this.actDamState.byDSToString());
            log("POLICY REFRESH: setted " + freqToSet + " as new frequence now");
            log("actState = " + this.valveConfig.getStringRapp());
        }
        
        this.mqtt.sendNewFreq(freqToSet);
        
        if (this.valveConfig == ValveType.AUTOMATIC) {
            this.servoController.moveServo(VALVES_OP_STATE.get(actLev).intValue());
            if (CONTROLLER_D || SHOW) {
                log("POLICY REFRESH: start moving valve to " + VALVES_OP_STATE.get(actLev).intValue() + "% now");
            }
        }
        
    }

    @Override
    public void setNewValveOpMan(RemoteValveSetting newPerc) {
        int tmp = newPerc.getPercentage();
        this.servoController.moveServo(tmp);
    }


    @Override
    public void setActValveOp(int actPerc) {
        this.http.pushActValveOp(actPerc);
        if (CONTROLLER_D){
            log("Valve is open to " + actPerc + "% now");
        }
    }


    @Override
    public void setNewValveType(ValveType newType) {
        this.valveConfig = newType;
        this.http.pushNewState(newType.getStringRapp());
        if (newType == ValveType.AUTOMATIC ) {
            applyPolicy();
        }
    }

    private void log(String toLog){
        System.out.println("[C] " + toLog);
    }

    
}
