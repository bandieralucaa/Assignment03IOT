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

    // This dependency is used by the application.
    implementation("com.google.guava:guava:32.1.1-jre")

    implementation(files("lib/jssc-2.9.5.jar"))

}

application {
    // Define the main class for the application.
    mainClass.set("backend2.App")
}