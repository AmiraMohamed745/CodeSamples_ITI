// Draw Multiple Lines Applet WITHOUT Point

import java.applet.Applet;
import java.awt.Graphics;
import java.util.Vector;
import java.awt.Color;
import java.awt.event.*;

public class MultipleLinesApplet extends Applet {

	private Vector<Line> linesDrawn = new Vector<Line>();
	private int numberOfLinesDrawn;
	
	private int x_temp_StartPoint;
	private int y_temp_StartPoint;
	private int x_temp_EndPoint;
	private int y_temp_EndPoint;
	
	private boolean isDragEvent = false;
	
	public void init() {
		addMouseListener(new LineHandler());
		addMouseMotionListener(new LineHandler());
	}
	
	public void paint(Graphics g) {
		
		for (int i = 0; i < numberOfLinesDrawn; i++) {
			if (linesDrawn.get(i) != null) {
				g.drawLine(
					linesDrawn.get(i).x_StartPoint,
					linesDrawn.get(i).y_StartPoint,
					linesDrawn.get(i).x_EndPoint,
					linesDrawn.get(i).y_EndPoint
				);
			}	
        }
		
		g.drawLine(
			x_temp_StartPoint,
			y_temp_StartPoint, 
			x_temp_EndPoint, 
			y_temp_EndPoint
		);
		
	}
	
	
	class LineHandler implements MouseListener, MouseMotionListener {
				
		public void mousePressed(MouseEvent mousePressedEvent) {
			
			x_temp_StartPoint = mousePressedEvent.getX();
			y_temp_StartPoint = mousePressedEvent.getY();
			
			x_temp_EndPoint = x_temp_StartPoint;
			y_temp_EndPoint = y_temp_StartPoint;
			
			isDragEvent = false;
		}
		
		public void mouseDragged(MouseEvent mouseDraggedEvent) {
			
			x_temp_EndPoint = mouseDraggedEvent.getX();
			y_temp_EndPoint = mouseDraggedEvent.getY();
			
			isDragEvent = true;
			repaint();
			
		}
		
		public void mouseReleased(MouseEvent mouseReleasedEvent) {
			if (isDragEvent) {
				
				linesDrawn.add(
					new Line(
						x_temp_StartPoint,
						y_temp_StartPoint,
						mouseReleasedEvent.getX(),
						mouseReleasedEvent.getY()
					)
				);
				
				numberOfLinesDrawn = linesDrawn.size(); 
			}
			
			x_temp_StartPoint = y_temp_StartPoint = 
			x_temp_EndPoint = y_temp_EndPoint = 0;
			
			isDragEvent = false;
            repaint();
		}
		
		// Overriding the rest of the methods in Interface MouseListener
		public void mouseClicked(MouseEvent mouseClickedEvent) {}
		public void mouseEntered(MouseEvent mouseEnteredEvent) {}
		public void mouseExited(MouseEvent mouseExitedEvent) {}
		
		// Overriding the rest of the methods in Interface MouseMotionListener
		public void mouseMoved(MouseEvent mouseMovedEvent) {}

	}
	
	// Line Class
	class Line {
		
        int x_StartPoint;
        int y_StartPoint;
        int x_EndPoint;
        int y_EndPoint;
		
		Line (
			int x_StartPoint,
			int y_StartPoint,
			int x_EndPoint,
			int y_EndPoint
		) {
			this.x_StartPoint = x_StartPoint;
			this.y_StartPoint = y_StartPoint;
			this.x_EndPoint = x_EndPoint;
			this.y_EndPoint = y_EndPoint;
		}
	}

}