package view;
import java.awt.BorderLayout;
import java.awt.geom.Point2D;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;

import model.GHelper;
//import model.Graham;
//import model.Jarvis;
import formatter.csv.CSVFormatter;


public class MainWindow extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = -3880026026104218593L;
	
	PlanePanel plane;

	private ToolBoxPanel toolbox;

	private AlgControlPanel algpanel;
	
	public MainWindow(String[] args)
	{
		setLayout(new BorderLayout());
		plane = new PlanePanel();
		plane.SetFormatter(new CSVFormatter());
		
		toolbox = new ToolBoxPanel();
		toolbox.setController(plane);
		add(plane, BorderLayout.CENTER);
		add(toolbox, BorderLayout.EAST);
		
		setTitle("Geometry");
		setSize(1024, 768);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		InputStream input = System.in;
		if(args.length == 1){
			try {
				input = new FileInputStream(args[0]);
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		}
		Watcher w = new Watcher(plane, new CSVFormatter(), input);
		Thread t = new Thread(w);
		
		algpanel = new AlgControlPanel(w); 
				
		add(algpanel, BorderLayout.WEST);
		t.start();
                plane.Load("D:\\Repo\\Studia\\SEM7\\geo_obl\\project\\QuadTree\\sim_out.txt");
	}

	public static void main(final String[] args)
	{
		SwingUtilities.invokeLater(new Runnable() {
            public void run() {
            	MainWindow app = new MainWindow(args);
                app.setVisible(true);
            }
        });
	}
}
