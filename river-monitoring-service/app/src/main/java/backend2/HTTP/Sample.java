package backend2.HTTP;

public class Sample {

    private final double sample;
    private final long myTime;

    public Sample(double sample, long myTime) {
        this.sample = sample;
        this.myTime = myTime;
    }

    public double getSample() {
        return sample;
    }

    public long getMyTime() {
        return myTime;
    }

}
