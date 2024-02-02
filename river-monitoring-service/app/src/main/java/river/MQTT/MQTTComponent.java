package river.MQTT;

public interface MQTTComponent  {
    
    /**
     * start the component
     */
    void startComponent();

    /**
     * reconnect if the connection is lost
     */
    void reconnectIfNot();

    /**
     * send a new frequency
     * @param newFreqMillis
     */
    void sendNewFreq(int newFreqMillis);


    /**
     * check if the MQTT is connected
     * @return
    */
    boolean isMQTTConnected();
}
