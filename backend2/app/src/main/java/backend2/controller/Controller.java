package backend2.controller;


import java.io.Serial;
import java.util.List;

import backend2.HTTP.HTTPComponent;
import backend2.HTTP.HTTPComponentImpl;
import backend2.HTTP.RemoteValveSetting;
import backend2.HTTP.Sample;
import backend2.MQTT.MQTTComponent;
import backend2.MQTT.MQTTComponentImpl;
import backend2.serial.main.ServoController;
import io.vertx.core.Vertx;
import io.vertx.mqtt.MqttServer;




public class Controller implements ControllerObs {


    private final static boolean MQTT_D = false;

    private DamState actDamState;
    private ValveType valveConfig;

    private ServoController servoController;

    private Vertx vertx = Vertx.vertx();
    private MQTTComponent mqtt;
    private HTTPComponent http;
    private ServoController serial;


    private final static int FNormal = 2500;//5000;
    private final static int FDanger = 1000;//1000;

    private final static double D1 = 0.15;
    private final static double D2 = 0.25;
    private final static double D3 = 0.35;
    private final static double D4 = 0.45;
    //private final static int AMOUNTD = 4;
    private final static List<Double> DD = List.of(D1, D2, D3, D4);
    private final static List<Integer> VALVES_OP_STATE = List.of(0, 25, 25, 50, 100);
    //private final static List<Double> stateString = ["ALARM-TOO-LOW", "NORMAL STATE", "PRE-ALARM-TOO-HIGH", "ALARM-TOO-HIGH", "ALARM-TOO-HIGT-CRITIC"];





    public Controller() {
        http = new HTTPComponentImpl(8080, this, vertx);
        http.startComponent();
        mqtt = new MQTTComponentImpl(vertx, this);
        mqtt.startComponent();

        
        try {
            serial = new ServoController("COM4", 9600, this);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void go(){
        this.keepMeAlive();
    }

    private void keepMeAlive(){
        // System.out.println("PROV");
        while (true) {
            // System.out.println("PROV2");
            // mqtt.sendNewFreq((int)Math.floor(Math.random()*100));
            // System.out.println("HELO");
            serial.exec();
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }



    @Override
    public void setSample(double newSample) {
        if(MQTT_D){
            System.out.println("Receiver new sample: " + newSample);
        }
        startDamPolicy(newSample);
        http.pushNewSample(new Sample(newSample, System.currentTimeMillis()));
        
    }

    private int actLev = -1; //1 -> to
    private void startDamPolicy(double sampledMeasure) {
        int newLev = 0;
        boolean mustExit = false;
        while(newLev < DD.size() && !(mustExit)) {
            if (newLev != 0) {
                mustExit = (sampledMeasure <= DD.get(newLev));
            } else {
                mustExit = (sampledMeasure < DD.get(newLev));
            }
            if (!mustExit){
                newLev = newLev + 1;
            }
        }

        if (MQTT_D){
            log("LEVEL: " + actLev);
        }

        switchState(newLev);
    }

    private int getActFreqToConsider(int actState){
        if (actState < 2) {
            return FNormal;
        } else {
            return FDanger;
        }
    }

    private void switchState(int newLev) {
        if (actLev != newLev) {
            int freqToSet = getActFreqToConsider(newLev);
            actDamState = DamState.values()[newLev];
            http.sendDamState(actDamState.byDSToString(), freqToSet);

            if (MQTT_D){
                log("POLICY CHANGE: new state -> " + actDamState.byDSToString());
            }
            
            // switch (newLev) {
            //     case 0:
            //         //freqCampionamento = nomale
            //         serial.moveServo(0);
            //         //aperturaValvola = 0
            //         break;
                
            //     case 1:
            //         //freqCampionamento = nomale
            //         serial.moveServo(25);
            //         //aperturaValvola = 25
            //         break;
                
            //     case 2:
            //         //freqCampionamento = danger
            //         serial.moveServo(25);
            //         //aperturaValvola = 25
            //         break;
                
            //     case 3:
            //         //freqCampionamento = danger
            //         serial.moveServo(50);
            //         //aperturaValvola = 50
            //         break;

            //     case 4:
            //         //freqCampionamento = danger
            //         serial.moveServo(100);
            //         //aperturaValvola = 100
            //         break;
            // }
            mqtt.sendNewFreq(freqToSet);
            serial.moveServo(VALVES_OP_STATE.get(newLev));
            //client.publish(publish_topic, freqToSet + "");
            if(MQTT_D){
                log("POLICY CHANGE: setted " + freqToSet + " now");
            }
            actLev = newLev;    
        }
        
    }



    private int lastSendedValveOp = -1;
    @Override
    public void setNewValveOpMan(RemoteValveSetting newPerc) {
        int tmp = newPerc.getPercentage();
        if (tmp != lastSendedValveOp){
            
            System.out.println("Setto la valvola a: " + newPerc.getPercentage());
            
            this.servoController.moveServo(newPerc.getPercentage());
            lastSendedValveOp = tmp;
        }
        
    }




    @Override
    public void setActValveOp(int actPerc) {
        http.pushActValveOp(actPerc);
    }


    @Override
    public void setNewValveType(ValveType newType) {
        this.valveConfig = newType;
        http.pushNewState(newType.getStringRapp());
        //da aggiornare HTTP (?)
    }





    private void log(String toLog){
        System.out.println(toLog);
    }

    
}
