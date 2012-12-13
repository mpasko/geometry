package model;

import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.List;

public class Model {
	public List<PointModel> points = new ArrayList<PointModel>();
	
	synchronized public void AddPoint(PointModel e)
	{
		points.add(e);
	}
	
	synchronized public void RemovePoint(PointModel e)
	{
		points.remove(e);
	}
        
        synchronized public void clean(){
                points.clear();
        }
	
	synchronized public PointModel FindPointByCoords(double x, double y)
	{
		for(PointModel p : points)
		{
			if(p.point.x == x && p.point.y == y)
				return p;
		}
		
		return null;
	}
	
	synchronized public PointModel FindPointByCoords(Point2D.Double coords)
	{
		return FindPointByCoords(coords.x, coords.y);
	}
}
