package river.controller;

public enum ValveType {
    
    AUTOMATIC("Automatic"),
    MANUAL("Manual"),
    UNKNOW("Unknow");

    private String byVTtoString;

    private ValveType(String stringVal){
        this.byVTtoString = stringVal;
    }

    public String getStringRapp() {
        return this.byVTtoString;
    }
}
