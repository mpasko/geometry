package view;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Shape;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.awt.geom.AffineTransform;
import java.awt.geom.GeneralPath;
import java.awt.geom.Line2D;
import java.awt.geom.NoninvertibleTransformException;
import java.awt.geom.Point2D;
import java.awt.geom.Point2D.Double;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import javax.swing.JComponent;
import javax.swing.SwingUtilities;

import model.LineWrap;
import model.Model;
import model.PointModel;
import model.ShapeWrap;
import formatter.IFormatter;

public class PlanePanel extends JComponent implements MouseMotionListener, MouseListener, MouseWheelListener, IController {

    /**
     *
     */
    private static final long serialVersionUID = 1379314306499920242L;
    private double magnif = 1.0F;
    private double transX = 0., transY = 0.;
    private int labelGenerator;
    AffineTransform transformation;
    private int pressX, pressY;
    boolean pressed = false;
    ArrayList<ShapeWrap> shapes;
    Mode workingMode;
    boolean changeMade;
    ArrayList<Point2D.Double> editedPoints;
    Shape editedShape;
    int editedShapeID = 0;
    private Model _all_points;
    private Object selection = null;
    private Color currentColor = Color.BLACK;
    private IFormatter formatter;
    private String filename;
	private boolean autoclosure = false;

    @Override
    public void Reload() {
        this.Load(filename);
    }

    enum Mode {

        VIEW, CREATE
    };

    public PlanePanel() {
        addMouseListener(this);
        addMouseMotionListener(this);
        addMouseWheelListener(this);
        shapes = new ArrayList<ShapeWrap>();
        shapes.ensureCapacity(1000);

        workingMode = Mode.VIEW;

        editedShape = null;
        editedPoints = new ArrayList<Point2D.Double>();
        changeMade = false;

        _all_points = new Model();
        transformation = new AffineTransform();
        ResetView();
    }

    private Shape GenerateShapeFromPoints(List<Point2D.Double> points) {
        if (points.size() == 0) {
            return null;
        }
        if (points.size() <= 2) {
            Line2D.Double line = new Line2D.Double();
            Point2D p1 = transformation.transform(points.get(0),null);
            Point2D p2 = transformation.transform(points.get(points.size() - 1),null);
            
            line.x1 = p1.getX();
            line.y1 = p1.getY();

            line.x2 = p2.getX();
            line.y2 = p2.getY();

            return line;
        } else {
            GeneralPath path = null;
            for (Point2D.Double a : points) {
            	Point2D p = transformation.transform(a,null);
                if (path == null) {
                    path = new GeneralPath();
                    path.moveTo(p.getX(), p.getY());
                } else {
                    path.lineTo(p.getX(), p.getY());
                }
            }
            return path;
        }
    }

    private ShapeWrap GenerateWrapFromPoints(List<Point2D.Double> points) {
        if (points.size() == 0 || points.size() == 1) {
            return null;
        } else if (points.size() == 2) {
            return new LineWrap(GenerateShapeFromPoints(points));
        } else {
            return new ShapeWrap(GenerateShapeFromPoints(points));
        }
    }

    synchronized public List<Point2D.Double> getPoints() {
        LinkedList<Point2D.Double> ret = new LinkedList<Point2D.Double>();
        for (PointModel model : _all_points.points) {
            ret.add(model.point);
        }
        return ret;
    }
    
    private void recalcTransform(){
    	AffineTransform translation = new AffineTransform();
        translation.translate(this.getWidth() / 2, this.getHeight() / 2);
        translation.concatenate(AffineTransform.getScaleInstance(magnif, magnif));
        translation.translate(transX, transY);
//        translation.scale(1., -1.); //TODO Poprawic w innych miejscach
        transformation = translation;
    }

    @Override
    public void paintComponent(Graphics g) {

        regenerateShapes();
    	
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g;

        AffineTransform savedTransform = g2d.getTransform();

        recalcTransform();
        g2d.transform(transformation);      

        g2d.setTransform(savedTransform);
        
        DrawShapes(g2d);
        
        if (workingMode == Mode.CREATE) {
            if (changeMade) {
                editedShape = GenerateShapeFromPoints(editedPoints);
            }
            if (editedShape != null) {
                g2d.draw(editedShape);
            }
        }

        DrawPoints(g2d, transformation);
    }

