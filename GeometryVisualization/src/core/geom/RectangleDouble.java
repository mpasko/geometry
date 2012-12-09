package core.geom;

import java.awt.geom.Rectangle2D;

public class RectangleDouble extends Rectangle2D {

	double x, y, width, height;

	public RectangleDouble(double x, double y, double width, double height) {
		super();
		setRect(x, y, width, height);
	}

	@Override
	public void setRect(double x, double y, double w, double h) {
		this.x = x;
		this.y = y;
		this.width = w;
		this.height = h;
	}

	@Override
	public int outcode(double x, double y) {
		int out = 0;
		if (this.width <= 0) {
			out |= OUT_LEFT | OUT_RIGHT;
		} else if (x < this.x) {
			out |= OUT_LEFT;
		} else if (x > this.x + this.width) {
			out |= OUT_RIGHT;
		}
		if (this.height <= 0) {
			out |= OUT_TOP | OUT_BOTTOM;
		} else if (y < this.y) {
			out |= OUT_TOP;
		} else if (y > this.y + this.height) {
			out |= OUT_BOTTOM;
		}
		return out;
	}

	@Override
	public Rectangle2D createIntersection(Rectangle2D r) {
		Rectangle2D dest = new Rectangle2D.Double();
		Rectangle2D.intersect(this, r, dest);
		return dest;
	}

	@Override
	public Rectangle2D createUnion(Rectangle2D r) {
		Rectangle2D dest = new Rectangle2D.Double();
		Rectangle2D.union(this, r, dest);
		return dest;
	}

	@Override
	public double getX() {
		return x;
	}

	@Override
	public double getY() {
		return y;
	}

	@Override
	public double getWidth() {
		return width;
	}

	@Override
	public double getHeight() {
		return height;
	}

	@Override
	public boolean isEmpty() {
		return width <= 0 || height <= 0;
	}

	public void setMinX(double x) {
		setRect(x, y, width, height);
	}

	public void setMinY(double y) {
		setRect(x, y, width, height);
	}

	public void setMaxX(double x) {
		width = x - this.x;
	}

	public void setMaxY(double y) {
		height = y - this.y;
	}
}
