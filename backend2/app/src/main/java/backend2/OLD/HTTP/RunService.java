package backend2.OLD.HTTP;

import io.vertx.core.Vertx;

/*
 * Data Service as a vertx event-loop 
 */
public class RunService {


	public static void main(String[] args) {
		Vertx vertx = Vertx.vertx();
		DataService service = new DataService(8080);
		vertx.deployVerticle(service);
		// while (true) {
			
		// 	try {
		// 		Thread.sleep(1000);
		// 	} catch (InterruptedException e) {
		// 		// TODO Auto-generated catch block
		// 		e.printStackTrace();
		// 	}
			
		// }
	}
}