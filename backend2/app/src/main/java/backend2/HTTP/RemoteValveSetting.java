package backend2.HTTP;

public class RemoteValveSetting {

    private final int percentage;
    private final long time;

    
    public RemoteValveSetting(int percentage, long time) {
        this.percentage = percentage;
        this.time = time;
    }


    public int getPercentage() {
        return percentage;
    }


    public long getTime() {
        return time;
    }



    
}
