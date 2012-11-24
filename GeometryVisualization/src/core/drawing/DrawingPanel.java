package core.drawing;

import java.awt.Color;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;
import java.text.NumberFormat;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import javax.swing.JPanel;
import javax.swing.event.MouseInputAdapter;

import core.figures.DisplayProperties;
import core.figures.GAxis;
import core.figures.GFigure;
import core.figures.GGrid;
import core.figures.GPoint;
import core.figures.GSegment;
import core.figures.TextCoordinatesTransformer;
import core.figures.XTextCoordinates;
import core.figures.YTextCoordinates;
import core.geom.PointDouble;
import core.geom.RectangleDouble;

public class DrawingPanel extends JPanel {
	Map<Integer, GFigure> figuresMap = new HashMap<Integer, GFigure>();
	RectangleDouble drawingArea;
	GAxis oxAxis = new GAxis();
	GAxis oyAxis = new GAxis();
	GGrid grid = new GGrid();

	PointPainter pointPainter = new PointPainter();
	SegmentPainter segmentPainter = new SegmentPainter(pointPainter);
	LinePainter linePainter = new LinePainter();
	HorizontalAxisPainter horizontalAxisPainter = new HorizontalAxisPainter(
			linePainter);
	VerticalAxisPainter verticalAxisPainter = new VerticalAxisPainter(
			linePainter);
	GridPainter gridPainter = new GridPainter(linePainter);

	private static double zoomPerClick = 1.2;
	private static double dragFactor = 0.75;

	private class DragListener extends MouseInputAdapter {
		Point2D startingPoint;

		public void mousePressed(MouseEvent e) {
			startingPoint = projectPointToPlotCoords(e.getPoint());
		}

		public void mouseDragged(MouseEvent e) {
			drawPlot(startingPoint, projectPointToPlotCoords(e.getPoint()));
			startingPoint = projectPointToPlotCoords(e.getPoint());
		}

		public void mouseReleased(MouseEvent e) {
			drawPlot(startingPoint, projectPointToPlotCoords(e.getPoint()));
			repaint();
		}

		private void drawPlot(Point2D startingPoint, Point2D endingPoint) {
			drawingArea.setRect(
					drawingArea.getMinX()
							+ (endingPoint.getX() - startingPoint.getX())
							* dragFactor,
					drawingArea.getMinY()
							+ (endingPoint.getY() - startingPoint.getY())
							* dragFactor, drawingArea.getWidth(),
					drawingArea.getHeight());
			repaint();
		}

		public void register(Component parent) {
			register(parent, true);
		}

		public void register(Component parent, boolean isDraggable) {
			if (isDraggable) {
				parent.addMouseMotionListener(this);
			}
			parent.addMouseListener(this);
		}
	}

	public DrawingPanel() {
		super();
		setBackground(Color.white);
		drawingArea = new RectangleDouble(0, 0, 10, 10);

		grid.getDisplayProperties().setStyle('-');
		grid.setRendered(true);

		DragListener dragListener = new DragListener();
		dragListener.register(this);
	}

	@Override
	public void paint(Graphics g) {
		super.paint(g);
		Graphics gg = g.create();
		drawAll(gg);
	}

	private void drawAll(Graphics g) {
		synchronized (this) {
			if (grid.isRendered()) {
				gridPainter.drawGrid(grid, g);
			}

			if (oxAxis.isRendered()) {
				horizontalAxisPainter.drawHorizontalAxis(oxAxis, g);
			}

			if (oyAxis.isRendered()) {
				verticalAxisPainter.drawVerticalAxis(oyAxis, g);
			}

			Set<Entry<Integer, GFigure>> entrySet = figuresMap.entrySet();
			for (Entry<Integer, GFigure> entry : entrySet) {
				if (entry.getValue() instanceof GSegment) {
					if (entry.getValue().isRendered()) {
						segmentPainter.drawSegment((GSegment) entry.getValue(),
								g);
					}
				}
			}
			for (Entry<Integer, GFigure> entry : entrySet) {
				if (entry.getValue() instanceof GPoint) {
					if (entry.getValue().isRendered()) {
						pointPainter.drawPoint((GPoint) entry.getValue(), g);
					}
				}
			}
		}
	}

