package core.simulation;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import core.drawing.DrawingPanel;
import core.figures.GFigure;

public class Simulator {
	List<SimStep> simulationList = new ArrayList<SimStep>();
	DrawingPanel drawingPanel;
	int step;

	public void loadSimultionList(List<SimStep> simulationList) {
		this.simulationList = simulationList;
	}

	public Map<Integer, GFigure> getInitialGeometry() {
		List<SimEvent> stepList;

		if (simulationList.isEmpty()) {
			return null;
		} else {
			stepList = simulationList.get(0).getSimEventsList();
		}

		Map<Integer, GFigure> figuresMap = new HashMap<Integer, GFigure>(
				(int) (stepList.size() / 0.75) + 1);

		for (SimEvent simEvent : stepList) {
			if (simEvent.getAction() == SimAction.DISPLAY) {
				figuresMap.put(simEvent.getFigure().getId(),
						simEvent.getFigure());
			} else {
				figuresMap.remove(simEvent.getFigure().getId());
			}
		}
		step = 0;
		return figuresMap;
	}

	public void nextStepUpdate(Map<Integer, GFigure> figuresMap) {
		if (step + 1 >= simulationList.size()) {
			return;
		}
		++step;
		for (SimEvent simEvent : simulationList.get(step).getSimEventsList()) {
			if (simEvent.getAction() == SimAction.DISPLAY) {
				figuresMap.put(simEvent.getFigure().getId(),
						simEvent.getFigure());
			} else {
				figuresMap.remove(simEvent.getFigure().getId());
			}
		}
	}

	public void stepUpdate(int stepIndex, Map<Integer, GFigure> figuresMap) {
		if (stepIndex >= simulationList.size() || stepIndex < 0) {
			return;
		}
		step = stepIndex;
		for (SimEvent simEvent : simulationList.get(step).getSimEventsList()) {
			if (simEvent.getAction() == SimAction.DISPLAY) {
				figuresMap.put(simEvent.getFigure().getId(),
						simEvent.getFigure());
			} else {
				figuresMap.remove(simEvent.getFigure().getId());
			}
		}
	}

	public int getStep() {
		return step;
	}

	public void setStep(int step) {
		this.step = step;
	}

	public int maxStep() {
		return simulationList.size() - 1;
	}
}
