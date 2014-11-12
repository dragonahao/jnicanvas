import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Space2dSettingsButton extends JButton implements ActionListener {
    private Space2dSettings space2dSettings;

    public Space2dSettingsButton(JPanel parent, Space2d space2d) {
        super("Settings...");
        space2dSettings = new Space2dSettings(space2d);
        addActionListener(this);
        parent.add(this);
    }

    public void actionPerformed(ActionEvent event) {
        space2dSettings.setVisible(true);
    }

    private class Space2dSettings extends JFrame implements ActionListener {
        private Space2d space2d;
        private JPanel panel;
        private ButtonGroup group;
    //    private PanelDoubleText height;
    //    private PanelDoubleText width;

        public Space2dSettings(Space2d space2d_) {
            space2d = space2d_;

            panel = new JPanel(new FlowLayout());
            getContentPane().add(panel);

            JLabel label = new JLabel("Space2d Settings");
            panel.add(label);

            group = new ButtonGroup();

            JButton apply = new JButton("Apply");
            apply.addActionListener(this);
            group.add(apply);
            panel.add(apply);

            JButton reset = new JButton("Reset");
            reset.addActionListener(this);
            group.add(reset);
            panel.add(reset);

            pack();
        }

        public void actionPerformed(ActionEvent event) {
            System.out.println(event.getActionCommand());
            if (event.getActionCommand() == "Apply")
                applyProcedure();
            else
                resetProcedure();
        }
    }

    private void applyProcedure() {
/*
	space2d.height = space2dSettings.height.value();
	System.out.println("Space2dApplyButton::proc(): height = "
		+ space2d.height);
	space2d.width = space2dSettings.width.value();
	System.out.println("Space2dApplyButton::proc(): width = "
		+ space2d.width);
*/
    }

    private void resetProcedure() {
/*
	space2dSettings.height.value(space2d.height);
	System.out.println("Space2dResetButton::proc(): height = "
		+ space2d.height);
	space2dSettings.width.value(space2d.width);
	System.out.println("Space2dResetButton::proc(): width = "
		+ space2d.width);
*/
    }

    public static void main(final String[] args) {
        JFrame frame = new JFrame();
        JPanel panel = new JPanel();
        frame.getContentPane().add(panel);
        Space2d space2d = new Space2d();
        Space2dSettingsButton space2dSettingsButton
                = new Space2dSettingsButton(panel, space2d);
        frame.setSize(300, 75);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}
