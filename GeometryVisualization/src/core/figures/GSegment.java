package core.figures;

import java.awt.Color;
import java.awt.geom.Point2D;

public class GSegment extends GFigure {
	GPoint a;
	GPoint b;

	public GSegment() {
		super();
	}

	public GSegment(Point2D a, Point2D b) {
		super();
		this.a = new GPoint(a);
		this.b = new GPoint(b);
	}

	@Override
	protected void setDefaultDisplayProperties() {
		displayProperties = new DisplayProperties('-', 1, Color.black);
	}

	public GPoint getPointA() {
		return a;
	}

	public void setA(GPoint a) {
		this.a = a;
	}

	public GPoint getPointB() {
		return b;
	}

	public void setB(GPoint b) {
		this.b = b;
	}

	@Override
	public String toString() {
		return a + ", " + b;
	}

}
