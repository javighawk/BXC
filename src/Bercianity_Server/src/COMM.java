import java.io.*;
import java.net.*;

public class COMM{
	
	/* COMM packages */
	public final static short EOT 				= 0x04;
	public final static short ENDOFTM 			= 0x05;
	public final static short TELEMETRY 		= 0x0E;
	public final static short TM_PETITION		= 0x0F;
	public final static short ESC 				= 0x7E;
	public final static short TM_CONFIRMATION	= 0x80;
	public final static short ENDOFPCK 			= 0x88;
	
	/* Mode identifiers */
	public final static short MODE_MASK 		= 0x0C;
	public final static short MOVE_MODE 		= 0x00;
	public final static short SPIN_MODE 		= 0x0C;
	public final static short TEXT_MODE 		= 0x04;
	public final static short COMMAND_MODE 		= 0x08;
		
	/* Movement/Spin mode identifiers */
	public final static short DIRECTION_MASK	= 0x30;
	public final static short DIR_UP 			= 0x00;
	public final static short DIR_DOWN 			= 0x10;
	public final static short DIR_LEFT 			= 0x20;
	public final static short DIR_RIGHT 		= 0x30;
	public final static short SPIN_U_L 			= 0x00;
	public final static short SPIN_U_R 			= 0x10;
	public final static short SPIN_D_L 			= 0x20;
	public final static short SPIN_D_R 			= 0x30;
	
	/* Movement speed identifiers */
	public final static short SPEED_MASK 		= 0x03;
	public final static short SPEED_NOCHANGE 	= 0x00;
	public final static short SPEED_NEWSPEED 	= 0x01;
	public final static short SPEED_STOP 		= 0x02;

	/* Command identifiers */
	public final static short CMD_TESTMOTORS 	= 0x12;
	
	/* Last speed of the bot */
	private static int lastSpeed = 0;
	
	/* Input and output COMM streams */
	private Writer output = null;
    private Reader input = null;
    
    /* Sockets */
    private ServerSocket serverSocket;
    private Socket clientSocket;
    
    
    /*
     * Constructor
     */
    public COMM(){
    	try {
			MainAction.GUI.setServerIP(InetAddress.getLocalHost());
		} catch (UnknownHostException e) {
			e.printStackTrace();
		}
    }
    
    
    /*
     * Initialize COMM. Open socket and wait for a client connection
     */
    public void initialize(){
    	
    	// Get port number
    	int portNumber = MainAction.GUI.getPort();
        
        try{
        	
        	// Initialize sockets
        	serverSocket = new ServerSocket(portNumber);
            
        	// Wait for an incoming connection
            MainAction.GUI.println("[Server]: Created socket. Waiting for connection...");
            clientSocket = serverSocket.accept();
            
            // Connection received
            MainAction.GUI.println("[Server]: Client connected!");
            MainAction.GUI.setClientIP(clientSocket.getInetAddress());
            
            // Initialize input and output streams
            output = new OutputStreamWriter(clientSocket.getOutputStream(), "ISO-8859-1");                   
            input = new BufferedReader(new InputStreamReader(clientSocket.getInputStream(), "ISO-8859-1"));    
            
        } catch (IOException e) {
        	 MainAction.showError("Exception caught when trying to initialize comm");
        	 e.printStackTrace();
        }
    }
    

    //**************************************************************//
    //********************* MOVEMENT FUNCTIONS *********************//
    //**************************************************************//
    
    
    /*
     * Create the command to move/spin the bot and push it to the output queue
     * 
     * @param mode MOVE_MODE or SPIN_MODE
     * @param dir Movement/Spin mode (DIR_* or SPIN_*)
     */
    public void sendMovement( int mode, int dir ){
    	// Initial assert
    	if( mode == MOVE_MODE ){
	    	if( dir != DIR_UP && 
	    		dir != DIR_DOWN &&
	    		dir != DIR_LEFT && 
	    		dir != DIR_RIGHT
	    		)
	    		return;
    	} else if( mode == SPIN_MODE ){
    		if( dir != SPIN_U_L && 
    	    	dir != SPIN_U_R &&
    	    	dir != SPIN_D_L && 
    	    	dir != SPIN_D_R)
    			return;
    	} else return;
    	
    	// Get speed
    	int newSpeed = MainAction.GUI.getSpeed();
    	
    	// Send data
    	MainAction.OutputCOMMLock.lock();
    	if( newSpeed != lastSpeed ){
    		lastSpeed = newSpeed;
    		MainAction.outputS.push( mode | SPEED_NEWSPEED | dir );
    		MainAction.outputS.push( newSpeed );
    	} else {
    		MainAction.outputS.push( mode | SPEED_NOCHANGE | dir );
    	}
    	MainAction.OutputCOMMLock.unlock();
    }
    
    
    /*
     * Stop all motors using the Move mode
     */
    public void stopMotors(){
    	// Send data
    	MainAction.OutputCOMMLock.lock();
    	MainAction.outputS.push( MOVE_MODE | DIR_UP | SPEED_STOP );	    	
    	MainAction.OutputCOMMLock.unlock();
    	
    	// Update last speed
    	lastSpeed = 0;  	
    }
    
    
    //**************************************************************//
    //********************* COMMAND FUNCTIONS **********************//
    //**************************************************************//
    
    
    /*
     * Sends the Test Motors shortcut command to the bot
     */
    public void sendTestM(){
    	// Send command
		MainAction.OutputCOMMLock.lock();
		MainAction.outputS.push( COMMAND_MODE );
		MainAction.outputS.push( CMD_TESTMOTORS );
    	MainAction.OutputCOMMLock.unlock();	
    }
    
    
    //**************************************************************//
    //*********************** COMM FUNCTIONS ***********************//
    //**************************************************************//
    
    
    /*
     * Sends data to Arduino over TCP
     * 
     * @param data Data to send
     * @throws IOException if communication is cut
     */
    public void sendData(short data) throws IOException{
		output.write(data);
		output.flush();
		MainAction.GUI.printOutputData(data);
    }
    
    
    /*
     * Reads data from Arduino over TCP
     * 
     * @return Data read. -1 if nothing available
     * @throws IOException if communication is cut
     */
    public int readData() throws IOException{
    	short data = -1;
    	data = (short) input.read();			
    	
    	//If received byte is a flag, we have to discard it
    	// and take the following byte
    	if( data == ESC )
			while( (data = (short) input.read()) < 0 );
    	
    	if( data >= 0 ) MainAction.GUI.printInputData(data);
    	return data;
    }      

    
    /*
     * Close streams
     */
    public void closeSockets(){
    	try {
    		serverSocket.close();
    		clientSocket.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
    }    
}