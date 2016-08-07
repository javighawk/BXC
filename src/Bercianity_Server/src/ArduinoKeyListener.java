import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;


public class ArduinoKeyListener implements KeyListener{

    public void keyPressed ( KeyEvent e ){  
    	    	
	  	switch(e.getKeyCode()){
		  		 
	  		/* Left */
	  		case KeyEvent.VK_A:
	  			MainAction.arduino.sendMovement(COMM.MOVE_MODE, COMM.DIR_LEFT);
	  			break;
	  			
	  		/* Right */
	  		case KeyEvent.VK_D:
	  			MainAction.arduino.sendMovement(COMM.MOVE_MODE, COMM.DIR_RIGHT);
	  			break;
	  			
	  		/* Up */
	  		case KeyEvent.VK_W: 
	  			MainAction.arduino.sendMovement(COMM.MOVE_MODE, COMM.DIR_UP);
	  			break;
	  			
	  		/* Down */
	  		case KeyEvent.VK_S:
	  			MainAction.arduino.sendMovement(COMM.MOVE_MODE, COMM.DIR_DOWN);
	  			break;
	  		
	  		/* Up-left */
	  		case KeyEvent.VK_Q:
	  			MainAction.arduino.sendMovement(COMM.SPIN_MODE, COMM.SPIN_U_L);
	  			break;
	  		
	  		/* Up-right */
	  		case KeyEvent.VK_E:
	  			MainAction.arduino.sendMovement(COMM.SPIN_MODE, COMM.SPIN_U_R);
	  			break;
	  		
	  		/* Down-left */
	  		case KeyEvent.VK_Z:
	  			MainAction.arduino.sendMovement(COMM.SPIN_MODE, COMM.SPIN_D_L);
	  			break;
	  		
	  		/* Down-right */
	  		case KeyEvent.VK_C:
	  			MainAction.arduino.sendMovement(COMM.SPIN_MODE, COMM.SPIN_D_R);
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
