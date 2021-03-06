package view;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class AlgControlPanel extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 2032431186092259597L;
	private JButton start;
	private JButton stop;
	private JButton read;
	private JSpinner time;
	private IAlgorithmController control;
	private final JButton next;
	private final JButton reload;
	private final JButton prev;

	public AlgControlPanel(IAlgorithmController controller) {
		this.control = controller;
		this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
		JPanel action = new JPanel();
		action.setLayout(new GridLayout(13,1));
		start = new JButton("Start");
		stop = new JButton("Stop");
		next = new JButton("Nastepny");
		prev = new JButton("Poprzedni");
		reload = new JButton("Przeladuj");
		read = new JButton("Wczytaj");
		time = new JSpinner();
		time.setValue(new Integer(1000));
		action.add(new JLabel("Akcja"));
		action.add(stop);
		action.add(start);
		action.add(next);
		action.add(prev);
		action.add(reload);
		action.add(read);
		action.add(time);
		
		this.add(action);
		
		setActions();
	}

	private void setActions() {
		start.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				control.start();
			}
		});
		stop.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				control.stop();
			}
		});
		read.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				JFileChooser chooser = new JFileChooser();
				int result = chooser.showOpenDialog(AlgControlPanel.this);
				if(result == JFileChooser.APPROVE_OPTION){
					control.setFilename(chooser.getSelectedFile().getPath());
				}
			}
		});
		time.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent arg0) {
				control.setTimeInterval((Integer) time.getValue());
			}
		});
		reload.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ce) {
				control.reload();
			}
		});
		next.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ce) {
				control.next();
			}
		});
		prev.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ce) {
				control.prev();
			}
		});
	}
}
