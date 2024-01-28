package backend2.MQTT;

public interface MQTTComponent  {
    
    void startComponent();
    void reconnectIfNot();

    void sendNewFreq(int newFreqMillis);
}
