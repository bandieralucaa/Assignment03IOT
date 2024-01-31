package backend2.HTTP;

import java.util.Collections;
import java.util.Date;
import java.util.LinkedList;

import backend2.controller.ControllerObs;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.RequestBody;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.CorsHandler;

public class HTTPComponentImpl extends AbstractVerticle implements HTTPComponent  {

    private final static boolean HTTP_D = true;
    private final static boolean SHOW = false;

	private int port;
	private static final int MAX_SIZE = 100;
	private LinkedList<Sample> values;
    private final ControllerObs obs;


    private String stateStringToSend;
    private int suggestedActFreq;
    
    private int actValveOp;
    private String actValveTypeConfig;
	
	public HTTPComponentImpl(int port, ControllerObs obs, Vertx vertx) {
		values = new LinkedList<>();	
		this.port = port;
        this.obs = obs;
        this.vertx = vertx;
	}

    @Override
    public void startComponent() {
        this.start();
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
		
		router.get("/api/data/samples").handler(this::getSamples);
        router.get("/api/data/damstate").handler(this::getDamState);
        router.get("/api/data/valvetype").handler(this::getValveTypeConfig);
        router.get("/api/data/valveop").handler(this::getActValveOp);	
		router.post("/api/data/valveop").handler(this::postValveOpening);	

		vertx
			.createHttpServer()
			.requestHandler(router)
			.listen(port);
        
        if (HTTP_D){
            log("Service ready on port: " + port);
        }
	
	}

    private void sendToClient(RoutingContext routingContext, String body){
        routingContext.response()
			.putHeader("content-type", "application/json")
			.end(body);
    }

    private void getSamples(RoutingContext routingContext) {
        final JsonArray arr = new JsonArray();
        values.forEach(s -> {
            JsonObject data = new JsonObject();
			data.put("x", s.getMyTime());
			data.put("y", s.getSample());
            arr.add(data);
        });
		sendToClient(routingContext, arr.encodePrettily());
    }

    private void getDamState(RoutingContext routingContext) {
        JsonObject data = new JsonObject();
        data.put("state", stateStringToSend);
        data.put("freq", suggestedActFreq);
        sendToClient(routingContext, data.encodePrettily());
    }

    private void getActValveOp(RoutingContext routingContext) {
        JsonObject data = new JsonObject();
        data.put("percentage", this.actValveOp);
        sendToClient(routingContext, data.encodePrettily());
    }

    private void getValveTypeConfig(RoutingContext routingContext) {
        JsonObject data = new JsonObject();
        data.put("valveState", this.actValveTypeConfig);
        sendToClient(routingContext, data.encodePrettily());
    }

    

    private void postValveOpening(RoutingContext routingContext) {
        HttpServerResponse response = routingContext.response();
		
		RequestBody tmpres = routingContext.body();
		JsonObject res = tmpres.asJsonObject();
		
        RemoteValveSetting tmp;

		if (res == null) {
            response.setStatusCode(400).end();
		} else {
			int newValveOp = res.getInteger("percentage");
            long time = res.getLong("time");
			

			if (HTTP_D) {
                log("New value: " + newValveOp + " on " + new Date(time));
            }

			tmp = new RemoteValveSetting(newValveOp, time);
            obs.setNewValveOpMan(tmp);

			response.setStatusCode(200).end();
		}

    }


    @Override
    public void pushNewSample(Sample newInfo) {
        values.addFirst(Collections.nCopies(1,newInfo).get(0));
        if (values.size() > MAX_SIZE) {
            values.removeLast();
        }
    }


    @Override
    public void sendDamState(String newDamState, int newSuggestFreq) {
        this.stateStringToSend = newDamState;
        this.suggestedActFreq = newSuggestFreq;
    }

    @Override
    public void pushActValveOp(int actOp) {
        this.actValveOp = actOp;
    }

    @Override
    public void pushNewState(String newValveTypeConfig) {
        this.actValveTypeConfig = newValveTypeConfig;
    }


    private void log(String msg) {
		System.out.println("[HTTP SERVICE] " + msg);
	}
    
    
}
