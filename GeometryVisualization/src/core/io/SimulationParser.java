package core.io;

import java.awt.Color;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.logging.LogManager;
import java.util.logging.Logger;

import core.figures.DisplayProperties;
import core.figures.GPoint;
import core.figures.GSegment;
import core.geom.PointDouble;
import core.io.attributes.DisplayPorpertiesAttributes;
import core.io.attributes.GeneralEventAttributes;
import core.io.attributes.PointEventAttributes;
import core.io.attributes.SegmentEventAttributes;
import core.io.attributes.StepEventAttributes;
import core.simulation.SimAction;
import core.simulation.SimEvent;
import core.simulation.SimStep;

class ParserLogger extends Logger {

	public ParserLogger(String name) {
		super(name, null);

	}

	public ParserLogger(String name, String resourceBundleName) {
		super(name, resourceBundleName);

	}

	public static ParserLogger getLogger(String name) {
		LogManager m = LogManager.getLogManager();
		Logger logger = m.getLogger(name);
		if (logger == null) {
			logger = new ParserLogger(name);
			m.addLogger(logger);
			return (ParserLogger) logger;
		} else {
			if (logger instanceof ParserLogger) {
				return (ParserLogger) logger;
			} else {
				return null;
			}
		}
	}

	private String lineNumberToString(int lineNumber) {
		return "line " + lineNumber + " : ";
	}

	public void info(int line, String msg) {
		info(lineNumberToString(line) + msg);
	}

	public void severe(int line, String msg) {
		severe(lineNumberToString(line) + msg);
	}

	public void warning(int line, String msg) {
		warning(lineNumberToString(line) + msg);
	}

}

public class SimulationParser {
	private final static ParserLogger LOGGER = ParserLogger
			.getLogger(SimulationParser.class.getName());

	/*
	 * pomocnicze zmienne wykorzystywane do przechowywania danych w czasie
	 * parsowania pliku
	 */
	private String textLine;
	private Integer lineNumber = 0;
	private Integer previousStep = -1;
	private List<SimStep> simulationList;
	private List<SimEvent> stepEventsList;

	public List<SimStep> parse(File filePath) throws FileNotFoundException,
			IOException {
		BufferedReader bufferedReader = new BufferedReader(new FileReader(
				filePath));
		try {
			simulationList = new ArrayList<SimStep>();
			stepEventsList = null;
			lineNumber = 0;
			previousStep = -1;
			while ((textLine = bufferedReader.readLine()) != null) {
				++lineNumber;
				parseLine();
			}
		} finally {
			bufferedReader.close();
		}
		LOGGER.info("File parsed");
		return simulationList;
	}

	private void parseLine() {
		textLine = textLine.trim();
		/* check if is a comment */
		if (!textLine.startsWith("#")) {
			String[] args = textLine.split(",");
			/* check if is non-empty */
			if (args.length > 0) {
				/* trim all arguments */
				trimAll(args);
				/* check if step */
				if (StepEventAttributes.symbol
						.equals(args[GeneralEventAttributes.TYPE.ordinal()])) {
					addNewStep(args);
				} else {
					/* check if step number is specified */
					if (stepEventsList != null) {
						/* add point */
						if (PointEventAttributes.symbol
								.equals(args[GeneralEventAttributes.TYPE
										.ordinal()].toLowerCase())) {
							createPoint(args);
						} else {
							/* add segment */
							if (SegmentEventAttributes.symbol
									.equals(args[GeneralEventAttributes.TYPE
											.ordinal()].toLowerCase())) {
								createSegemnt(args);
							}
						}
					} else {
						LOGGER.severe("line " + lineNumber
								+ ": no step was initialized.");
					}
				}
			} else {
				LOGGER.warning("line " + lineNumber + ": is empty.");
			}
		} else {
			LOGGER.info("line " + lineNumber + ": Treated as comment.");
		}
	}

	private boolean validateValuesQUantity(int line, String[] values,
			int expectedQuantity) {
		if (values.length != expectedQuantity) {
			LOGGER.warning("line " + line + ": " + expectedQuantity
					+ " values expected. Line will be omitted.");
			return false;
		}
		return true;
	}

	private void addNewStep(String[] args) {
		if (validateValuesQUantity(lineNumber, args,
				StepEventAttributes.attributesNumber)) {
			int newStepIndex = parseInteger(lineNumber,
					args[StepEventAttributes.INDEX.ordinal()]);
			if (newStepIndex <= previousStep) {
				LOGGER.warning(lineNumber, newStepIndex
						+ " - unexpected step value.");
			}
			stepEventsList = new LinkedList<SimEvent>();
			simulationList.add(new SimStep(newStepIndex, stepEventsList));
		}
	}

