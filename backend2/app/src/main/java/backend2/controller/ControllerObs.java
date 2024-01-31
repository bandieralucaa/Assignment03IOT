package backend2.controller;

import backend2.HTTP.RemoteValveSetting;

public interface ControllerObs {

    /**
     * set the new sample value
     */
    void setSample(double newSample);
    
    /**
     * da HTTP a Seriale
     * @param newPerc
     */
    void setNewValveOpMan(RemoteValveSetting newPerc);

    /**
     * da Seriale a HTTP
     * @param newPerc
     */
    void setActValveOp(int actPerc);

    /**
     * set the new type of valve
     */
    void setNewValveType(ValveType newType);

}
