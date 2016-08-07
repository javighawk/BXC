import java.io.*;
import java.util.concurrent.Semaphore;


public class Telemetry{
	
	/* Telemetry identifiers */
	public final static byte TEL_SPEED  	  = 0x00;
	public final static int  TEL_TIMES		  = 0x17;
	public final static int  TEL_TIMELABELS   = 0x18;
	public final static byte ENDOFTM		  = 0x05;
	
	/* Time data */
	private static long[] times;
	
	/* Time data labels */
	private static String []labels;

	/* Motors speed data */
	private static short[] mSpeed;

	/* Determines whether we are recording data */
	private static boolean isRecordingData = false;

	/* File descriptors */
	private static File timeData, mSpeedData;
	
	/* File writers */
	private static FileWriter timeWriter, mSpeedWriter;
	
	/* Buffered writers */
	private static BufferedWriter timeBW, mSpeedBW;
	
	/* Semaphore to control the Files access */
	private static Semaphore filesSemaphore = new Semaphore(1);
	
	
	/*
	 * Reads telemetry data and updates the UI
	 */
	public static void readTelemetry() throws IOException{
		
		int inputTelemetry;
		
		// Keep reading until END OF TM flag is received
		while( (inputTelemetry = MainAction.arduino.readData()) != ( Telemetry.ENDOFTM )){
			
			// Record the number of records and size of each for the incoming data
			int nRecs, sizeRecs;
			while((nRecs = MainAction.arduino.readData()) == -1);
			while((sizeRecs = MainAction.arduino.readData()) == -1);

			switch(inputTelemetry){
			
				// Time records
				case TEL_TIMES:
					times = new long[nRecs];
					for( int i=0 ; i<nRecs ; i++ )
						for( int j=0 ; j<sizeRecs ; j++ ){
							while((inputTelemetry = MainAction.arduino.readData()) == -1);
							times[i] = (times[i] << 8) + inputTelemetry;
						}
					MainAction.GUI.setTimeBarValues(times);
					break;	
					
				// Time record labels
				case TEL_TIMELABELS:
					labels = new String[nRecs];
					for( int i=0 ; i<nRecs ; i++ ){
						labels[i] = new String();
						for( int j=0 ; j<sizeRecs ; j++ ){
							while((inputTelemetry = MainAction.arduino.readData()) == -1);
							if( inputTelemetry == 0 ) continue;
							labels[i] = String.valueOf((char)inputTelemetry).concat(labels[i]);
						}
					}
					MainAction.GUI.setTimeLabels(labels);
					break;	
				
				// Speed information
				case TEL_SPEED:
					mSpeed = new short[nRecs];
					for( int i=0 ; i<nRecs ; i++ )
						for( int j=0 ; j<sizeRecs ; j++ ){
							while((inputTelemetry = MainAction.arduino.readData()) == -1);
							mSpeed[i] = (short) ((mSpeed[i] << 8) + inputTelemetry);
						}
					MainAction.GUI.setSpeeds(mSpeed[0], mSpeed[1]);					
					break;

				// Unidentified Telemetry data
				default:
					MainAction.GUI.println("[Server]: Unknown telemetry ID: 0x" + Integer.toHexString(inputTelemetry));
					for( int i=0 ; i<nRecs ; i++ )
						for( int j=0 ; j<sizeRecs ; j++ ){
							while((inputTelemetry = MainAction.arduino.readData()) == -1);
						}
					break;
			}	
		}
		
		// Record data
		if( isRecordingData )
			recordCurrentData();
	}
	
	
	/*
	 * Creates external files to record telemetry data and initializes buffered Writers
	 */
	public static void startRecordingData(){
		
		try{
			
			// Request access
			filesSemaphore.acquire();
		
			// Initialize files
			timeData = new File("timeData.txt");
			mSpeedData = new File("mSpeedData.txt");
			
			// Create files (overwrite if they exist) and folder
			timeData.createNewFile();
			mSpeedData.createNewFile();
			
			// Initialize FileWriters
			timeWriter = new FileWriter(timeData.getAbsoluteFile());
			mSpeedWriter = new FileWriter(mSpeedData.getAbsoluteFile());
			
			// Initialize Buffered writers
			timeBW = new BufferedWriter(timeWriter);
			mSpeedBW = new BufferedWriter(mSpeedWriter);
			
			// Turn flag up
			isRecordingData = true;

			// Release access
			filesSemaphore.release();
		
		} catch (Exception e){
			e.printStackTrace();
		}
	}
	
	
	/*
	 * Records the current Telemetry data
	 */
	private static void recordCurrentData(){
		
		try{
			
			// Request access
			filesSemaphore.acquire();
			
			if( isRecordingData ){
			
				// Write time data
				timeBW.write(Long.toString(times[0]) + "\t");
				timeBW.write(labels[0] + ":" + Long.toString(times[1]) + "\t");
				timeBW.write(labels[1] + ":" + Long.toString(times[2]) + "\t");
				timeBW.write(labels[2] + ":" + Long.toString(times[3]));
				timeBW.newLine();
				
				// Write motors speed data
				mSpeedBW.write(Integer.toString(mSpeed[0]) + "\t");
				mSpeedBW.write(Integer.toString(mSpeed[1]));
				mSpeedBW.newLine();				
			}
			
			// Release access
			filesSemaphore.release();
			
		} catch (Exception e){
			e.printStackTrace();
		}	
	}
	
	
	/*
	 * Closes files and buffered writers
	 */
	public static void stopRecordingData(){
		
		try {
			
			// Request access
			filesSemaphore.acquire();
			
			// Close buffered writers
			timeBW.close();
			mSpeedBW.close();
			
			// Turn flag down
			isRecordingData = false;
			
			// Release access
			filesSemaphore.release();
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	
	/*
	 * Check if telemetry is being recorded
	 * 
	 * @return Whether TM is being recorded
	 */
	public static boolean isRecordingData(){
		return isRecordingData;
	}
}