	class SegmentPainter {
		PointPainter pointPainter;
		boolean drawLables = true;
		int labelVerticalDistanceFromCenter = 5;

		public SegmentPainter(PointPainter pointPainter) {
			super();
			this.pointPainter = pointPainter;
		}

		public void drawSegment(GSegment segment, Graphics g) {
			g.setColor(segment.getDisplayProperties().getColor());
			Point2D projectedPointA = projectPointToComponentCoords(segment
					.getPointA().getPoint());
			Point2D projectedPointB = projectPointToComponentCoords(segment
					.getPointB().getPoint());
			switch (segment.getDisplayProperties().getStyle()) {
			case '-':
				g.drawLine((int) projectedPointA.getX(),
						(int) projectedPointA.getY(),
						(int) projectedPointB.getX(),
						(int) projectedPointB.getY());
				break;
			case '.':
				g.drawLine((int) projectedPointA.getX(),
						(int) projectedPointA.getY(),
						(int) projectedPointB.getX(),
						(int) projectedPointB.getY());
				pointPainter.drawProjectedPoint(projectedPointA,
						segment.getDisplayProperties(), g);
				pointPainter.drawProjectedPoint(projectedPointB,
						segment.getDisplayProperties(), g);
			}
			if (drawLables == true) {
				g.setColor(Color.red);
				g.drawString(
						String.valueOf(segment.getId()),
						TextCoordinatesTransformer.transformXCoordintaes(
								String.valueOf(segment.getId()),
								g,
								(int) (projectedPointB.getX() + (projectedPointA
										.getX() - projectedPointB.getX()) / 2.0),
								XTextCoordinates.CENTER),
						TextCoordinatesTransformer.transformYCoordintaes(
								String.valueOf(segment.getId()),
								g,
								(int) (projectedPointB.getY() + (projectedPointA
										.getY() - projectedPointB.getY()) / 2.0)
										- labelVerticalDistanceFromCenter,
								YTextCoordinates.DOWN)

				);
				g.setColor(Color.black);
			}
		}

		public boolean isDrawLables() {
			return drawLables;
		}

		public void setDrawLables(boolean drawLables) {
			this.drawLables = drawLables;
		}

	}

	class GridPainter {
		LinePainter linePainter;

		public GridPainter(LinePainter linePainter) {
			this.linePainter = linePainter;
		}

		public void drawGrid(GGrid grid, Graphics g) {
			g.setColor(grid.getDisplayProperties().getColor());
			switch (grid.getDisplayProperties().getStyle()) {
			case '-':
				double gridLinesGap = getWidth()
						/ (double) (grid.getVerticalLinesNumber() + 1);
				double lineCoordinate = 0;
				for (int i = 0; i < grid.getVerticalLinesNumber(); ++i) {
					lineCoordinate += gridLinesGap;
					linePainter.drawLineInComponent(new PointDouble(
							lineCoordinate, 0), new PointDouble(lineCoordinate,
							getHeight()), grid.getDisplayProperties(), g);
				}
				gridLinesGap = getHeight()
						/ (double) (grid.getHorizontalLinesNumber() + 1);
				lineCoordinate = 0;
				for (int i = 0; i < grid.getHorizontalLinesNumber(); ++i) {
					lineCoordinate += gridLinesGap;
					linePainter.drawLineInComponent(new PointDouble(0,
							lineCoordinate), new PointDouble(getWidth(),
							lineCoordinate), grid.getDisplayProperties(), g);
				}
				break;
			}
		}
	}

	class PointPainter {

		public void drawPoint(GPoint point, Graphics g) {
			Point2D projectedPoint = projectPointToComponentCoords(point
					.getPoint());
			drawProjectedPoint(projectedPoint, point.getDisplayProperties(), g);
		}

