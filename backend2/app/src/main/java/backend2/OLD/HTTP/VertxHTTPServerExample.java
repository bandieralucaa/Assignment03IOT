package backend2.OLD.HTTP;

import java.util.HashSet;
import java.util.Set;

import io.netty.handler.codec.http.HttpMethod;
import io.vertx.core.*;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.handler.CorsHandler;

public class VertxHTTPServerExample extends AbstractVerticle {

	@Override
	public void start() throws Exception {

		// final Set<String> allowedHeaders = new HashSet<>();
		// allowedHeaders.add("x-requested-with");
		// allowedHeaders.add("Access-Control-Allow-Origin");
		// allowedHeaders.add("Access-Control-Allow-Methods");
		// allowedHeaders.add("Access-Control-Allow-Headers");
		// allowedHeaders.add("Access-Control-Allow-Credentials");
		// allowedHeaders.add("origin");
		// allowedHeaders.add("Content-Type");
		// allowedHeaders.add("accept");
		// allowedHeaders.add("X-PINGARUNER");
		// allowedHeaders.add("Authorization");

		// final Set<HttpMethod> allowedMethods = new HashSet<>();
		// allowedMethods.add(HttpMethod.GET);
		// allowedMethods.add(HttpMethod.POST);
		// allowedMethods.add(HttpMethod.OPTIONS);
		// allowedMethods.add(HttpMethod.DELETE);
		// allowedMethods.add(HttpMethod.PATCH);
		// allowedMethods.add(HttpMethod.PUT);

		// Create a Router
		Router router = Router.router(vertx);
		//io.vertx.rxjava.ext.web.handler.C
		router.route().handler(CorsHandler.create("*")
			.allowedMethod(io.vertx.core.http.HttpMethod.GET)
			.allowedMethod(io.vertx.core.http.HttpMethod.POST)
			.allowedMethod(io.vertx.core.http.HttpMethod.OPTIONS)
			.allowedHeader("Access-Control-Request-Method")
			.allowedHeader("Access-Control-Allow-Credentials")
			.allowedHeader("Access-Control-Allow-Origin")
			.allowedHeader("Access-Control-Allow-Headers")
			.allowedHeader("Content-Type"));

		// Mount the handler for all incoming requests at every path and HTTP method
		router.route().handler(context -> {
			// Get the address of the request
			String address = context.request().connection().remoteAddress().toString();
			
			// Get the query parameter "name"
			MultiMap queryParams = context.queryParams();
			String name = queryParams.contains("name") ? queryParams.get("name") : "unknown";
			
			
			// Write a json response
			context.json(new JsonObject().put("name", name).put("address", address).put("message",
					"Hello " + name + " connected from " + address));
		});

		// Create the HTTP server
		vertx.createHttpServer()
				// Handle every request using the router
				.requestHandler(router)
				// Start listening
				.listen(8080)
				// Print the port
				.onSuccess(server -> System.out.println("HTTP server started on port " + server.actualPort()));
	}

	public static void main(String[] args) {
		Vertx vertx = Vertx.vertx();
		VertxHTTPServerExample service = new VertxHTTPServerExample();
		vertx.deployVerticle(service);

	}

}