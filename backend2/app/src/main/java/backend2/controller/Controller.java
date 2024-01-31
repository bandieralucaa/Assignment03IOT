package backend2.controller;


import java.util.List;

import backend2.HTTP.HTTPComponent;
import backend2.HTTP.HTTPComponentImpl;
import backend2.HTTP.RemoteValveSetting;
import backend2.HTTP.Sample;
import backend2.MQTT.MQTTComponent;
import backend2.MQTT.MQTTComponentImpl;
import backend2.serial.main.ServoController;
import io.vertx.core.Vertx;


public class Controller implements ControllerObs {

    private final static boolean CONTROLLER_D = false;
    private final static boolean SHOW = false;

    /**
     * Server constanst: system depend on them
     */
    private final static double D1 = 0.15;
    private final static double D2 = 0.25;
    private final static double D3 = 0.35;
    private final static double D4 = 0.45;
    private final static List<Double> DD = List.of(D1, D2, D3, D4);
    private final static List<Integer> VALVES_OP_STATE = List.of(0, 25, 25, 50, 100);
    private final static int FNormal = 3000;//5000;
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


    public Controller() {
        http = new HTTPComponentImpl(8080, this, vertx);
        http.startComponent();
        mqtt = new MQTTComponentImpl(vertx, this);
        mqtt.startComponent();

        try {
            this.servoController = new ServoController("COM4", 9600, this);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void go(){
        this.keepMeAlive();
    }

    private void keepMeAlive(){
        while (true) {
            this.servoController.exec();

            if(!this.mqtt.isMQTTConnected()){
                this.mqtt.reconnectIfNot();
            }

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
            System.out.println("Receiver new sample: " + newSample);
        }
        http.pushNewSample(new Sample(newSample, System.currentTimeMillis()));
        startDamPolicy(newSample);
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

        if (CONTROLLER_D){
            log("LEVEL: " + actLev);
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
        if (actLev < 0 || actLev > DD.size()){
            return;
        }
        int freqToSet = getActFreqToConsider(actLev);
        actDamState = DamState.values()[actLev];
        http.sendDamState(actDamState.byDSToString(), freqToSet);

        if (CONTROLLER_D) {
            log("POLICY REFRESH: act state -> " + actDamState.byDSToString());
            log("POLICY REFRESH: setted " + freqToSet + " now");
        }
        
        mqtt.sendNewFreq(freqToSet);
        
        log("actState = " + this.valveConfig.getStringRapp());
        if (this.valveConfig == ValveType.AUTOMATIC) {
            this.servoController.moveServo(VALVES_OP_STATE.get(actLev).intValue());
            log("POLICY REFRESH: start moving valve to " + VALVES_OP_STATE.get(actLev).intValue() + " now");
        }
        
    }

    @Override
    public void setNewValveOpMan(RemoteValveSetting newPerc) {
        int tmp = newPerc.getPercentage();
        if (CONTROLLER_D) {
            log("Set valve to: " + tmp + "%");
        }
        this.servoController.moveServo(tmp);
    }


    @Override
    public void setActValveOp(int actPerc) {
        http.pushActValveOp(actPerc);
    }


    @Override
    public void setNewValveType(ValveType newType) {
        this.valveConfig = newType;
        http.pushNewState(newType.getStringRapp());
        if (newType == ValveType.AUTOMATIC ) {
            applyPolicy();
        }
    }

    private void log(String toLog){
        System.out.println("[C] " + toLog);
    }

    
}
