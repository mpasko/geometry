package core.figures;

import java.awt.Color;

public class GGrid extends GFigure {
	private int verticalLinesNumber = 10;
	private int horizontalLinesNumber = 10;

	private DisplayProperties displayProperties = new DisplayProperties(':', 1,
			Color.lightGray);

	@Override
	protected void setDefaultDisplayProperties() {
	}

	public int getVerticalLinesNumber() {
		return verticalLinesNumber;
	}

	public void setVerticalLinesNumber(int verticalLinesNumber) {
		this.verticalLinesNumber = verticalLinesNumber;
	}

	public int getHorizontalLinesNumber() {
		return horizontalLinesNumber;
	}

	public void setHorizontalLinesNumber(int horizontalLinesNumber) {
		this.horizontalLinesNumber = horizontalLinesNumber;
	}

	public DisplayProperties getDisplayProperties() {
		return displayProperties;
	}

	public void setDisplayProperties(DisplayProperties displayProperties) {
		this.displayProperties = displayProperties;
	}
}
