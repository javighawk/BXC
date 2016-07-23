import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;


public class ArduinoKeyListener implements KeyListener{

    public void keyPressed ( KeyEvent e ){  
    	    	
	  	switch(e.getKeyCode()){
		  		 
	  		/* Left */
	  		case KeyEvent.VK_A:
	  			MainAction.arduino.moveBot(2);
	  			break;
	  			
	  		/* Right */
	  		case KeyEvent.VK_D:
	  			MainAction.arduino.moveBot(3);
	  			break;
	  			
	  		/* Up */
	  		case KeyEvent.VK_W: 
	  			MainAction.arduino.moveBot(0);
	  			break;
	  			
	  		/* Down */
	  		case KeyEvent.VK_S:
	  			MainAction.arduino.moveBot(1);
	  			break;
	  		
	  		/* Up-left */
	  		case KeyEvent.VK_Q:
	  			MainAction.arduino.spinBot(0); 
	  			break;
	  		
	  		/* Up-right */
	  		case KeyEvent.VK_E:
	  			MainAction.arduino.spinBot(1);
	  			break;
	  		
	  		/* Down-left */
	  		case KeyEvent.VK_Z:
	  			MainAction.arduino.spinBot(2);
	  			break;
	  		
	  		/* Down-right */
	  		case KeyEvent.VK_C:
	  			MainAction.arduino.spinBot(3);
	  			break;
	  			
	  		/* Stop motors */
	  		case KeyEvent.VK_SPACE:
	  			MainAction.arduino.stopMotors();
	  			break;	  	
	  	  }
   }  
   
    public void keyReleased ( KeyEvent e ){  
    	
    	/* Stop motors when any key released */
		MainAction.arduino.stopMotors();
    }
    
	@Override
	public void keyTyped(KeyEvent arg0) {}  

}
