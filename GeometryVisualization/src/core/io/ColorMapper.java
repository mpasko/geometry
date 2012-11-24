package core.io;

import java.awt.Color;

public class ColorMapper {
	public static Color getColor(String string) {
		if (string == null || string.isEmpty()) {
			return null;
		}

		String colorString = string.toUpperCase().trim();

		if ("WHITE".equals(colorString)) {
			return Color.WHITE;
		}
		if ("LIGHT_GRAY".equals(colorString)) {
			return Color.LIGHT_GRAY;
		}
		if ("GRAY".equals(colorString)) {
			return Color.GRAY;
		}
		if ("DARK_GRAY".equals(colorString)) {
			return Color.DARK_GRAY;
		}
		if ("BLACK".equals(colorString)) {
			return Color.BLACK;
		}
		if ("RED".equals(colorString)) {
			return Color.RED;
		}
		if ("PINK".equals(colorString)) {
			return Color.PINK;
		}
		if ("ORANGE".equals(colorString)) {
			return Color.ORANGE;
		}
		if ("YELLOW".equals(colorString)) {
			return Color.YELLOW;
		}
		if ("GREEN".equals(colorString)) {
			return Color.GREEN;
		}
		if ("MAGENTA".equals(colorString)) {
			return Color.MAGENTA;
		}
		if ("CYAN".equals(colorString)) {
			return Color.CYAN;
		}
		if ("BLUE".equals(colorString)) {
			return Color.BLUE;
		}

		// TODO
		throw new UnsupportedOperationException("Cannot map '" + string
				+ "' color.");
	}
}
