/*
 * This file was generated by the Gradle 'init' task.
 *
 * This generated file contains a sample Java application project to get you started.
 * For more details take a look at the 'Building Java & JVM projects' chapter in the Gradle
 * User Manual available at https://docs.gradle.org/8.0.2/userguide/building_java_projects.html
 */

plugins {
    
    // Apply the java plugin to add support for Java
    java

    // Apply the application plugin to add support for building a CLI application
    // You can run your app via task "run": ./gradlew run
    application

    // /*
    //  * Adds tasks to export a runnable jar.
    //  * In order to create it, launch the "shadowJar" task.
    //  * The runnable jar will be found in build/libs/projectname-all.jar
    //  */
    // id("com.github.johnrengelman.shadow") version "7.1.2"
    // id("org.danilopianini.gradle-java-qa") version "0.43.0"

    //id("org.openjfx.javafxplugin") version "0.0.13"
    //id("org.beryx.jlink") version "2.24.1"

    ////////////////////// PPPPPPPPPPP
    // // Apply the application plugin to add support for building a CLI application in Java.
    // application
}

repositories {
    // Use Maven Central for resolving dependencies.
    mavenCentral()
}

dependencies {
    
    implementation("io.vertx:vertx-core:4.3.1")   
    implementation("io.vertx:vertx-web:4.3.1")
    implementation("io.vertx:vertx-web-client:4.3.1")
    implementation("io.vertx:vertx-mqtt:4.3.1")

    /* for logging */
    implementation("org.slf4j:slf4j-api:1.7.25")
    implementation("org.slf4j:slf4j-jdk14:1.7.36")

    // Use JUnit Jupiter for testing.
    testImplementation("org.junit.jupiter:junit-jupiter:5.9.3")

    testRuntimeOnly("org.junit.platform:junit-platform-launcher")

    // This dependency is used by the application.
    implementation("com.google.guava:guava:32.1.1-jre")

    implementation(files("lib/jssc-2.9.5.jar"))

}

application {
    // Define the main class for the application.
    mainClass.set("backend2.App")
    //mainClass.set("backend2.MQTT.TestMQTTClient")
    
    //mainClass.set("backend2.HTTP.VertxHTTPServerExample")
    //mainClass.set("backend2.HTTP.TestClient")
    // mainClass.set("backend2.HTTP.RunService")
    
}

tasks.named<Test>("test") {
    // Use JUnit Platform for unit tests.
    useJUnitPlatform()
}
