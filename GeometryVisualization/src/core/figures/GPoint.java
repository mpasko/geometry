package core.figures;

import java.awt.Color;
import java.awt.Font;
import java.awt.geom.Point2D;

import core.geom.PointDouble;

public class GPoint extends GFigure {
	private Font font = new Font("Arial", Font.PLAIN, 12);
	private PointDouble point;

	public GPoint() {
		super();
	}

	public GPoint(Point2D point) {
		super();
		this.point = new PointDouble(point);
	}

	public GPoint(double x, double y) {
		super();
		this.point = new PointDouble(x, y);

	}

	public PointDouble getPoint() {
		return point;
	}

	public void setPoint(PointDouble point) {
		this.point = point;
	}

	public Font getFont() {
		return font;
	}

	public void setFont(Font font) {
		this.font = font;
	}

	@Override
	public String toString() {
		return "(" + point.getX() + ", " + point.getY() + ")";
	}

	@Override
	protected void setDefaultDisplayProperties() {
		displayProperties = new DisplayProperties('.', 1, Color.black);
	}

}
