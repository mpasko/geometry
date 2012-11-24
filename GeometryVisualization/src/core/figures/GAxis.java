package core.figures;

import java.awt.Color;
import java.awt.Font;

public class GAxis extends GFigure {
	private int separatorsNumber;
	private int subseparatorsNumber;
	private int separatorLength = 8;
	private int subseparatorLength = 4;
	private int numberSeparatorGapSize = 2;
	private Font font;

	private boolean showNumbers;

	private static Font defaultFont = new Font("Arail", Font.PLAIN, 12);
	private static int defaultSeparatorsNumber = 10;
	private static int defaultSubseparatorsNumber = 5;

	public GAxis() {
		super();
		this.isRendered = true;
		this.showNumbers = true;

	}

	@Override
	protected void setDefaultDisplayProperties() {
		displayProperties = new DisplayProperties('-', 1, Color.black);
		separatorsNumber = GAxis.defaultSeparatorsNumber;
		subseparatorsNumber = GAxis.defaultSubseparatorsNumber;
		font = GAxis.defaultFont;
	}

	public DisplayProperties getDisplayProperties() {
		return displayProperties;
	}

	public void setDisplayProperties(DisplayProperties displayProperties) {
		this.displayProperties = displayProperties;
	}

	public int getSeparatorsNumber() {
		return separatorsNumber;
	}

	public void setSeparatorsNumber(int separatorsNumber) {
		this.separatorsNumber = separatorsNumber;
	}

	public int getSubseparatorsNumber() {
		return subseparatorsNumber;
	}

	public void setSubseparatorsNumber(int subseparatorsNumber) {
		this.subseparatorsNumber = subseparatorsNumber;
	}

	public int getSeparatorLength() {
		return separatorLength;
	}

	public void setSeparatorLength(int separatorLength) {
		this.separatorLength = separatorLength;
	}

	public int getSubseparatorLength() {
		return subseparatorLength;
	}

	public void setSubseparatorLength(int subseparatorLength) {
		this.subseparatorLength = subseparatorLength;
	}

	public Font getFont() {
		return font;
	}

	public void setFont(Font font) {
		this.font = font;
	}

	public boolean isShowNumbers() {
		return showNumbers;
	}

	public void setShowNumbers(boolean showNumbers) {
		this.showNumbers = showNumbers;
	}

	public int getNumberSeparatorGapSize() {
		return numberSeparatorGapSize;
	}

	public void setNumberSeparatorGapSize(int numberSeparatorGapSize) {
		this.numberSeparatorGapSize = numberSeparatorGapSize;
	}
}
