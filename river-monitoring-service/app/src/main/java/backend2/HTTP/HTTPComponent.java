package backend2.HTTP;

public interface HTTPComponent {
    

    /**
     * send the new dam state
     * @param newDamState
     * @param newSuggestFreq
     */
    void sendDamState(String newDamState, int newSuggestFreq);

    /**
     * start the component
     */
    void startComponent();

    /**
     * set the new sample 
     */
    void pushNewSample(Sample newInfo);


    /**
     * set the new value of valve
     * @param actOp
     */
    void pushActValveOp(int actOp);

    /**
     * set the new type of valve
     *
     * @param newValveTypeConfig
     */
    void pushNewState(String newValveTypeConfig);

}
