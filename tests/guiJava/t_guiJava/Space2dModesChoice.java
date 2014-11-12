import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import guiJava.PanelChoice;

public class Space2dModesChoice extends PanelChoice {
    private static final String label = "Modes:";
    private static final String[] strings = { "Vertical", "Horizontal" };
    private Space2d space2d;

    public Space2dModesChoice(JPanel parent, Space2d space2d_) {
        super(parent, label, strings,
                space2d_.mode == Space2d.Space2dMode.VERT ? 0 : 1);
        space2d = space2d_;
    }

    public void actionPerformed(ActionEvent event) {
	space2d.mode = (event.getActionCommand() == strings[0]
                ? Space2d.Space2dMode.VERT : Space2d.Space2dMode.HORIZ);
	System.out.println("Space2dModesChoice::actionPerformed(): mode = "
                + space2d.mode);
    }

    public static void main(final String[] args) {
        JFrame frame = new JFrame();
        JPanel panel = new JPanel();
        frame.getContentPane().add(panel);
        Space2d space2d = new Space2d();
        Space2dModesChoice space2dModesChoice
                = new Space2dModesChoice(panel, space2d);
        frame.setSize(300, 75);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
};
