package backend2.OLD.MQTT;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;

public class OLDTestMQTTClient extends AbstractVerticle {
	
	public static void main(String[] args) throws Exception {		
		Vertx vertx = Vertx.vertx();
		OLDMQTTAgent agent = new OLDMQTTAgent();
		vertx.deployVerticle(agent);
	}
		
}