		public void drawProjectedPoint(Point2D projectedPoint,
				DisplayProperties dispProperties, Graphics g) {
			g.setColor(dispProperties.getColor());
			switch (dispProperties.getStyle()) {
			case '.':
				int thickness = dispProperties.getThickness();
				g.fillOval((int) projectedPoint.getX() - thickness - 1,
						(int) projectedPoint.getY() - thickness - 1,
						thickness * 2 + 1, thickness * 2 + 1);
				break;
			}
		}
	}

	class LinePainter {
		public void drawLine(Point startPoint, Point endPoint,
				DisplayProperties displayProperties, Graphics g) {
			PointDouble projStartPoint = projectPointToComponentCoords(startPoint);
			PointDouble projEndPoint = projectPointToComponentCoords(endPoint);

			drawLineInComponent(projStartPoint, projEndPoint,
					displayProperties, g);
		}

		public void drawLineInComponent(PointDouble startPoint,
				PointDouble endPoint, DisplayProperties displayProperties,
				Graphics g) {
			g.setColor(displayProperties.getColor());
			switch (displayProperties.getStyle()) {
			case '-':
				g.drawLine((int) startPoint.getX(), (int) startPoint.getY(),
						(int) endPoint.getX(), (int) endPoint.getY());
				break;
			}
		}
	}

	class HorizontalAxisPainter {
		LinePainter linePainter;

		public HorizontalAxisPainter(LinePainter linePainter) {
			this.linePainter = linePainter;
		}

		public void drawHorizontalAxis(GAxis axis, Graphics g) {
			g.setColor(axis.getDisplayProperties().getColor());
			g.setFont(axis.getFont());
			double gap = getWidth() / (double) (axis.getSeparatorsNumber() + 1);
			double plotGap = drawingArea.getWidth()
					/ (double) (axis.getSeparatorsNumber() + 1);
			double lineCoordinate = 0;
			int separatorStart = getHeight();
			int separatorEnd = getHeight() - axis.getSeparatorLength();
			for (int i = 0; i < axis.getSeparatorsNumber(); ++i) {
				lineCoordinate += gap;
				linePainter.drawLineInComponent(new PointDouble(lineCoordinate,
						separatorStart), new PointDouble(lineCoordinate,
						separatorEnd), axis.getDisplayProperties(), g);
			}
			if (axis.isShowNumbers()) {
				lineCoordinate = 0;
				double plotLineCoordinate = drawingArea.getMinX();
				int textHeight = separatorEnd
						- axis.getNumberSeparatorGapSize();
				NumberFormat numberFormat = NumberFormat.getNumberInstance();
				numberFormat.setMaximumFractionDigits(2);
				String number;

				for (int i = 0; i < axis.getSeparatorsNumber(); ++i) {
					lineCoordinate += gap;
					plotLineCoordinate += plotGap;
					number = numberFormat.format(plotLineCoordinate);
					g.drawString(number, TextCoordinatesTransformer
							.transformXCoordintaes(number, g,
									(int) lineCoordinate,
									XTextCoordinates.CENTER), textHeight);
				}
			}
		}
	}

	class VerticalAxisPainter {
		LinePainter linePainter;

		public VerticalAxisPainter(LinePainter linePainter) {
			this.linePainter = linePainter;
		}

