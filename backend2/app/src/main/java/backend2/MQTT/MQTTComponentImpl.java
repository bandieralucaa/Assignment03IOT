package backend2.MQTT;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;

import io.vertx.mqtt.MqttClient;

import backend2.controller.ControllerObs;

public class MQTTComponentImpl extends AbstractVerticle implements MQTTComponent   {

	public final boolean MQTT_D = true;

    private ControllerObs obs;
    private MqttClient myClient;
    private static final String BROKER_ADDRESS = "localhost"; // 192.168.43.132
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

			log("connected");
			
			log("subscribing...");
			this.myClient.publishHandler(s -> {
				// System.out.println("There are new message in topic: " + s.topicName());
				// System.out.println("Content(as string) of the message: " + s.payload().toString());
				// System.out.println("QoS: " + s.qosLevel());
				this.obs.setSample(Double.parseDouble(s.payload().toString()));
			})
			.subscribe(TOPIC_SUB, 2);	
		});
	}


    @Override
    public void sendNewFreq(int newFreqMillis) {
		if(this.myClient.isConnected()){
			if(MQTT_D){
				this.log("publishing a msg");
			}
        	this.myClient.publish(TOPIC_PUB,
				  Buffer.buffer(Integer.toString(newFreqMillis)), //manda il messaggio hello
				  MqttQoS.AT_LEAST_ONCE,
				  false,
				  false);
		}
    }

	@Override
	public void reconnectIfNot() {
		if (!this.myClient.isConnected()) {
			log("Retry connection");
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
