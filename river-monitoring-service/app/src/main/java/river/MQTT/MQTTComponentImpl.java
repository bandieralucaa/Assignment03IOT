package river.MQTT;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;

import io.vertx.mqtt.MqttClient;
import river.controller.ControllerObs;

import java.util.Date;

public class MQTTComponentImpl extends AbstractVerticle implements MQTTComponent   {

	public final boolean MQTT_D = false;
	private final static boolean SHOW = true;

    private ControllerObs obs;
    private MqttClient myClient;
    private static final String BROKER_ADDRESS = "192.168.43.132";//"localhost";
	private static final String TOPIC_SUB = "river/sample";
    private static final String TOPIC_PUB = "river/freq";

    public MQTTComponentImpl(Vertx vertx, ControllerObs obs){
        this.vertx = vertx;
        this.obs = obs;
		MqttClient client = MqttClient.create(vertx);
		this.myClient = client;
    }

	@Override
	public void startComponent() {
		this.start();
	}

	@Override
	public void start() {
		this.myClient.connect(1883, BROKER_ADDRESS, c -> {

			if (MQTT_D || SHOW) {
				log("connecting...");
			}
			
			if (this.myClient.isConnected()) {
				if (MQTT_D || SHOW) {
					log("connected");
				}
				if (MQTT_D) {
					log("subscribing...");
				}
				
				this.myClient.publishHandler(s -> {
					if (this.myClient.isConnected()){
						String tmp = s.payload().toString();
						if (MQTT_D) {
							log("Remote sensor send new sample (" + tmp + ") on " + (new Date(System.currentTimeMillis()).toString()));
						}
						this.obs.setSample(Double.parseDouble(tmp));
					}
				})
				.subscribe(TOPIC_SUB, 2);	
			}
		}).closeHandler(c -> {
			myClient.disconnect();
		});
	}


    @Override
    public void sendNewFreq(int newFreqMillis) {
		if(this.myClient.isConnected()){
			if(MQTT_D){
				this.log("publishing a msg");
			}
        	this.myClient.publish(TOPIC_PUB,
				  Buffer.buffer(Integer.toString(newFreqMillis)),
				  MqttQoS.AT_LEAST_ONCE,
				  false,
				  false);
		}
    }

	@Override
	public void reconnectIfNot() {
		if (!this.myClient.isConnected()) {
			if (MQTT_D){
				log("Retry connection");
			}
			this.start();
		}
	}

	@Override
	public boolean isMQTTConnected() {
		return this.myClient.isConnected();
	}


	private void log(String msg) {
		System.out.println("[MQTT AGENT] "+msg);
	}

	
    
}