	private void trimAll(String[] stringArray) {
		for (int i = 0; i < stringArray.length; ++i) {
			stringArray[i] = stringArray[i].trim();
		}
	}

	private void createPoint(String[] args) {
		if (!validateValuesQUantity(lineNumber, args,
				PointEventAttributes.attributesNumber)) {
			return;
		} else {
			SimAction simAction = createSimAction(args);
			GPoint point = new GPoint(new PointDouble());
			point.getPoint().setX(
					parseDouble(lineNumber,
							args[PointEventAttributes.X.ordinal()]));
			point.getPoint().setY(
					parseDouble(lineNumber,
							args[PointEventAttributes.Y.ordinal()]));
			point.setId(parseInteger(lineNumber,
					args[PointEventAttributes.ID.ordinal()]));
			DisplayProperties displayProperties = createDisplayProportions(args[PointEventAttributes.STYLE
					.ordinal()]);
			if (displayProperties != null) {
				point.setDisplayProperties(displayProperties);
			}
			SimEvent simEvent = new SimEvent(simAction, point);
			stepEventsList.add(simEvent);
		}
	}

	private void createSegemnt(String[] args) {
		if (!validateValuesQUantity(lineNumber, args,
				SegmentEventAttributes.attributesNumber)) {
			return;
		} else {
			SimAction simAction = createSimAction(args);
			GSegment segment = new GSegment();
			GPoint pointA = new GPoint(new PointDouble());
			pointA.getPoint().setX(
					parseDouble(lineNumber,
							args[SegmentEventAttributes.AX.ordinal()]));
			pointA.getPoint().setY(
					parseDouble(lineNumber,
							args[SegmentEventAttributes.AY.ordinal()]));
			segment.setA(pointA);

			GPoint pointB = new GPoint(new PointDouble());
			pointB.getPoint().setX(
					parseDouble(lineNumber,
							args[SegmentEventAttributes.BX.ordinal()]));
			pointB.getPoint().setY(
					parseDouble(lineNumber,
							args[SegmentEventAttributes.BY.ordinal()]));
			segment.setB(pointB);

			DisplayProperties displayProperties = createDisplayProportions(args[PointEventAttributes.STYLE
					.ordinal()]);

			if (displayProperties != null) {
				segment.setDisplayProperties(displayProperties);
			}
			segment.setId(parseInteger(lineNumber,
					args[SegmentEventAttributes.ID.ordinal()]));
			SimEvent simEvent = new SimEvent(simAction, segment);
			stepEventsList.add(simEvent);
		}
	}

	private DisplayProperties createDisplayProportions(String dispPropsString) {
		String[] dispPropssArray = dispPropsString.split("&");
		if (dispPropssArray.length == 0) {
			return null;
		} else {
			if (dispPropssArray.length != 3) {
				if (!"HIDE".equals(dispPropssArray[0].toUpperCase())) {
					LOGGER.warning(lineNumber,
							"wrong number of display properties. Setting default display.");
				}
				return null;
			} else {
				String colorDescr = dispPropssArray[DisplayPorpertiesAttributes.COLOR
						.ordinal()];
				String styleDescr = dispPropssArray[DisplayPorpertiesAttributes.STYLE
						.ordinal()];
				String thicnessDescr = dispPropssArray[DisplayPorpertiesAttributes.THICKNESS
						.ordinal()];
				Color color;
				char style;
				Integer thickness;

				color = ColorMapper.getColor(colorDescr);
				if (color == null) {
					LOGGER.warning(lineNumber,
							"color incorrect. Setting default display.");
					return null;
				}
				if (styleDescr.length() != 1) {
					LOGGER.warning(lineNumber,
							"style incorrect. Setting default display.");
					return null;
				}
				style = styleDescr.charAt(0);
				thickness = parseInteger(lineNumber, thicnessDescr);
				if (thickness == null || thickness < 0) {
					LOGGER.warning(lineNumber,
							"thickness incorrect. Setting default display.");
					return null;
				}

				return new DisplayProperties(style, thickness, color);
			}
		}
	}

	private SimAction createSimAction(String[] args) {
		return "HIDE".equals(args[PointEventAttributes.STYLE.ordinal()]
				.toUpperCase()) ? SimAction.HIDE : SimAction.DISPLAY;
	}

	private Integer parseInteger(int lineNumber, String string) {
		try {
			return Integer.parseInt(string);
		} catch (NumberFormatException e) {
			LOGGER.warning("line " + lineNumber + "'" + string
					+ "' to int : NumberFormatException");
		}
		return null;
	}

	private Double parseDouble(int lineNumber, String string) {
		try {
			return Double.parseDouble(string);
		} catch (NumberFormatException e) {
			LOGGER.warning("line " + lineNumber + "'" + string
					+ "' to int : NumberFormatException");
		}
		return null;
	}
}
