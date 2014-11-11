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
        }
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

/*
void
Space2dApplyButton::proc(void)
{
	space2d.height = space2dSettings.height.value();
	std::cerr << "Space2dApplyButton::proc(): height = "
		<< space2d.height << "\n";
	space2d.width = space2dSettings.width.value();
	std::cerr << "Space2dApplyButton::proc(): width = "
		<< space2d.width << "\n";
}

void
Space2dResetButton::proc(void)
{
	space2dSettings.height.value(space2d.height);
	std::cerr << "Space2dResetButton::proc(): height = "
		<< space2d.height << "\n";
	space2dSettings.width.value(space2d.width);
	std::cerr << "Space2dResetButton::proc(): width = "
		<< space2d.width << "\n";
}

Space2dSettings::Space2dSettings(const Frame parent, Space2d space2d,
		int x__, int y__)
    extends Frame(parent, x__, y__),
	  Panel(*this, Panel::VERTICAL),
	  height(*this),
	  width(*this),
	  apply(*this, space2d),
	  reset(*this, space2d)
{
	display_label("Settings...");

	height.display_label("Height:");
	width.display_label("Width:");

	reset.proc();

	fit_height();
	fit_width();
}

void
Space2dSettings::show(void)
{
	reset.proc();
	Frame::show();
}

Space2dSettingsButton::Space2dSettingsButton(const Panel parent__,
	Space2d space2d_)
    extends PanelButton(parent__),
	  space2d(space2d_),
	  space2dSettings(0)
{
	display_label("Settings...");
}
*/
