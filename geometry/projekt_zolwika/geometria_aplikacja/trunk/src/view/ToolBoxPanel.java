package view;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JColorChooser;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class ToolBoxPanel extends JPanel {

    /**
     *
     */
    private static final long serialVersionUID = -1824950985899816256L;
    private JButton save;
    private JButton open;
    private JButton generate;
    private JButton addPoint;
    private JButton movePoint;
    private JButton closeShape;
    private JButton setColour;
    private JButton resetPosition;
    private IController controller;
    private JSpinner zoom;
	private JButton clean;
	private JCheckBox autoclos;

    public ToolBoxPanel() {
        this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        JPanel file = new JPanel();
        file.setLayout(new GridLayout(6, 1));
        save = new JButton("Zapisz");
        open = new JButton("Otworz");
        generate = new JButton("Przeladuj");
        clean = new JButton("Czysc");
        file.add(new JLabel("Plik"));
        file.add(open);
        file.add(save);
        file.add(generate);
        file.add(clean);

        JPanel edit = new JPanel();
        edit.setLayout(new GridLayout(7, 1));
        addPoint = new JButton("Dodaj punkt");
        movePoint = new JButton("Przesun punkt");
        closeShape = new JButton("Zamknij wielokat");
        autoclos = new JCheckBox("Autodomykanie");
        setColour = new JButton("Ustaw kolor");
        resetPosition = new JButton("Zresetuj pozycje");
        edit.add(new JLabel("Edycja"));
        edit.add(addPoint);
        edit.add(movePoint);
        edit.add(closeShape);
        edit.add(autoclos);
        edit.add(setColour);

        JPanel view = new JPanel();
        view.setLayout(new GridLayout(4, 1));
        zoom = new JSpinner();
        view.add(new JLabel("Widok"));
        view.add(zoom);
        view.add(resetPosition);
        this.add(file);
        this.add(edit);
        this.add(view);
    }

    void setActions() {
        this.addPoint.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent arg0) {
                controller.AddPoint();
            }
        });
        this.closeShape.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent arg0) {
                controller.CloseEditedShape();
            }
        });

        this.setColour.addActionListener(new ActionListener() {
            private Color fg = Color.BLACK;

            @Override
            public void actionPerformed(ActionEvent arg0) {
                fg = JColorChooser.showDialog(ToolBoxPanel.this, "Wybierz kolor", fg);
                controller.SetColor(fg);
            }
        });
        this.save.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fc = new JFileChooser();
                if (JFileChooser.APPROVE_OPTION == fc.showSaveDialog(ToolBoxPanel.this)) {
                    controller.Save(fc.getSelectedFile().getPath());
                }
            }
        });
        this.open.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent arg0) {
                JFileChooser fc = new JFileChooser();
                if (JFileChooser.APPROVE_OPTION == fc.showOpenDialog(ToolBoxPanel.this)) {
                    controller.Load(fc.getSelectedFile().getPath());
                }
            }
        });
        this.resetPosition.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                zoom.setValue(0);
                controller.ResetView();
            }
        });
        this.zoom.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent arg0) {
                // TODO Auto-generated method stub
                controller.SetZoom((Integer) zoom.getValue());
            }
        });
        this.generate.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ce) {
                controller.Reload();
            }
        });
        this.clean.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				controller.cleanup();
			}
		});
        this.autoclos.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				controller.setAutoClosure(autoclos.isSelected());
			}
		});
    }

    public void setController(IController controller) {
        this.controller = controller;
        setActions();
    }
}
