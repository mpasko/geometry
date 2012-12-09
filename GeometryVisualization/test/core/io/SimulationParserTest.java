package core.io;

import java.io.File;
import java.util.List;

import org.junit.Test;

import core.simulation.SimEvent;
import core.simulation.SimStep;

public class SimulationParserTest {

	@Test
	public void testStepsLoading() {
		SimulationParser simParser = new SimulationParser();
		String filePath = "C:\\Users\\Właściciel\\Desktop\\Simulation.txt";
		try {
			List<SimStep> simStepsList = simParser.parse(new File(filePath));
			printEvents(simStepsList);
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	public void printEvents(List<SimStep> simStepsList) {
		for (SimStep simStep : simStepsList) {
			System.out.println("step: " + simStep.getStepNumber());
			for (SimEvent event : simStep.getSimEventsList()) {
				System.out.println(event.getFigure() + " disp: "
						+ event.getFigure().getDisplayProperties());
			}
		}
	}
}
