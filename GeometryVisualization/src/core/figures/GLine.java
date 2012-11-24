package core.figures;

import java.awt.Color;

public class GLine {
	private DisplayProperties displayProperties = new DisplayProperties('-', 1,
			Color.black);

	public DisplayProperties getDisplayProperties() {
		return displayProperties;
	}

	public void setDisplayProperties(DisplayProperties displayProperties) {
		this.displayProperties = displayProperties;
	}
}
