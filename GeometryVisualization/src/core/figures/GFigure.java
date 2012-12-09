package core.figures;

public abstract class GFigure {
	protected boolean isRendered = true;
	protected int id;
	protected DisplayProperties displayProperties;

	public GFigure() {
		setDefaultDisplayProperties();
	}

	protected abstract void setDefaultDisplayProperties();

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public boolean isRendered() {
		return isRendered;
	}

	public void setRendered(boolean isRendered) {
		this.isRendered = isRendered;
	}

	public DisplayProperties getDisplayProperties() {
		return displayProperties;
	}

	public void setDisplayProperties(DisplayProperties displayProperties) {
		this.displayProperties = displayProperties;
	}
}
