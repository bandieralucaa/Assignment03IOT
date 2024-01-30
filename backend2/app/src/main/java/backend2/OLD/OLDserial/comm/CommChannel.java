package backend2.OLD.OLDserial.comm;

/**
 * Questa interfaccia è stata presa dal codice visto a lezione e fornita dal prof. Ricci.
 * 
 * Simple interface for an async msg communication channel
 * @author aricci
 *
 */
public interface CommChannel {
	
	/**
	 * Send a message represented by a string (without new line).
	 * 
	 * Asynchronous model.
	 * 
	 * @param msg
	 */
	void sendMsg(String msg);
	
	/**
	 * To receive a message. 
	 * 
	 * Blocking behaviour.
	 */
	String receiveMsg() throws InterruptedException;

	/**
	 * To check if a message is available.
	 * 
	 * @return
	 */
	boolean isMsgAvailable();

}
