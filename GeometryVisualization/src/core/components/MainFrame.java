package core.components;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Map;
import java.util.logging.Logger;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSpinner;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

import core.figures.GFigure;
import core.io.SimulationParser;
import core.simulation.SimStep;
import core.simulation.Simulator;

public class MainFrame extends JFrame {

	private static Logger LOGGER = Logger.getLogger(MainFrame.class.getName());

	private JPanel contentPane;
	private Simulator simulator = new Simulator();
	private VisualizationGui visualizationGui;
	private JLabel lblSimStep;
	private JLabel lblMaxStep;
	private File simulationFile;

	JSpinner simStepSpinner;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					MainFrame frame = new MainFrame();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	private void loadSimulationFromFile(File file) {
		try {
			List<SimStep> simulationList = new SimulationParser().parse(file);
			if (simulationList != null && !simulationList.isEmpty()) {
				simulator.loadSimultionList(simulationList);
				visualizationGui
						.loadNewGeometry(simulator.getInitialGeometry());
				lblMaxStep.setText(String.valueOf(simulationList.size() - 1));
			}
		} catch (IOException exc) {
			LOGGER.severe("IO Exception when reading file.");
		}
	}

	/**
	 * Create the frame.
	 */
	public MainFrame() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 756, 500);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);

		JMenuBar menuBar = new JMenuBar();

		JMenu popupMenu = new JMenu("File");
		menuBar.add(popupMenu);

		JMenuItem mntmOpen = new JMenuItem("Open");
		popupMenu.add(mntmOpen);
		mntmOpen.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				JFileChooser fileChooser = new JFileChooser();
				int returnVal = fileChooser.showOpenDialog(contentPane);

				if (returnVal == JFileChooser.APPROVE_OPTION) {
					simulationFile = fileChooser.getSelectedFile();
					loadSimulationFromFile(simulationFile);
				}
			}
		});

		JMenuItem mntmReload = new JMenuItem("Reload");
		popupMenu.add(mntmReload);
		mntmReload.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				loadSimulationFromFile(simulationFile);
			}
		});

		JPanel mainPanel = new JPanel();
		mainPanel.setPreferredSize(new Dimension(1000, 1000));
		GridBagLayout gbl_mainPanel = new GridBagLayout();
		gbl_mainPanel.columnWidths = new int[] { 772, 0 };
		gbl_mainPanel.rowHeights = new int[] { 406, 0, 0 };
		gbl_mainPanel.columnWeights = new double[] { 1.0, Double.MIN_VALUE };
		gbl_mainPanel.rowWeights = new double[] { 1.0, 1.0, Double.MIN_VALUE };
		mainPanel.setLayout(gbl_mainPanel);

		visualizationGui = new VisualizationGui();
		GridBagConstraints gbc_visualizationGui = new GridBagConstraints();
		gbc_visualizationGui.weighty = 1.0;
		gbc_visualizationGui.insets = new Insets(0, 0, 5, 0);
		gbc_visualizationGui.fill = GridBagConstraints.BOTH;
		gbc_visualizationGui.gridx = 0;
		gbc_visualizationGui.gridy = 0;
		mainPanel.add(visualizationGui, gbc_visualizationGui);

		JScrollPane simFlowPane = new JScrollPane();
		simFlowPane.setAlignmentY(Component.BOTTOM_ALIGNMENT);
		simFlowPane.setMaximumSize(new Dimension(32767, 80));
		simFlowPane.setMinimumSize(new Dimension(22, 60));

		JPanel simFlowPanel = new JPanel();
		simFlowPanel.setMaximumSize(new Dimension(32767, 40));
		simFlowPane.setViewportView(simFlowPanel);
		GridBagLayout gbl_simFlowPanel = new GridBagLayout();
		gbl_simFlowPanel.columnWidths = new int[] { 307, 47, 127, 0 };
		gbl_simFlowPanel.rowHeights = new int[] { 33, 0, 0 };
		gbl_simFlowPanel.columnWeights = new double[] { 0.0, 0.0, 0.0,
				Double.MIN_VALUE };
		gbl_simFlowPanel.rowWeights = new double[] { 0.0, 0.0, Double.MIN_VALUE };
		simFlowPanel.setLayout(gbl_simFlowPanel);

		JPanel simButtonsPanel = new JPanel();
		GridBagConstraints gbc_simButtonsPanel = new GridBagConstraints();
		gbc_simButtonsPanel.anchor = GridBagConstraints.NORTHWEST;
		gbc_simButtonsPanel.insets = new Insets(0, 0, 5, 5);
		gbc_simButtonsPanel.gridx = 0;
		gbc_simButtonsPanel.gridy = 0;
		simFlowPanel.add(simButtonsPanel, gbc_simButtonsPanel);

		JButton button = new JButton("Prev");
		button.setVerticalAlignment(SwingConstants.BOTTOM);
		button.setHorizontalAlignment(SwingConstants.LEFT);
		simButtonsPanel.add(button);

		JButton button_1 = new JButton("Next");
		button_1.setVerticalAlignment(SwingConstants.BOTTOM);
		button_1.setHorizontalAlignment(SwingConstants.LEFT);
		button_1.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				simulator.nextStepUpdate(visualizationGui.getDrawingPanel()
						.getFiguresMap());
				lblSimStep.setText("Sim step: " + simulator.getStep());
				visualizationGui.getDrawingPanel().repaint();
			}
		});
		simButtonsPanel.add(button_1);

		JButton button_2 = new JButton("Run");
		button_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				for (int i = simulator.getStep(); i < simulator.maxStep(); ++i) {
					simulator.nextStepUpdate(visualizationGui.getDrawingPanel()
							.getFiguresMap());
				}
				lblSimStep.setText("Sim step: " + simulator.getStep());
				visualizationGui.getDrawingPanel().repaint();
			}
		});
		button_2.setVerticalAlignment(SwingConstants.BOTTOM);
		button_2.setHorizontalAlignment(SwingConstants.LEFT);
		simButtonsPanel.add(button_2);

		JButton button_3 = new JButton("Stop");
		button_3.setVerticalAlignment(SwingConstants.BOTTOM);
		button_3.setHorizontalAlignment(SwingConstants.LEFT);
		simButtonsPanel.add(button_3);

		JButton button_4 = new JButton("Reset");
		button_4.setVerticalAlignment(SwingConstants.BOTTOM);
		button_4.setHorizontalAlignment(SwingConstants.LEFT);
		button_4.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				Map<Integer, GFigure> map = simulator.getInitialGeometry();
				if (map != null) {
					visualizationGui.loadNewGeometry(map);
					visualizationGui.getDrawingPanel().repaint();
					lblSimStep.setText("Sim step: " + simulator.getStep());
				}
			}
		});
		simButtonsPanel.add(button_4);

		JPanel panel = new JPanel();
		GridBagConstraints gbc_panel = new GridBagConstraints();
		gbc_panel.insets = new Insets(0, 0, 5, 0);
		gbc_panel.anchor = GridBagConstraints.NORTHWEST;
		gbc_panel.gridx = 2;
		gbc_panel.gridy = 0;
		simFlowPanel.add(panel, gbc_panel);

		JButton btnGoTo = new JButton("Go to step");
		btnGoTo.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				int stepIndex = (Integer) simStepSpinner.getValue();
				if (stepIndex < 0 || stepIndex > simulator.maxStep()
						|| stepIndex == simulator.getStep()) {
					return;
				}
				if (stepIndex < simulator.getStep()) {
					simulator.setStep(0);
					visualizationGui.loadNewGeometry(simulator
							.getInitialGeometry());
				}
				for (int i = simulator.getStep(); i < stepIndex; ++i) {
					simulator.nextStepUpdate(visualizationGui.getDrawingPanel()
							.getFiguresMap());
				}
				lblSimStep.setText("Sim step: " + simulator.getStep());
				visualizationGui.getDrawingPanel().repaint();
			}
		});
		panel.add(btnGoTo);

		simStepSpinner = new JSpinner();
		simStepSpinner.setPreferredSize(new Dimension(50, 20));
		panel.add(simStepSpinner);

		lblSimStep = new JLabel("Sim step: ");
		GridBagConstraints gbc_lblSimStep = new GridBagConstraints();
		gbc_lblSimStep.anchor = GridBagConstraints.WEST;
		gbc_lblSimStep.insets = new Insets(0, 0, 0, 5);
		gbc_lblSimStep.gridx = 0;
		gbc_lblSimStep.gridy = 1;
		simFlowPanel.add(lblSimStep, gbc_lblSimStep);

		lblMaxStep = new JLabel("Max step:");
		lblMaxStep.setHorizontalAlignment(SwingConstants.LEFT);
		GridBagConstraints gbc_lblMaxStep = new GridBagConstraints();
		gbc_lblMaxStep.anchor = GridBagConstraints.WEST;
		gbc_lblMaxStep.gridx = 2;
		gbc_lblMaxStep.gridy = 1;
		simFlowPanel.add(lblMaxStep, gbc_lblMaxStep);
		contentPane.setLayout(new BorderLayout(0, 0));
		contentPane.add(menuBar, BorderLayout.NORTH);
		contentPane.add(mainPanel, BorderLayout.CENTER);
		contentPane.add(simFlowPane, BorderLayout.SOUTH);
	}
}
