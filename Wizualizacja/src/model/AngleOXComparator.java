package model;

import java.awt.geom.Point2D;
import java.util.Comparator;

public class AngleOXComparator implements Comparator<Point2D>{
	Point2D p0;
	
	AngleOXComparator(Point2D p0)
	{
		this.p0 = p0;
	}
	@Override
	public int compare(Point2D o1, Point2D o2) {
		Point2D.Double v1 = new Point2D.Double(o1.getX() - p0.getX(), o1.getY() - p0.getY());
		Point2D.Double v2 = new Point2D.Double(o2.getX() - p0.getX(), o2.getY() - p0.getY());
		double a1 = GHelper.getOXAngle(v1);
		double a2 = GHelper.getOXAngle(v2);
		if(a1 < a2) return -1;
		if(a1 > a2) return 1;
		return 0;
	}
}