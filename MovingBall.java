// Play and Pause Animation for Ball using Lambda

import java.util.concurrent.ThreadLocalRandom;
import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Button; 
import java.awt.event.*;

// Removed "implements Runnable"
public class MovingBall extends Applet {
	
	
	// Size and coordinates of the ball
	private int xPosOfBall; 
	private int yPosOfBall; 
	private int radiusOfBall; 
	
	
	// Ball speed 
	int xSpeedOfBall;
	int ySpeedOfBall;
	
	
	// Ball max speed for random number generator for speed
	int xSpeedOfBall_Max; 
	int ySpeedOfBall_Max;
	
	
	// Buttons
	private Button btnStart;
	private Button btnPause;
	
	
	 // ActionListener interface references to implement actionPerformed() using lambda expression
    /* Don't have to declare a reference; can pass the lambda directly to addActionListener() */
//	ActionListener startButtonListener = (startButtonEvent) -> moveBall();
//	ActionListener stopButtonListener = (stopButtonEvent) -> stopBall();
	
	
	// Thread
	private Thread movingBallThread;
	private boolean stopFlag;
	
	
	public void init() {
		
		
		// The bigger the number you divide by, the faster the ball
		xSpeedOfBall_Max = getWidth() / 20;
		ySpeedOfBall_Max = getHeight() / 20;
		
		
		// public static ThreadLocalRandom current()
		// public int nextInt(int origin,int bound)
		xSpeedOfBall = ThreadLocalRandom.current().nextInt(-xSpeedOfBall_Max, xSpeedOfBall_Max+1); 
		ySpeedOfBall = ThreadLocalRandom.current().nextInt(-ySpeedOfBall_Max, ySpeedOfBall_Max+1);
		
		
		radiusOfBall = Math.min(getWidth(), getHeight()) / 20;
		xPosOfBall = getWidth() / 2;
		yPosOfBall = getHeight() / 2;
		
		
		btnStart = new Button("Start");
		btnPause = new Button("Pause");
		
		
//		btnStart.addActionListener(startButtonListener);
//		btnPause.addActionListener(stopButtonListener);
		
		
		btnStart.addActionListener((startButtonEvent) -> moveBall());
		btnPause.addActionListener((stopButtonEvent) -> stopBall());
		 
		
		add(btnStart);
		add(btnPause);
		
	}	
	
	
	public void moveBall() {
		
		// So pressing start multiple times doesn't speed up the ball
		if (movingBallThread == null || !movingBallThread.isAlive()) {
		
		// Runnable interface reference to implement the run() method using lambda expression
		Runnable movingBallRunnable = () -> {
		
			while (!stopFlag) {
			
				xPosOfBall += xSpeedOfBall;
				yPosOfBall += ySpeedOfBall;
			
				if ((xPosOfBall - radiusOfBall + xSpeedOfBall < 0) || (xPosOfBall + radiusOfBall + xSpeedOfBall > getWidth())) {
					xSpeedOfBall = -xSpeedOfBall; 
				}	
			
				if ((yPosOfBall - radiusOfBall + ySpeedOfBall < 0) || (yPosOfBall + radiusOfBall + ySpeedOfBall > getHeight())) {
					ySpeedOfBall = -ySpeedOfBall; 
				}
			
				repaint();
			
				try {
				
					Thread.sleep(50);
				
				} catch(InterruptedException interruptException) {
			
					interruptException.printStackTrace();
					System.out.println("Thread interrupted during sleep.");
			
				}
			
			}
		
		};
		
		
		movingBallThread = new Thread(movingBallRunnable); // passing the Runnable reference 
		stopFlag = false; 
		movingBallThread.start();
		
		}
	}
	
	
	public void stopBall() {
        stopFlag = true; 
		movingBallThread = null;
    }
	
	
	public void paint(Graphics g) {
		g.setColor(Color.GREEN);
		g.fillOval(xPosOfBall - radiusOfBall, yPosOfBall - radiusOfBall, radiusOfBall * 2, radiusOfBall * 2);
	}
	
	
}




