package backend2.MQTT;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.mqtt.MqttClient;
import io.vertx.mqtt.MqttServer;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import backend2.controller.ControllerObs;

public class MQTTComponentImpl extends AbstractVerticle implements MQTTComponent   {

	public final boolean MQTT_D = false;

    //private Vertx vertx;
    private ControllerObs obs;
    private MqttClient myClient;
    private static final String BROKER_ADDRESS = "192.168.43.132";
	private static final String TOPIC_SUB = "river/sample";
    private static final String TOPIC_PUB = "river/freq";
    // private static final String TOPIC_NAME = "esiot-2023";

    public MQTTComponentImpl(Vertx vertx, ControllerObs obs){
        this.vertx = vertx;
        this.obs = obs;
		MqttClient client = MqttClient.create(vertx);
		this.myClient = client;
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

			// client.publish(TOPIC_PUB,
			// 	  Buffer.buffer("hello"), //manda il messaggio hello
			// 	  MqttQoS.AT_LEAST_ONCE,
			// 	  false,
			// 	  false);

            // client.subscribe(TOPIC_NAME, 0, null)
		});
	}
	

	private void log(String msg) {
		System.out.println("[MQTT AGENT] "+msg);
	}


	@Override
	public void reconnectIfNot() {
		if (!this.myClient.isConnected()){
			this.start();
		}
	}


	


	
    



    // private void summonMQTTServer() {

		
	// 	MqttServer mqttServer = MqttServer.create(vertx);
	// 	mqttServer.endpointHandler(endpoint -> {
	
	// 	  // shows main connect info
	// 	  System.out.println("MQTT client [" + endpoint.clientIdentifier() + "] request to connect, clean session = " + endpoint.isCleanSession());
	
	// 	  if (endpoint.auth() != null) {
	// 	    System.out.println("[username = " + endpoint.auth().getUsername() + ", password = " + endpoint.auth().getPassword() + "]");
	// 	  }
	// 	  if (endpoint.will() != null) {
	// 	    System.out.println("[will topic = " + endpoint.will().getWillTopic() + " msg = " + new String(endpoint.will().getWillMessageBytes()) +
	// 	      " QoS = " + endpoint.will().getWillQos() + " isRetain = " + endpoint.will().isWillRetain() + "]");
	// 	  }
	
	// 	  System.out.println("[keep alive timeout = " + endpoint.keepAliveTimeSeconds() + "]");
	
	// 	  // accept connection from the remote client
	// 	  endpoint.accept(false);
	
	// 	})
	// 	  .listen(ar -> {

			
	// 	    if (ar.succeeded()) {
	
	// 	      System.out.println("MQTT server is listening on port " + ar.result().actualPort());
	// 	    } else {
	
	// 	      System.out.println("Error on starting the server");
	// 	      ar.cause().printStackTrace();
	// 	    }
	// 	  });
	// }
}
