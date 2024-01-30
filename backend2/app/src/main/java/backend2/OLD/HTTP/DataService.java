package backend2.OLD.HTTP;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.core.http.HttpClientRequest;
import io.vertx.core.http.HttpServerRequest;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.RequestBody;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.CorsHandler;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

/*
 * Data Service as a vertx event-loop 
 */
public class DataService extends AbstractVerticle {

	private int port;
	private static final int MAX_SIZE = 10;
	public static final String Thread = null;
	private LinkedList<DataPoint> values;
	
	public DataService(int port) {
		values = new LinkedList<>();		
		this.port = port;
	}

	@Override
	public void start() {		
		Router router = Router.router(vertx);
		

		router.route().handler(CorsHandler.create("*")
			.allowedMethod(io.vertx.core.http.HttpMethod.GET)
			.allowedMethod(io.vertx.core.http.HttpMethod.POST)
			.allowedMethod(io.vertx.core.http.HttpMethod.OPTIONS)
			.allowedHeader("Access-Control-Request-Method")
			.allowedHeader("Access-Control-Allow-Credentials")
			.allowedHeader("Access-Control-Allow-Origin")
			.allowedHeader("Access-Control-Allow-Headers")
			.allowedHeader("Content-Type"));
		
		
		router.route().handler(BodyHandler.create());
		
		router.post("/api/data").handler(this::handleAddNewData);
		router.get("/api/data").handler(this::handleGetData);		
		vertx
			.createHttpServer()
			.requestHandler(router)
			.listen(port);

		log("Service ready on port: " + port);
		
	}
	
	private void handleAddNewData(RoutingContext routingContext) {
		
		
		//System.out.println(routingContext.response().body().asJsonObject());
		HttpServerResponse response = routingContext.response();
		// log("new msg "+routingContext.getBodyAsString());
		
		JsonObject res = routingContext.getBodyAsJson();
		//RequestBody tmpres = routingContext.body();
		//JsonObject res = tmpres.asJsonObject();
		
		if (res == null) {
			
			sendError(400, response);
		} else {
			System.out.println(res);
			
			long time = System.currentTimeMillis();
			System.out.println("AAA");
			System.out.println(" / "+ time);
			
			String place = res.getString("place");
			System.out.println("AAA");
			System.out.println(" / " + place + " / "+ time);

			double value;
			try{	
				String tmp = res.getString("value");
				value = Double.parseDouble(tmp);
			} catch (Exception e){
				value = 99999.99999999;
			}
			
			System.out.println("AAA");
			System.out.println(value + " / " + place + " / "+ time);
			
			

			values.addFirst(new DataPoint(value, time, place));
			if (values.size() > MAX_SIZE) {
				values.removeLast();
			}
			
			log("New value: " + value + " from " + place + " on " + new Date(time));
			response.setStatusCode(200).end();
		}

		// System.out.println("CIAO");
		
		// HttpServerRequest request = routingContext.request();
		// if (request == null ){
		// 	System.out.println("AHIA");
		// }
		// String tmp = "NO";
		// if(request.body().isComplete()){
		// 	tmp = request.body().result().toString();
		// }
		// System.out.println(tmp);
		

		// HttpServerRequest request = routingContext.request();
		// // log("new msg "+routingContext.getBodyAsString());
		// //JsonObject res = routingContext.getBodyAsJson();
		// RequestBody tmpres = routingContext.body();
		// JsonObject res = tmpres.asJsonObject();
		// if (res == null) {
		// 	//sendError(400, response);
		// 	request.
		// 	response.setStatusCode(400).end();
		// } else {
		// 	float value = res.getFloat("value");
		// 	String place = res.getString("place");
		// 	long time = System.currentTimeMillis();
			
		// 	values.addFirst(new DataPoint(value, time, place));
		// 	if (values.size() > MAX_SIZE) {
		// 		values.removeLast();
		// 	}
			
		// 	log("New value: " + value + " from " + place + " on " + new Date(time));
		// 	response.setStatusCode(200).end();
		// }
	}
	
	private void handleGetData(RoutingContext routingContext) {
		JsonArray arr = new JsonArray();
		for (DataPoint p: values) {
			JsonObject data = new JsonObject();
			data.put("time", p.getTime());
			data.put("value", p.getValue());
			data.put("place", p.getPlace());
			arr.add(data);
		}
		routingContext.response()
			.putHeader("content-type", "application/json")
			.end(arr.encodePrettily());
		//System.out.println(routingContext.);
	}
	
	private void sendError(int statusCode, HttpServerResponse response) {
		response.setStatusCode(statusCode).end();
	}

	private void log(String msg) {
		System.out.println("[DATA SERVICE] "+msg);
	}

}