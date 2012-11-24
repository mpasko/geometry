package core.components;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.util.Map;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSeparator;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.border.LineBorder;

import core.drawing.DrawingPanel;
import core.figures.GFigure;

public class VisualizationGui extends JPanel {

	private DrawingPanel drawingPanel;
	private JTextField xAxisSeparatorGaps;
	private JTextField yAxisSeparatorGaps;
	private JTextField oxMaxTextField;
	private JTextField oyMaxTextField;
	private JTextField oxMinTextField;
	private JTextField oyMinTextField;
	private JTextField txtBoxGridXSpacing;
	private JTextField textBoxGridYSpacing;

	public VisualizationGui() {

		super();

		GridBagLayout gbl_panel = new GridBagLayout();
		gbl_panel.columnWidths = new int[] { 500, 180 };
		gbl_panel.rowHeights = new int[] { 307 };
		gbl_panel.columnWeights = new double[] { 0.0 };
		gbl_panel.rowWeights = new double[] { 0.0 };
		this.setLayout(gbl_panel);

		drawingPanel = new DrawingPanel();
		FlowLayout flowLayout = (FlowLayout) drawingPanel.getLayout();
		flowLayout.setHgap(0);
		flowLayout.setVgap(0);
		drawingPanel.addMouseWheelListener(new MouseWheelListener() {
			public void mouseWheelMoved(MouseWheelEvent e) {
				drawingPanel.zoom(e.getWheelRotation(), e.getPoint());
			}
		});
		drawingPanel.setPreferredSize(new Dimension(32767, 32767));
		drawingPanel.setBorder(new LineBorder(new Color(0, 0, 0)));
		GridBagConstraints gbc_drawingPanel = new GridBagConstraints();
		gbc_drawingPanel.weighty = 1.0;
		gbc_drawingPanel.weightx = 1.0;
		gbc_drawingPanel.insets = new Insets(0, 0, 0, 5);
		gbc_drawingPanel.fill = GridBagConstraints.BOTH;
		gbc_drawingPanel.gridx = 0;
		gbc_drawingPanel.gridy = 0;
		this.add(drawingPanel, gbc_drawingPanel);

		Box verticalBox = Box.createVerticalBox();
		verticalBox.setMinimumSize(new Dimension(80, 100));
		verticalBox.setMaximumSize(new Dimension(200, 3000));
		verticalBox.setPreferredSize(new Dimension(250, 100));
		GridBagConstraints gbc_verticalBox = new GridBagConstraints();
		gbc_verticalBox.anchor = GridBagConstraints.WEST;
		gbc_verticalBox.fill = GridBagConstraints.BOTH;
		gbc_verticalBox.gridx = 1;
		gbc_verticalBox.gridy = 0;
		this.add(verticalBox, gbc_verticalBox);

		JPanel plotPanel = new JPanel();
		plotPanel.setPreferredSize(new Dimension(180, 100));
		plotPanel.setMaximumSize(new Dimension(200, 32767));
		verticalBox.add(plotPanel);
		GridBagLayout gbl_plotPanel = new GridBagLayout();
		gbl_plotPanel.columnWidths = new int[] { 98, 0 };
		gbl_plotPanel.rowHeights = new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		gbl_plotPanel.columnWeights = new double[] { 1.0, Double.MIN_VALUE };
		gbl_plotPanel.rowWeights = new double[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
				0.0, 0.0, 1.0, Double.MIN_VALUE };
		plotPanel.setLayout(gbl_plotPanel);

		final JCheckBox showAxesCheckbox = new JCheckBox("Show axes");
		showAxesCheckbox.setSelected(drawingPanel.getOxAxis().isRendered()
				&& drawingPanel.getOyAxis().isRendered());
		showAxesCheckbox.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				drawingPanel.getOxAxis().setRendered(
						showAxesCheckbox.isSelected());
				drawingPanel.getOyAxis().setRendered(
						showAxesCheckbox.isSelected());
				drawingPanel.repaint();
			}
		});

		showAxesCheckbox.setHorizontalAlignment(SwingConstants.LEFT);
		GridBagConstraints gbc_checkBox_1 = new GridBagConstraints();
		gbc_checkBox_1.anchor = GridBagConstraints.WEST;
		gbc_checkBox_1.insets = new Insets(10, 0, 10, 0);
		gbc_checkBox_1.gridx = 0;
		gbc_checkBox_1.gridy = 0;
		plotPanel.add(showAxesCheckbox, gbc_checkBox_1);

		final JCheckBox showAxesNumbersCheckbox = new JCheckBox(
				"Show axes numbers");
		showAxesNumbersCheckbox.setSelected(drawingPanel.getOxAxis()
				.isShowNumbers() && drawingPanel.getOyAxis().isShowNumbers());
		showAxesNumbersCheckbox.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				drawingPanel.getOxAxis().setShowNumbers(
						showAxesNumbersCheckbox.isSelected());
				drawingPanel.getOyAxis().setShowNumbers(
						showAxesNumbersCheckbox.isSelected());
				drawingPanel.repaint();
			}
		});
		GridBagConstraints gbc_checkBox_2 = new GridBagConstraints();
		gbc_checkBox_2.insets = new Insets(0, 30, 5, 0);
		gbc_checkBox_2.anchor = GridBagConstraints.WEST;
		gbc_checkBox_2.gridx = 0;
		gbc_checkBox_2.gridy = 1;
		plotPanel.add(showAxesNumbersCheckbox, gbc_checkBox_2);
		showAxesNumbersCheckbox.setHorizontalAlignment(SwingConstants.LEFT);

		JPanel plotSettingsPanel = new JPanel();
		GridBagConstraints gbc_plotSettingsPanel = new GridBagConstraints();
		gbc_plotSettingsPanel.insets = new Insets(0, 0, 5, 0);
		gbc_plotSettingsPanel.gridx = 0;
		gbc_plotSettingsPanel.gridy = 2;
		plotPanel.add(plotSettingsPanel, gbc_plotSettingsPanel);
		GridBagLayout gbl_panel_4 = new GridBagLayout();
		gbl_panel_4.columnWidths = new int[] { 81, 77, 0 };
		gbl_panel_4.rowHeights = new int[] { 0, 0, 0 };
		gbl_panel_4.columnWeights = new double[] { 0.0, 1.0, Double.MIN_VALUE };
		gbl_panel_4.rowWeights = new double[] { 0.0, 0.0, Double.MIN_VALUE };
		plotSettingsPanel.setLayout(gbl_panel_4);

		xAxisSeparatorGaps = new JTextField();
		xAxisSeparatorGaps.setText(Integer.toString(drawingPanel.getOxAxis()
				.getSeparatorsNumber()));
		xAxisSeparatorGaps.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent e) {
				try {
					int value = Integer.parseInt(xAxisSeparatorGaps.getText());
					if (value >= 0) {
						drawingPanel.getOxAxis().setSeparatorsNumber(value);
						drawingPanel.repaint();
						return;
					}
				} catch (NumberFormatException excp) {
				}
				xAxisSeparatorGaps.setText(Integer.toString(drawingPanel
						.getOxAxis().getSeparatorsNumber()));
				return;
			}
		});
		xAxisSeparatorGaps.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					int value = Integer.parseInt(xAxisSeparatorGaps.getText());
					if (value >= 0) {
						drawingPanel.getOxAxis().setSeparatorsNumber(value);
						drawingPanel.repaint();
						return;
					}
				} catch (NumberFormatException excp) {
				}
				xAxisSeparatorGaps.setText(Integer.toString(drawingPanel
						.getOxAxis().getSeparatorsNumber()));
				return;
			}
		});

		JLabel label_2 = new JLabel("X spacing");
		GridBagConstraints gbc_label_2 = new GridBagConstraints();
		gbc_label_2.anchor = GridBagConstraints.WEST;
		gbc_label_2.insets = new Insets(0, 20, 5, 5);
		gbc_label_2.gridx = 0;
		gbc_label_2.gridy = 0;
		plotSettingsPanel.add(label_2, gbc_label_2);
		label_2.setHorizontalAlignment(SwingConstants.LEFT);
		xAxisSeparatorGaps.setPreferredSize(new Dimension(35, 20));
		xAxisSeparatorGaps.setMaximumSize(new Dimension(35, 2147483647));
		xAxisSeparatorGaps.setColumns(5);
		GridBagConstraints gbc_xAxisSeparatorGaps = new GridBagConstraints();
		gbc_xAxisSeparatorGaps.anchor = GridBagConstraints.WEST;
		gbc_xAxisSeparatorGaps.insets = new Insets(0, 0, 5, 0);
		gbc_xAxisSeparatorGaps.gridx = 1;
		gbc_xAxisSeparatorGaps.gridy = 0;
		plotSettingsPanel.add(xAxisSeparatorGaps, gbc_xAxisSeparatorGaps);

		JLabel label_3 = new JLabel("Y spacing");
		label_3.setHorizontalAlignment(SwingConstants.LEFT);
		GridBagConstraints gbc_label_3 = new GridBagConstraints();
		gbc_label_3.anchor = GridBagConstraints.WEST;
		gbc_label_3.insets = new Insets(0, 20, 0, 5);
		gbc_label_3.gridx = 0;
		gbc_label_3.gridy = 1;
		plotSettingsPanel.add(label_3, gbc_label_3);

		yAxisSeparatorGaps = new JTextField();
		yAxisSeparatorGaps.setText(Integer.toString(drawingPanel.getOyAxis()
				.getSeparatorsNumber()));
		yAxisSeparatorGaps.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent e) {
				try {
					int value = Integer.parseInt(yAxisSeparatorGaps.getText());
					if (value >= 0) {
						drawingPanel.getOyAxis().setSeparatorsNumber(value);
						drawingPanel.repaint();
						return;
					}
				} catch (NumberFormatException excp) {
				}
				yAxisSeparatorGaps.setText(Integer.toString(drawingPanel
						.getOyAxis().getSeparatorsNumber()));
				return;
			}
		});
		yAxisSeparatorGaps.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					int value = Integer.parseInt(yAxisSeparatorGaps.getText());
					if (value >= 0) {
						drawingPanel.getOyAxis().setSeparatorsNumber(value);
						drawingPanel.repaint();
						return;
					}
				} catch (NumberFormatException excp) {
				}
				yAxisSeparatorGaps.setText(Integer.toString(drawingPanel
						.getOyAxis().getSeparatorsNumber()));
				return;
			}
		});
		yAxisSeparatorGaps.setPreferredSize(new Dimension(35, 20));
		yAxisSeparatorGaps.setMaximumSize(new Dimension(35, 2147483647));
		yAxisSeparatorGaps.setColumns(5);
		GridBagConstraints gbc_yAxisSeparatorGaps = new GridBagConstraints();
		gbc_yAxisSeparatorGaps.anchor = GridBagConstraints.WEST;
		gbc_yAxisSeparatorGaps.gridx = 1;
		gbc_yAxisSeparatorGaps.gridy = 1;
		plotSettingsPanel.add(yAxisSeparatorGaps, gbc_yAxisSeparatorGaps);

		JSeparator separator = new JSeparator();
		GridBagConstraints gbc_separator = new GridBagConstraints();
		gbc_separator.fill = GridBagConstraints.HORIZONTAL;
		gbc_separator.insets = new Insets(0, 0, 5, 0);
		gbc_separator.gridx = 0;
		gbc_separator.gridy = 3;
		plotPanel.add(separator, gbc_separator);

		JLabel lblAxesSpan = new JLabel("Set axes");
		lblAxesSpan.setFont(new Font("Tahoma", Font.BOLD, 11));
		GridBagConstraints gbc_lblAxesSpan = new GridBagConstraints();
		gbc_lblAxesSpan.anchor = GridBagConstraints.WEST;
		gbc_lblAxesSpan.insets = new Insets(0, 0, 5, 0);
		gbc_lblAxesSpan.gridx = 0;
		gbc_lblAxesSpan.gridy = 4;
		plotPanel.add(lblAxesSpan, gbc_lblAxesSpan);

		JPanel panel_1 = new JPanel();
		GridBagConstraints gbc_panel_1 = new GridBagConstraints();
		gbc_panel_1.insets = new Insets(0, 0, 5, 0);
		gbc_panel_1.fill = GridBagConstraints.BOTH;
		gbc_panel_1.gridx = 0;
		gbc_panel_1.gridy = 5;
		plotPanel.add(panel_1, gbc_panel_1);
		GridBagLayout gbl_panel_1 = new GridBagLayout();
		gbl_panel_1.columnWidths = new int[] { 0, 53, 43, 48, 0 };
		gbl_panel_1.rowHeights = new int[] { 0, 0, 0, 0 };
		gbl_panel_1.columnWeights = new double[] { 0.0, 1.0, 0.0, 0.0,
				Double.MIN_VALUE };
		gbl_panel_1.rowWeights = new double[] { 1.0, 0.0, 1.0, Double.MIN_VALUE };
		panel_1.setLayout(gbl_panel_1);

		JLabel lblOxMin = new JLabel("OX Min");
		GridBagConstraints gbc_lblOxMin = new GridBagConstraints();
		gbc_lblOxMin.anchor = GridBagConstraints.EAST;
		gbc_lblOxMin.insets = new Insets(0, 5, 5, 5);
		gbc_lblOxMin.gridx = 0;
		gbc_lblOxMin.gridy = 0;
		panel_1.add(lblOxMin, gbc_lblOxMin);

		oxMinTextField = new JTextField();
		GridBagConstraints gbc_oxMinTextField = new GridBagConstraints();
		gbc_oxMinTextField.insets = new Insets(0, 0, 5, 5);
		gbc_oxMinTextField.fill = GridBagConstraints.HORIZONTAL;
		gbc_oxMinTextField.gridx = 1;
		gbc_oxMinTextField.gridy = 0;
		panel_1.add(oxMinTextField, gbc_oxMinTextField);
		oxMinTextField.setColumns(10);

		JLabel lblOxMax = new JLabel("OX Max");
		GridBagConstraints gbc_lblOxMax = new GridBagConstraints();
		gbc_lblOxMax.anchor = GridBagConstraints.EAST;
		gbc_lblOxMax.insets = new Insets(0, 0, 5, 5);
		gbc_lblOxMax.gridx = 2;
		gbc_lblOxMax.gridy = 0;
		panel_1.add(lblOxMax, gbc_lblOxMax);

		oxMaxTextField = new JTextField();
		GridBagConstraints gbc_oxMaxTextField = new GridBagConstraints();
		gbc_oxMaxTextField.fill = GridBagConstraints.HORIZONTAL;
		gbc_oxMaxTextField.insets = new Insets(0, 0, 5, 0);
		gbc_oxMaxTextField.gridx = 3;
		gbc_oxMaxTextField.gridy = 0;
		panel_1.add(oxMaxTextField, gbc_oxMaxTextField);
		oxMaxTextField.setColumns(10);

		JLabel lblOyMin = new JLabel("OY Min");
		GridBagConstraints gbc_lblOyMin = new GridBagConstraints();
		gbc_lblOyMin.anchor = GridBagConstraints.EAST;
		gbc_lblOyMin.insets = new Insets(0, 5, 5, 5);
		gbc_lblOyMin.gridx = 0;
		gbc_lblOyMin.gridy = 1;
		panel_1.add(lblOyMin, gbc_lblOyMin);

		oyMinTextField = new JTextField();
		GridBagConstraints gbc_oyMinTextField = new GridBagConstraints();
		gbc_oyMinTextField.insets = new Insets(0, 0, 5, 5);
		gbc_oyMinTextField.fill = GridBagConstraints.HORIZONTAL;
		gbc_oyMinTextField.gridx = 1;
		gbc_oyMinTextField.gridy = 1;
		panel_1.add(oyMinTextField, gbc_oyMinTextField);
		oyMinTextField.setColumns(10);

		JLabel lblOyMax = new JLabel("OY Max");
		GridBagConstraints gbc_lblOyMax = new GridBagConstraints();
		gbc_lblOyMax.anchor = GridBagConstraints.EAST;
		gbc_lblOyMax.insets = new Insets(0, 0, 5, 5);
		gbc_lblOyMax.gridx = 2;
		gbc_lblOyMax.gridy = 1;
		panel_1.add(lblOyMax, gbc_lblOyMax);

		oyMaxTextField = new JTextField();
		GridBagConstraints gbc_OyMaxTextField = new GridBagConstraints();
		gbc_OyMaxTextField.insets = new Insets(0, 0, 5, 0);
		gbc_OyMaxTextField.fill = GridBagConstraints.HORIZONTAL;
		gbc_OyMaxTextField.gridx = 3;
		gbc_OyMaxTextField.gridy = 1;
		panel_1.add(oyMaxTextField, gbc_OyMaxTextField);
		oyMaxTextField.setColumns(10);

		JButton btnNewButton = new JButton("Set axes");
		GridBagConstraints gbc_btnNewButton = new GridBagConstraints();
		gbc_btnNewButton.anchor = GridBagConstraints.WEST;
		gbc_btnNewButton.insets = new Insets(0, 0, 5, 0);
		gbc_btnNewButton.gridx = 0;
		gbc_btnNewButton.gridy = 6;
		plotPanel.add(btnNewButton, gbc_btnNewButton);
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					double maxXValue = Double.parseDouble(oxMaxTextField
							.getText());
					double minXValue = Double.parseDouble(oxMinTextField
							.getText());
					double maxYValue = Double.parseDouble(oyMaxTextField
							.getText());
					double minYValue = Double.parseDouble(oyMinTextField
							.getText());
					if (maxXValue > minXValue && maxYValue > minYValue) {
						drawingPanel.getDrawingArea().setMinX(minXValue);
						drawingPanel.getDrawingArea().setMaxX(maxXValue);
						drawingPanel.getDrawingArea().setMinY(minYValue);
						drawingPanel.getDrawingArea().setMaxY(maxYValue);
						drawingPanel.repaint();
						return;
					}
				} catch (NumberFormatException excp) {
				}
			}
		});
		btnNewButton.setHorizontalAlignment(SwingConstants.LEFT);

		JSeparator separator_1 = new JSeparator();
		GridBagConstraints gbc_separator_1 = new GridBagConstraints();
		gbc_separator_1.fill = GridBagConstraints.HORIZONTAL;
		gbc_separator_1.insets = new Insets(0, 0, 5, 0);
		gbc_separator_1.gridx = 0;
		gbc_separator_1.gridy = 7;
		plotPanel.add(separator_1, gbc_separator_1);

		JPanel panel_3 = new JPanel();
		panel_3.setPreferredSize(new Dimension(180, 80));
		panel_3.setAlignmentY(0.0f);
		GridBagConstraints gbc_panel_3 = new GridBagConstraints();
		gbc_panel_3.fill = GridBagConstraints.BOTH;
		gbc_panel_3.gridx = 0;
		gbc_panel_3.gridy = 8;
		plotPanel.add(panel_3, gbc_panel_3);
		GridBagLayout gbl_panel_3 = new GridBagLayout();
		gbl_panel_3.columnWidths = new int[] { 74, 42, 0 };
		gbl_panel_3.rowHeights = new int[] { 0, 0, 0, 0 };
		gbl_panel_3.columnWeights = new double[] { 0.0, 0.0, Double.MIN_VALUE };
		gbl_panel_3.rowWeights = new double[] { 0.0, 0.0, 0.0, Double.MIN_VALUE };
		panel_3.setLayout(gbl_panel_3);

		final JCheckBox chkBoxShowGrid = new JCheckBox("Show grid");
		chkBoxShowGrid.setSelected(drawingPanel.getGrid().isRendered());
		chkBoxShowGrid.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				drawingPanel.getGrid().setRendered(chkBoxShowGrid.isSelected());
				drawingPanel.repaint();
			}
		});
		chkBoxShowGrid.setSelected(true);
		chkBoxShowGrid.setHorizontalAlignment(SwingConstants.LEFT);
		GridBagConstraints gbc_checkBox = new GridBagConstraints();
		gbc_checkBox.insets = new Insets(0, 0, 5, 5);
		gbc_checkBox.gridx = 0;
		gbc_checkBox.gridy = 0;
		panel_3.add(chkBoxShowGrid, gbc_checkBox);

		JLabel label = new JLabel("gridXSpacing");
		label.setHorizontalAlignment(SwingConstants.LEFT);
		GridBagConstraints gbc_label = new GridBagConstraints();
		gbc_label.anchor = GridBagConstraints.EAST;
		gbc_label.insets = new Insets(0, 0, 5, 5);
		gbc_label.gridx = 0;
		gbc_label.gridy = 1;
		panel_3.add(label, gbc_label);

		txtBoxGridXSpacing = new JTextField();
		txtBoxGridXSpacing.setText(Integer.toString(drawingPanel.getGrid()
				.getVerticalLinesNumber()));
		txtBoxGridXSpacing.setPreferredSize(new Dimension(35, 20));
		txtBoxGridXSpacing.setMaximumSize(new Dimension(35, 20));
		txtBoxGridXSpacing.setColumns(5);

		txtBoxGridXSpacing.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent e) {
				try {
					int value = Integer.parseInt(txtBoxGridXSpacing.getText());
					if (value >= 0) {
						drawingPanel.getGrid().setVerticalLinesNumber(value);
						drawingPanel.repaint();
						return;
					}
				} catch (NumberFormatException excp) {
				}
				txtBoxGridXSpacing.setText(Integer.toString(drawingPanel
						.getGrid().getVerticalLinesNumber()));
				return;
			}
		});
		txtBoxGridXSpacing.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					int value = Integer.parseInt(txtBoxGridXSpacing.getText());
					if (value >= 0) {
						drawingPanel.getGrid().setVerticalLinesNumber(value);
						drawingPanel.repaint();
						return;
					}
				} catch (NumberFormatException excp) {
				}
				txtBoxGridXSpacing.setText(Integer.toString(drawingPanel
						.getGrid().getVerticalLinesNumber()));
				return;
			}
		});

		GridBagConstraints gbc_textField_4 = new GridBagConstraints();
		gbc_textField_4.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField_4.anchor = GridBagConstraints.WEST;
		gbc_textField_4.insets = new Insets(0, 0, 5, 0);
		gbc_textField_4.gridx = 1;
		gbc_textField_4.gridy = 1;
		panel_3.add(txtBoxGridXSpacing, gbc_textField_4);

		JLabel label_1 = new JLabel("gridYSpacing");
		label_1.setHorizontalAlignment(SwingConstants.LEFT);
		GridBagConstraints gbc_label_1 = new GridBagConstraints();
		gbc_label_1.anchor = GridBagConstraints.EAST;
		gbc_label_1.insets = new Insets(0, 0, 0, 5);
		gbc_label_1.gridx = 0;
		gbc_label_1.gridy = 2;
		panel_3.add(label_1, gbc_label_1);

		textBoxGridYSpacing = new JTextField();
		textBoxGridYSpacing.setText("10");
		textBoxGridYSpacing.setPreferredSize(new Dimension(20, 20));
		textBoxGridYSpacing.setMaximumSize(new Dimension(20, 2147483647));
		textBoxGridYSpacing.setColumns(5);
		GridBagConstraints gbc_textField_5 = new GridBagConstraints();
		gbc_textField_5.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField_5.anchor = GridBagConstraints.WEST;
		gbc_textField_5.gridx = 1;
		gbc_textField_5.gridy = 2;
		panel_3.add(textBoxGridYSpacing, gbc_textField_5);

		textBoxGridYSpacing.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent e) {
				try {
					int value = Integer.parseInt(textBoxGridYSpacing.getText());
					if (value >= 0) {
						drawingPanel.getGrid().setHorizontalLinesNumber(value);
						drawingPanel.repaint();
						return;
					}
				} catch (NumberFormatException excp) {
				}
				textBoxGridYSpacing.setText(Integer.toString(drawingPanel
						.getGrid().getHorizontalLinesNumber()));
				return;
			}
		});
		textBoxGridYSpacing.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					int value = Integer.parseInt(textBoxGridYSpacing.getText());
					if (value >= 0) {
						drawingPanel.getGrid().setHorizontalLinesNumber(value);
						drawingPanel.repaint();
						return;
					}
				} catch (NumberFormatException excp) {
				}
				textBoxGridYSpacing.setText(Integer.toString(drawingPanel
						.getGrid().getHorizontalLinesNumber()));
				return;
			}
		});
	}

	public void loadNewGeometry(Map<Integer, GFigure> figuresMap) {
		drawingPanel.setFiguresMap(figuresMap);
		double maxX, minX, maxY, minY;
		drawingPanel.repaint();
	}

	public DrawingPanel getDrawingPanel() {
		return drawingPanel;
	}
}