    synchronized private void DrawShapes(Graphics2D g2d) {
        for (ShapeWrap sw : shapes) {
            sw.Draw(g2d);
        }
    }

    synchronized private void DrawPoints(Graphics2D g2d, AffineTransform at) {
        /* *x/
         synchronized(_all_points){
         /* */
        for (PointModel point : _all_points.points) {
            point.Draw(g2d, at);
        }
        /* *x/
         _all_points.notifyAll();
         }
         /* */
    }

    @Override
    public void mouseMoved(MouseEvent e) {
    }

    synchronized Object HandleCollisions(MouseEvent e) {
        for (ShapeWrap sw : shapes) {
            if (sw.Collision(GetTransformed(e.getPoint()))) {
                System.out.print("clicked ");
                if (sw.label.equals("")) {
                    System.out.println("unknown label");
                } else {
                    System.out.println(sw.label);
                }

                return sw;
            }
        }
        for (PointModel pm : _all_points.points) {

            if (Math.abs(pm.getVisibleX(transformation) - e.getPoint().x) <= PointModel.pointW) {
                if (Math.abs(pm.getVisibleY(transformation) - e.getPoint().y) <= PointModel.pointW) {
                    System.out.println("clicked " + pm.label);
                    return pm;
                }
            }
        }

        return null;
    }

    synchronized void AddPointToEditedList(Point2D p) {
        editedPoints.add(new Point2D.Double((double) p.getX(), (double) p.getY()));
        changeMade = true;
        _all_points.points.add(new PointModel(p, this.currentColor,
                new Integer(this.labelGenerator++).toString(),
                this.editedShapeID));
        repaint();
    }

    synchronized void RemoveLastPointFromList() {
        if (editedPoints.isEmpty()) {
            return;
        }
        editedPoints.remove(editedPoints.size() - 1);
        changeMade = true;
        repaint();
    }

    synchronized public void CloseEditedShape() {
        Shape s = GenerateShapeFromPoints(editedPoints);
        editedPoints = new ArrayList<Point2D.Double>();

        if (s instanceof Line2D.Double) {
            LineWrap lw = new LineWrap(s);
            lw.color = this.currentColor;
            shapes.add(lw);
        } else if (s instanceof GeneralPath) {
            ((GeneralPath) s).closePath();
            ShapeWrap sw = new ShapeWrap(s);
            sw.color = this.currentColor;
            shapes.add(sw);
        }

        this.editedShapeID++;
        repaint();
    }

    Point2D GetTransformed(Point mouseClick) {
        Point2D.Double coords = new Point2D.Double(mouseClick.x, mouseClick.y);
        try {
            return transformation.createInverse().transform(coords, null);
        } catch (NoninvertibleTransformException e) {
            e.printStackTrace();
        }
        return coords;
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        if (workingMode == Mode.CREATE) {
            if (SwingUtilities.isLeftMouseButton(e)) {
                AddPointToEditedList(GetTransformed(e.getPoint()));
                if(autoclosure){
                	CloseEditedShape();
                }
            } else if (SwingUtilities.isRightMouseButton(e) && e.isAltDown()) {
                RemoveLastPointFromList();
            } else if (SwingUtilities.isRightMouseButton(e)) {
                CloseEditedShape();
                workingMode = Mode.VIEW;
            }
        } else if (workingMode == Mode.VIEW) {
            if (HandleCollisions(e) != null) {
            }
        }
    }

    @Override
    public void mousePressed(MouseEvent e) {
        Object collider = HandleCollisions(e);
        if (SwingUtilities.isLeftMouseButton(e)) {
            pressX = e.getPoint().x;
            pressY = e.getPoint().y;
            pressed = true;
        }
        this.selection = collider;
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        movement(e);
        if (pressed) {
            pressX = e.getPoint().x;
            pressY = e.getPoint().y;
        }
    }

