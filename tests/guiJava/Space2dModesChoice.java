import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class Space2dModesChoice extends Choice {
    private static final String label = "Modes:";
    private static final String[] strings = { "Vertical", "Horizontal" };
    private Space2d space_2d_;

    public Space2dModesChoice(JPanel parent, Space2d space_2d) {
        super(parent, label, strings,
                space_2d.mode == Space2d.Space2dMode.VERT ? 0 : 1);
        space_2d_ = space_2d;
    }

    public void actionPerformed(ActionEvent event) {
	space_2d_.mode = (event.getActionCommand() == strings[0]
                ? Space2d.Space2dMode.VERT : Space2d.Space2dMode.HORIZ);
	System.out.println("Space2dModesChoice::actionPerformed(): mode = "
                + space_2d_.mode);
    }

    public static void main(final String[] args) {
        JFrame frame = new JFrame();
        JPanel panel = new JPanel();
        frame.getContentPane().add(panel);
        Space2d space_2d = new Space2d();
        Space2dModesChoice space_2d_modes_choice
                = new Space2dModesChoice(panel, space_2d);
        frame.setVisible(true);
    }
};
