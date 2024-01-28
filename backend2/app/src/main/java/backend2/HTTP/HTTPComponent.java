package backend2.HTTP;

import java.util.List;

public interface HTTPComponent {
    
    void sendDamState(String newDamState, int newSuggestFreq);
    void startComponent();

    void pushNewSample(Sample newInfo);

    void pushActValveOp(int actOp);

    // void sendSamples();

}
