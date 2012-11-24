package core.figures;

import java.awt.Color;

public class DisplayProperties {
	private char style;
	private int thickness;
	private Color color;

	public DisplayProperties() {
		super();
	}

	public DisplayProperties(char style, int thickness, Color color) {
		super();
		this.style = style;
		this.thickness = thickness;
		this.color = color;
	}

	public char getStyle() {
		return style;
	}

	public void setStyle(char style) {
		this.style = style;
	}

	public int getThickness() {
		return thickness;
	}

	public void setThickness(int thickness) {
		this.thickness = thickness;
	}

	public Color getColor() {
		return color;
	}

	public void setColor(Color color) {
		this.color = color;
	}

	@Override
	public String toString() {
		return "([" + color.getRed() + "," + color.getGreen() + ","
				+ color.getBlue() + "], " + style + ", " + thickness + ")";
	}
}
