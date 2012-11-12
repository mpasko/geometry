package model;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Shape;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;
import java.awt.geom.Point2D.Double;

public class LineWrap extends ShapeWrap
{
	public LineWrap(Shape s)
	{
		super(s);
	}
	
	public LineWrap(Point2D.Double p0, Point2D.Double p1)
	{
		super();
		shape = new Line2D.Double(p0, p1);
	}
	
	public LineWrap(Point2D.Double p0, Point2D.Double p1, Color c)
	{
		super();
		shape = new Line2D.Double(p0, p1);
		color = c;
	}
	
	public LineWrap(double x0, double y0, double x1, double y1)
	{
		super();
		shape = new Line2D.Double(x0, y0, x1, y1);
	}
	
	public void Draw(Graphics2D g2)
	{
		g2.setStroke(new BasicStroke(2.0f));
        g2.setPaint(color);
        g2.draw(shape);
        g2.setStroke(new BasicStroke(1.0f));
	}
	
	public boolean Collision(Point2D p)
	{
		return shape.intersects(GenerateRectFromPoint(p, THRESHHOLD));
	}
	
	public Point2D.Double[] GetPoints()
	{
		Point2D.Double[] out = new Point2D.Double[2];
		out[0] = (Double) ((Line2D.Double) shape).getP1();
		out[1] = (Double) ((Line2D.Double) shape).getP2();
		return out;
	}
}