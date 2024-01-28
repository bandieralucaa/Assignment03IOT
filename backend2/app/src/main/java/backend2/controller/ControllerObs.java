package backend2.controller;

import backend2.HTTP.RemoteValveSetting;

public interface ControllerObs {
    void setSample(double newSample);
    
    
    void setNewValveOpMan(RemoteValveSetting newPerc);
    //void setSpeedUploadingInfo(int newSpeed);


    void setActValveOp(int actPerc);
    void setNewValveType(ValveType newType);

}
