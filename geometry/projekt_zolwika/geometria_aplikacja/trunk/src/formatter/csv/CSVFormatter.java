package formatter.csv;

import java.awt.Color;
import java.awt.geom.Point2D;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.Scanner;

import model.Model;
import model.PointModel;
import formatter.IFormatter;

public class CSVFormatter implements IFormatter {
	
	Scanner scan = null;

	PointModel readPoint(){
		String[] items = scan.nextLine().split(",");
		double x,y;
		if (items.length<5){
			return null;
		}
		x = Double.parseDouble(items[0].trim());
		y = Double.parseDouble(items[1].trim());
		Color color = Color.decode("0x"+items[2].trim());
		String label = items[3].trim();
		int shape = Integer.parseInt(items[4].trim());
		PointModel m = new PointModel(new Point2D.Double(x, y),color,label,shape);
		return m;
	}
	
	String savePoint(PointModel m){
		StringBuilder builder = new StringBuilder();
		builder.append(m.point.x).append(",");
		builder.append(m.point.y).append(",");
		String rgb = Integer.toHexString(m.color.getRGB());
		rgb = rgb.substring(2, rgb.length());
		builder.append(rgb).append(",");
		builder.append(m.label).append(",");
		builder.append(m.shape);
		return builder.toString();
	}
	
	@Override
	public Model loadAll(InputStream in) {
		if(scan != null)
			scan.close();
		scan = new Scanner(in);
		Model m = new Model();
		while(scan.hasNext()){
			PointModel p = readPoint();
			if(p != null)
				m.points.add(p);
		}
		try {
			in.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return m;
	}

	@Override
	public void saveAll(PrintStream out, Model points) {
		for(PointModel point: points.points){
			out.println(savePoint(point));
		}
	}

	@Override
	public Model getNextStep(InputStream in, Model current) {
		if(scan == null)
			scan = new Scanner(in);
		if(!scan.hasNext()){
			scan.close();
			scan = null;
			return current;
		}
		PointModel newPoint = null;
		while(newPoint==null || newPoint.color.equals(Color.black)){
			newPoint = readPoint();
			if(newPoint==null){
				return current;
			}
			boolean change = false;
			for(PointModel oldPoint : current.points){
				if(newPoint.equals(oldPoint)){
					oldPoint.color = newPoint.color;
					oldPoint.label = newPoint.label;
					change = true;
				}
			}
			if(!change && newPoint != null){
				current.points.add(newPoint);
			}
		}
		//scan.close();
		return current;
	}

}