    private void movement(MouseEvent e) {
        double dx = (double) (e.getPoint().x - pressX) / magnif;
        double dy = (double) (e.getPoint().y - pressY) / magnif;
        if (pressed && (selection == null)) {
            transX += dx;
            transY += dy;
        } else if (selection != null) {
            if (selection instanceof PointModel) {
                PointModel moved = (PointModel) selection;
                moved.point.x += dx;
                moved.point.y += dy;
                regenerateShapes();
            } else if (selection instanceof ShapeWrap) {
                ShapeWrap moved = (ShapeWrap) selection;
                int num = this.shapes.indexOf(moved);
                for (PointModel pm : _all_points.points) {
                    if (pm.shape == num) {
                        pm.point.x += dx;
                        pm.point.y += dy;
                    }
                }
                regenerateShapes();
            }
        }
        repaint();
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        movement(e);
        pressed = false;
        selection = null;
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        // TODO Auto-generated method stub
    }

    @Override
    public void mouseExited(MouseEvent e) {
        // TODO Auto-generated method stub
    }

    @Override
    public void SetColor(Color c) {
        this.currentColor = c;
    }

    @Override
    public void Save(String filename) {
        try {
            formatter.saveAll(new PrintStream(new File(filename)), _all_points);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    synchronized private void regenerateShapes() {
        int num = -1;
        if (selection != null && selection instanceof ShapeWrap) {
            num = this.shapes.indexOf(selection);
        }

        //latanie dziury - potrzebna refaktoryzacja

        Map<Integer, List<PointModel>> map = new HashMap<Integer, List<PointModel>>();
        this.shapes.clear();
        for (PointModel p : _all_points.points) {
            List<PointModel> shape = null;
            if (p != null) {
                shape = map.get(p.shape);
            }
            if (shape == null) {
                shape = new ArrayList<PointModel>();
                map.put(p.shape, shape);
            }
            shape.add(p);
        }
        for (List<PointModel> shape : map.values()) {
            List<Double> points = new ArrayList<Double>();
            for (PointModel pm : shape) {
                points.add(pm.point);
            }
            ShapeWrap sh = GenerateWrapFromPoints(points);
            if (sh != null) {
                sh.color = shape.get(0).color;
                this.shapes.add(sh);
            }
        }
        if (num > -1 && shapes.size() > num) {
            selection = shapes.get(num);
        } else {
            selection = null;
        }
        java.util.Collections.sort(this.shapes, new Comparator<model.ShapeWrap>() {
            @Override
            public int compare(ShapeWrap arg0, ShapeWrap arg1) {
                return arg0.GetPoints().length - arg1.GetPoints().length;
            }
        });
    }

    @Override
    public void Load(String filename) {
        this.filename = filename;
        try {
            _all_points = formatter.loadAll(new FileInputStream(filename));
            regenerateShapes();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void SetFormatter(IFormatter formatter) {
        this.formatter = formatter;
    }

    @Override
    public void mouseWheelMoved(MouseWheelEvent e) {
        if (SwingUtilities.isLeftMouseButton(e)) {
            magnif = magnif * (1.f + e.getWheelRotation() * 0.2);
        }
        repaint();
    }

    @Override
    public void ResetView() {
//		transX = this.getWidth()/2;
//		transY = this.getHeight()/2;
        transX = 0.0;
        transY = 0.0;
        magnif = 1.f;
        repaint();
    }

    @Override
    synchronized public void AddPoint() {
        // TODO Auto-generated method stub
        if (workingMode == Mode.VIEW) {
            workingMode = Mode.CREATE;
        }
    }

    @Override
    public void SetZoom(int value) {
        magnif = Math.exp((double) (value) / 8);
        recalcTransform();
        repaint();
    }

    @Override
    public void Refresh(Model m) {
        final Model mod = m;
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                PlanePanel.this._all_points = mod;
                repaint();
            }
        });
    }

    @Override
    public Model GetModel() {
        return this._all_points;
    }

    synchronized public void AddShapeWrap(ShapeWrap e) {
        shapes.add(e);
    }

    synchronized public void RemoveShapeWrap(ShapeWrap e) {
        shapes.remove(e);
    }

	@Override
	public void cleanup() {
		this.Refresh(new Model());
	}

	@Override
	public void setAutoClosure(boolean a) {
		this.autoclosure = a;
	}
}
