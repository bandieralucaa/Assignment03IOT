package backend2.controller;

public enum ValveType {
    
    AUTOMATIC("Automatic"),
    MANUAL("Manual"),
    UNKNOW("Unknow");

    private String byVTtoString;

    private ValveType(String a){
        this.byVTtoString = a;
    }

    public String getStringRapp() {
        return this.byVTtoString;
    }
}
