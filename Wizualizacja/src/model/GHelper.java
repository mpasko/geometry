package model;

import java.awt.geom.Point2D;
import java.awt.geom.Point2D.Double;

public class GHelper
{
	public static double getAngle(Point2D.Double p1, Point2D.Double p2)
	{
		Point2D.Double p1n = VNor(p1);
		Point2D.Double p2n = VNor(p2);
		
		return Math.acos(p1n.getX() * p2n.getX() + p1n.getY() * p2n.getY());
	}
	
	public static double getOXAngle(Point2D.Double p)
	{
		Point2D.Double ox = new Point2D.Double(1.,0.);
		return getAngle(p, ox);
	}
	
	public static double side(Point2D a,Point2D b,Point2D c)
	{
		return (a.getX() - c.getX()) * (b.getY() - c.getY()) - (a.getY() - c.getY()) * (b.getX() - c.getX());
	}
	
	public static Point2D.Double VAdd (Point2D.Double v1, Point2D.Double v2) {
		return new Point2D.Double(v1.x + v2.x, v1.y + v2.y); 
	}
	
	public static Point2D.Double VSub (Point2D.Double v1, Point2D.Double v2) {
		return new Point2D.Double(v1.x - v2.x, v1.y - v2.y); 
	}
	
	public static Point2D.Double VMul (Point2D.Double v1, double d) {
		return new Point2D.Double(v1.x * d, v1.y * d); 
	}
	
	public static Point2D.Double VNor (Point2D.Double v1)
	{
		return new Point2D.Double(v1.getX()/VLen(v1), v1.getY()/VLen(v1));
	}
	
	public static double VLen( Point2D.Double v1)
	{
		return Math.sqrt(v1.x * v1.x + v1.y * v1.y); 
	}
	
	static public Point2D.Double[] GenerateOnQuad(int n, Point2D.Double v[])
	{
		Point2D.Double out[] = new Point2D.Double[n]; 
		
		double dist[] = new double [4];
		
		Point2D.Double _v[] = new Point2D.Double[4];
		_v[0] = VSub(v[1],v[0]);
		_v[1] = VSub(v[2],v[1]);
		_v[2] = VSub(v[3],v[2]);
		_v[3] = VSub(v[0],v[3]);
		
		dist[0] = v[0].distance(v[1]);
		dist[1] = v[1].distance(v[2]);
		dist[2] = v[2].distance(v[3]);
		dist[3] = v[3].distance(v[0]);
		double sum = dist[0]+dist[1]+dist[2]+dist[3];
		
		for(int i=0;i<n;i++)
		{
			double rand = Math.random() * sum;
			int e = 0;
			double acc = 0;
			while(acc + dist[e] < rand)
			{
				acc += dist[e];
				e++;
			}
			
			double rdist = Math.random() * dist[e];
			
			out[i] = VAdd(v[e], VMul(VNor(_v[e]),rdist));
		}
		
		return out;
	}
	
	static public Point2D.Double[] GenerateOnArea(int n, double minX, double maxX, double minY, double maxY)
	{
		
		Point2D.Double out[] = new Point2D.Double[n]; 
		
		for(int i=0;i<n;i++)
		{
			out[i] = new Point2D.Double((maxX-minX)*Math.random() + minX, (maxY-minY)*Math.random() + minY);
		}
		
		return out;
	}
	
	static public Point2D.Double[] GenerateOnCircle(int n, Point2D.Double mid, double ray)
	{
		Point2D.Double out[] = new Point2D.Double[n];
		
		for(int i=0;i<n;i++)
		{
			double arc = Math.random() * Math.PI * 2;
			
			out[i] = new Point2D.Double(Math.sin(arc)* ray, Math.cos(arc)* ray);
			
			out[i].x += mid.x;
			out[i].y += mid.y;
		}
		
		return out;
	}
	
	static public Point2D.Double[] GenerateOnQuadWithDiagonals(int n, int m, Point2D.Double v[])
	{
		if(n<4) return new Point2D.Double[0];
		
		Point2D.Double out[] = new Point2D.Double[n + m];
		out[0] = new Point2D.Double(v[0].x, v[0].y);
		out[1] = new Point2D.Double(v[1].x, v[1].y);
		out[2] = new Point2D.Double(v[2].x, v[2].y);
		out[3] = new Point2D.Double(v[3].x, v[3].y);
		
		Point2D.Double _N[] = GenerateOnQuad(n-4, v);
		for(int i=0;i<n-4;i++)
			out[i+4] = _N[i];
		
		Point2D.Double diag []= new Point2D.Double [2]; 
		diag[0] = VSub(v[2], v[0]);
		diag[1] = VSub(v[3], v[1]);
		
		double l0 = VLen(diag[0]);
		double l1 = VLen(diag[1]);
		
		for(int i=0;i<m;i++)
		{
			int k = 0;
			if(Math.random() * (l0+l1) > l0) k = 1;
			
			double scale= Math.random();
			
			out[n+i] = VAdd(v[k], VMul(VNor(diag[k]),scale * VLen(diag[k])));
		}
		
		return out;
	}
}