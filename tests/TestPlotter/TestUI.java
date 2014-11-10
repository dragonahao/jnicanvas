import java.util.List;
import java.util.ArrayList;
import java.awt.event.*;
import javax.swing.*;

public class TestUI {
    private static List<AbstractButton> toolBar_;
    private static TestButton testButton1_, testButton2_;

    public static void init() {
        toolBar_ = new ArrayList<AbstractButton>();

        testButton1_ = new TestButton("testButton 1");
        toolBar_.add(testButton1_);
        testButton2_ = new TestButton("testButton 2");
        toolBar_.add(testButton2_);
    }

    public static List<AbstractButton> getToolBar() {
        return toolBar_;
    }

    public static class TestButton extends JButton implements ActionListener {
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