		public void drawVerticalAxis(GAxis axis, Graphics g) {
			g.setColor(axis.getDisplayProperties().getColor());
			g.setFont(axis.getFont());
			double gap = getHeight()
					/ (double) (axis.getSeparatorsNumber() + 1);
			double plotGap = drawingArea.getHeight()
					/ (double) (axis.getSeparatorsNumber() + 1);
			double lineCoordinate = 0;
			int separatorStart = 0;
			int separatorEnd = axis.getSeparatorLength();
			for (int i = 0; i < axis.getSeparatorsNumber(); ++i) {
				lineCoordinate += gap;
				linePainter.drawLineInComponent(new PointDouble(separatorStart,
						lineCoordinate), new PointDouble(separatorEnd,
						lineCoordinate), axis.getDisplayProperties(), g);
			}
			if (axis.isShowNumbers()) {
				lineCoordinate = 0;
				double plotLineCoordinate = drawingArea.getMaxY();
				int textStart = separatorEnd + axis.getNumberSeparatorGapSize();
				NumberFormat numberFormat = NumberFormat.getNumberInstance();
				numberFormat.setMaximumFractionDigits(2);
				String number;

				for (int i = 0; i < axis.getSeparatorsNumber(); ++i) {
					lineCoordinate += gap;
					plotLineCoordinate -= plotGap;
					number = numberFormat.format(plotLineCoordinate);
					g.drawString(number, textStart, TextCoordinatesTransformer
							.transformYCoordintaes(number, g,
									(int) lineCoordinate,
									YTextCoordinates.CENTER));
				}
			}
		}
	}

	class StringPrinter {
		public void drawString(String string, Graphics g) {
		}
	}

	protected final PointDouble projectPointToComponentCoords(Point2D point) {
		// if (!drawingArea.contains(point)) {
		// return null;
		// }
		PointDouble projectedPoint = new PointDouble();
		projectedPoint.setLocation((point.getX() - getDrawingArea().getMinX())
				* getWidth() / getDrawingArea().getWidth(), getHeight()
				* (1 - (point.getY() - getDrawingArea().getMinY())
						/ getDrawingArea().getHeight()));
		return projectedPoint;
	}

	protected final PointDouble projectPointToPlotCoords(Point2D point) {
		PointDouble projectedPoint = new PointDouble();
		projectedPoint.setLocation(
				getDrawingArea().getMinX() + drawingArea.getWidth()
						/ getWidth() * point.getX(), getDrawingArea().getMinY()
						+ drawingArea.getHeight()
						* (1 - point.getY() / getHeight()));
		return projectedPoint;
	}

	public void zoom(int clicksCount, Point point) {
		double zoomFactor = 0;
		if (clicksCount > 0) {
			zoomFactor = zoomPerClick;
		} else {
			zoomFactor = 1 / zoomPerClick;
		}
		Point2D projectedPoint = projectPointToPlotCoords(point);
		double x0 = projectedPoint.getX() - zoomFactor
				* (projectedPoint.getX() - drawingArea.getMinX());
		double y0 = projectedPoint.getY() - zoomFactor
				* (projectedPoint.getY() - drawingArea.getMinY());
		double xn = projectedPoint.getX() + zoomFactor
				* (drawingArea.getMaxX() - projectedPoint.getX());
		double yn = projectedPoint.getY() + zoomFactor
				* (drawingArea.getMaxY() - projectedPoint.getY());
		drawingArea.setRect(x0, y0, xn - x0, yn - y0);

		repaint();
	}

	public RectangleDouble getDrawingArea() {
		return drawingArea;
	}

	public void setDrawingArea(RectangleDouble drawingArea) {
		this.drawingArea = drawingArea;
	}

	public Map<Integer, GFigure> getFiguresMap() {
		return figuresMap;
	}

	public void setFiguresMap(Map<Integer, GFigure> figuresMap) {
		this.figuresMap = figuresMap;
	}

	public GAxis getOxAxis() {
		return oxAxis;
	}

	public GAxis getOyAxis() {
		return oyAxis;
	}

	public GGrid getGrid() {
		return grid;
	}

	public PointPainter getPointPainter() {
		return pointPainter;
	}

	public LinePainter getLinePainter() {
		return linePainter;
	}

	public HorizontalAxisPainter getHorizontalAxisPainter() {
		return horizontalAxisPainter;
	}

	public VerticalAxisPainter getVerticalAxisPainter() {
		return verticalAxisPainter;
	}

	public GridPainter getGridPainter() {
		return gridPainter;
	}

}
