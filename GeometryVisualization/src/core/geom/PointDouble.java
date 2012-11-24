package core.geom;

import java.awt.geom.Point2D;

public class PointDouble extends Point2D {

	private double x, y;

	public PointDouble() {
		super();
	}

	public PointDouble(Point2D point) {
		super();
		x = point.getX();
		y = point.getY();
	}

	public PointDouble(double x, double y) {
		super();
		this.x = x;
		this.y = y;
	}

	@Override
	public double getX() {
		return x;
	}

	@Override
	public double getY() {
		return y;
	}

	public void setX(double x) {
		this.x = x;
	}

	public void setY(double y) {
		this.y = y;
	}

	@Override
	public void setLocation(double x, double y) {
		this.x = x;
		this.y = y;
	}

}
