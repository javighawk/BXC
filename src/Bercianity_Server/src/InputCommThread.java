import java.io.IOException;

public class InputCommThread extends Thread {
	
	/* Flag to determine thread flow */
	private boolean progress = true;
	
	/* Flag to accept telemetry */
	private boolean acceptTM = false;
	
	
	/* 
	 * @see java.lang.Thread#run()
	 */
	public void run(){
		MainAction.timeOut.timeOut();
		int inputData = 0;
		
		try{
			while(true){
				if(progress){
					// Read incoming data
					if((inputData = MainAction.arduino.readData()) >= 0){
						// Update time out
						MainAction.timeOut.refreshTime();
						
						// Telemetry petition
						if(inputData == Comm.TM_PETITION){						
							MainAction.OutputCOMMLock.lock();
							MainAction.outputS.push(0x80);
							MainAction.OutputCOMMLock.unlock();
							acceptTM = true;
							continue;
						}
						
						// Telemetry data
						if(inputData == Comm.TELEMETRY){
							if( acceptTM ){
								Telemetry.readTelemetry();
								acceptTM = false;
							} else {
								while( inputData != Telemetry.ENDOFTM ){
									inputData = MainAction.arduino.readData();
								}
							}
							continue;
						}
						
						// Unidentified data
						else{
							MainAction.GUI.println("[Server]: Input Data not identified: 0x" + Integer.toHexString(inputData));
						}
					}	
				}
			}
		} catch (IOException e) {
			MainAction.showInputIOException(e);
		}
	}
	
	
	/*
	 * Pause thread
	 */
	public void pause(){
		progress = false;
	}
	
	
	/*
	 * Resume thread
	 */
	public void threadContinue(){
		progress = true;
	}
}