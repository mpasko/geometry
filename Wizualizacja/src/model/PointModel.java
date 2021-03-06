package model;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.awt.geom.Point2D;
import java.awt.geom.Point2D.Double;

public class PointModel {

	public static int pointW = 3;
	public Point2D.Double point;
	public Color color;
	public String label;
	public int shape;
	public boolean messy;

	public PointModel(Point2D p, Color c, String l, int shapeID) {
		point = new Point2D.Double(p.getX(), p.getY());
		color = c;
		label = l;
		shape = shapeID;
	}
	/*	*/

	@Deprecated
	public int getVisibleX(double magnif, double transX, int centx) {
		int x = (int) ((point.x + transX) * magnif) + centx;
		return x;
	}

	@Deprecated
	public int getVisibleY(double magnif, double transY, int centy) {
		int y = (int) ((point.y + transY) * magnif) + centy;
		return y;
	}
	/*  */

	public int getVisibleX(AffineTransform t) {
		Point2D.Double tp = (Double) t.transform(point, null);
		return new java.lang.Double(tp.x).intValue();
	}

	public int getVisibleY(AffineTransform t) {
		Point2D.Double tp = (Double) t.transform(point, null);
		return new java.lang.Double(tp.y).intValue();
	}

	public void SetColor(Color c) {
		color = c;
	}

	@Deprecated
	public void Draw(Graphics2D g2d, double magnif, double transX, double transY, int centx, int centy) {
		g2d.setColor(color);
		double x = getVisibleX(magnif, transX, centx);
		double y = getVisibleY(magnif, transY, centy);

		g2d.drawRect((int) (x - pointW), (int) (y - pointW), 2 * pointW, 2 * pointW);
		g2d.setColor(Color.white);
		g2d.fillRect((int) (x - pointW) + 1, (int) (y - pointW) + 1, 2 * pointW - 2, 2 * pointW - 2);
		int txtx = (int) (x - pointW);
		int txty = (int) (y + 4 * pointW);
		int fontw = g2d.getFontMetrics().stringWidth(label);
		int fonth = g2d.getFontMetrics().getHeight();
		g2d.fillRect(txtx, (int) (y + 2 * pointW), fontw, fonth);
		g2d.setColor(color);
		g2d.drawString(label, txtx, txty);
	}

	public void Draw(Graphics2D g2d, AffineTransform t) {
		
		g2d.setColor(color);
		Point2D.Double tp = (Double) t.transform(point, null);
		double x = tp.x;
		double y = tp.y;

		if(messy){
			g2d.drawOval((int)x - pointW, (int)y - pointW, 2*pointW, 2*pointW);
		}
		if (color.equals(Color.red) || color.equals(Color.green)) {
			return;
		}
		g2d.drawRect((int) (x - pointW), (int) (y - pointW), 2 * pointW, 2 * pointW);
		g2d.setColor(Color.white);
		g2d.fillRect((int) (x - pointW) + 1, (int) (y - pointW) + 1, 2 * pointW - 2, 2 * pointW - 2);
		int txtx = (int) (x - pointW);
		int txty = (int) (y + 4 * pointW);
		int fontw = g2d.getFontMetrics().stringWidth(label);
		int fonth = g2d.getFontMetrics().getHeight();
		g2d.fillRect(txtx, (int) (y + 2 * pointW), fontw, fonth);
		g2d.setColor(color);
		g2d.drawString(label, txtx, txty);
	}

	@Override
	public boolean equals(Object o) {
		if (o instanceof PointModel) {
			PointModel pm = (PointModel) o;
			boolean match = Math.abs(point.x - pm.point.x) < 0.01
					&& Math.abs(point.y - pm.point.y) < 0.01;
			return match;
		} else {
			return false;
		}
	}
}
