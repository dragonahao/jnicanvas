import java.util.List;
import java.util.ArrayList;
import java.awt.event.*;
import javax.swing.*;

public class TestUI {
    private List<AbstractButton> toolBar;
    private TestButton testButton1, testButton2;

    public TestUI() {
        toolBar = new ArrayList<AbstractButton>();

        testButton1 = new TestButton("testButton 1");
        toolBar.add(testButton1);
        testButton2 = new TestButton("testButton 2");
        toolBar.add(testButton2);
    }

    public List<AbstractButton> getToolBar() {
        return toolBar;
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
