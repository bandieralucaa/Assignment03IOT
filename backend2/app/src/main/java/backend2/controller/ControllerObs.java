package backend2.controller;

import backend2.HTTP.RemoteValveSetting;

public interface ControllerObs {
    void setSample(double newSample);
    
    /**
     * da HTTP a Seriale
     * @param newPerc
     */
    void setNewValveOpMan(RemoteValveSetting newPerc);
    //void setSpeedUploadingInfo(int newSpeed);


    /**
     * da Seriale a HTTP
     * @param newPerc
     */
    void setActValveOp(int actPerc);
    void setNewValveType(ValveType newType);

}
