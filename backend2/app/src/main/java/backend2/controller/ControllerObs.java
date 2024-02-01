package backend2.controller;

import backend2.HTTP.RemoteValveSetting;

public interface ControllerObs {

    /**
     * By MQTT to HTTP
     * Redirect new sample obtained to the site
     * @param newSample 
     */
    void setSample(double newSample);
    
    /**
     * By HTTP to HTTP
     * Redirect the request new amount of valve opening that user config using the site to serial component
     * @param newPerc
     */
    void setNewValveOpMan(RemoteValveSetting newPerc);

    /**
     * By Serial To HTTP
     * Redirect actual percentage of valve opening to the site
     * @param newPerc
     */
    void setActValveOp(int actPerc);

    /**
     * By Serial To HTTP
     * Redirect actual type of valve management to the site
     * @param newType
     */
    void setNewValveType(ValveType newType);

}
