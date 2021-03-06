package model;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Shape;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;

public class ShapeWrap
{
	public Shape 	shape;
	public String	label;
	public Color	color;
	
	public ShapeWrap()
	{
		shape = null;
		label = "";
		color = Color.BLACK;
	}
	
	public void Draw(Graphics2D g2)
	{
		g2.setStroke(new BasicStroke(2.0f));
        g2.setPaint(color);
        g2.fill(shape);
        g2.draw(shape);
		g2.setStroke(new BasicStroke(1.0f));
	}
	
	public boolean Collision(Point2D p)
	{
		return shape.contains(p);
	}
	
	protected static final double THRESHHOLD = 2.f;
	
	public static Rectangle2D GenerateRectFromPoint(Point2D p, double thr)
	{
		return new Rectangle2D.Double(p.getX() - thr/2, p.getY() - thr/2, 
				thr, thr);
	}
	
	public ShapeWrap(Shape s)
	{
		shape = s;
		label = "";
		color = Color.BLACK;
	}
	
	public Point2D.Double[] GetPoints()
	{
		return new Point2D.Double[0]; 
	}
}