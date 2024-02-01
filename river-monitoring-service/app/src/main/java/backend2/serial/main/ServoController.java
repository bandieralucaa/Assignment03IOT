package backend2.serial.main;

public interface ServoController {

    /**
     * move the servo to the specified degrees
     * @param degree
     */
    void moveServo(int degree);

    /**
     * execute the command or the commands received from the serial
     */
    void exec();
    
} 
   

    
   
