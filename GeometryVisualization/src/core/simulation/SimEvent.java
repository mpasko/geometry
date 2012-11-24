package core.simulation;

import core.figures.GFigure;

public class SimEvent {
	SimAction action;
	GFigure figure;

	public SimEvent(SimAction action, GFigure figure) {
		super();
		this.action = action;
		this.figure = figure;
	}

	public SimAction getAction() {
		return action;
	}

	public void setAction(SimAction action) {
		this.action = action;
	}

	public GFigure getFigure() {
		return figure;
	}

	public void setFigure(GFigure figure) {
		this.figure = figure;
	}
}
