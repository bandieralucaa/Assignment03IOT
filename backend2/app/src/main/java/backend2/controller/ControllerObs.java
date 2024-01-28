package backend2.controller;

public interface ControllerObs {
    void setSample(double newSample);

    void setNewValveOpMan(int newPerc);
    void setSpeedUploadingInfo(int newSpeed);

    void setActValveOp(int actPerc);

    void setNewValveType(ValveType newType);

}
