import java.util.List;
import java.util.ArrayList;
import java.awt.event.*;
import javax.swing.*;

public class TestUI {
    private List<AbstractButton> tool_bar_;
    private TestButton test_button1_, test_button2_;

    public TestUI() {
        tool_bar_ = new ArrayList<AbstractButton>();

        test_button1_ = new TestButton("testButton 1");
        tool_bar_.add(test_button1_);
        test_button2_ = new TestButton("testButton 2");
        tool_bar_.add(test_button2_);
    }

    public List<AbstractButton> getToolBar() {
        return tool_bar_;
    }

    public class TestButton extends JButton implements ActionListener {
        public TestButton(String name) {
            super(name);
            addActionListener(this);
        }

        public void actionPerformed(ActionEvent e) {
            String cmd = e.getActionCommand();
            System.out.println(cmd + " pressed");
        }
    }
}
