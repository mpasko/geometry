package core.simulation;

import java.util.List;

public class SimStep {
	int stepNumber;
	List<SimEvent> simventsList;

	public SimStep(int stepNumber, List<SimEvent> simventsList) {
		super();
		this.stepNumber = stepNumber;
		this.simventsList = simventsList;
	}

	public int getStepNumber() {
		return stepNumber;
	}

	public void setStepNumber(int stepNumber) {
		this.stepNumber = stepNumber;
	}

	public List<SimEvent> getSimEventsList() {
		return simventsList;
	}

	public void setSimventsList(List<SimEvent> simventsList) {
		this.simventsList = simventsList;
	}
}
