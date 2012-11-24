package core.figures;

import java.awt.Font;
import java.awt.Graphics;
import java.awt.font.FontRenderContext;

public class TextCoordinatesTransformer {
	public static Integer transformXCoordintaes(String text, Graphics g, int x,
			XTextCoordinates xCoordinates) {
		Font font = g.getFont();
		FontRenderContext fontRenderContext = g.getFontMetrics()
				.getFontRenderContext();
		switch (xCoordinates) {
		case LEFT:
			return x;
		case CENTER:
			return (int) (x - font.getStringBounds(text, fontRenderContext)
					.getCenterX());
		case RIGHT:
			return (int) (x - font.getStringBounds(text, fontRenderContext)
					.getMaxX());
		default:
			return null;
		}
	}

	public static Integer transformYCoordintaes(String text, Graphics g, int y,
			YTextCoordinates yCoordinates) {
		Font font = g.getFont();
		FontRenderContext fontRenderContext = g.getFontMetrics()
				.getFontRenderContext();
		switch (yCoordinates) {
		case DOWN:
			return y;
		case CENTER:
			return (int) (y - font.getStringBounds(text, fontRenderContext)
					.getCenterY());
		case TOP:
			return (int) (y - font.getStringBounds(text, fontRenderContext)
					.getMaxY());
		default:
			return null;
		}
	}

	/*
	 * public static int transformXCoordintaes(String text, Graphics g, int x,
	 * XCoordinates xCoordinates) { Double x = null, y = null; if (xCoordinates
	 * == XCoordinates.LEFT && yCoordinates == YCoordinates.DOWN) { return new
	 * PointDouble(point); } Font font = g.getFont(); FontRenderContext
	 * fontRenderContext = g.getFontMetrics() .getFontRenderContext(); switch
	 * (xCoordinates) { case LEFT: x = point.getX(); break; case CENTER: x =
	 * point.getX() + font.getStringBounds(text, fontRenderContext)
	 * .getCenterX(); break; case RIGHT: x = point.getX() +
	 * font.getStringBounds(text, fontRenderContext).getMaxX(); break; } switch
	 * (yCoordinates) { case TOP: y = point.getX(); break; case CENTER: y =
	 * point.getY() + font.getStringBounds(text, fontRenderContext)
	 * .getCenterY(); break; case DOWN: y = point.getX() +
	 * font.getStringBounds(text, fontRenderContext).getMaxY(); break; } return
	 * new PointDouble(x, y); }
	 */
}
