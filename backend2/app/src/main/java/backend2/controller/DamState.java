package backend2.controller;

public enum DamState {
    
    ALARM_TOO_LOW("ALARM-TOO-LOW"),
    NORMAL_STATE("NORMAL STATE"), 
    PRE_ALARM_TOO_HIGH("PRE-ALARM-TOO-HIGH"), 
    ALARM_TOO_HIGH("ALARM-TOO-HIGH"), 
    ALARM_TOO_HIGT_CRITIC("ALARM-TOO-HIGT-CRITIC");
    
    private String toMyStringValue;

    private DamState(String toMyStringValue) {
        this.toMyStringValue = toMyStringValue;
    }

    public String byDSToString() {
        return this.toMyStringValue;
    }
}
