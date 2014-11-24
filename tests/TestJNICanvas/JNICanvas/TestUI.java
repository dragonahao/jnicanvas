package JNICanvas;

import java.util.List;
import java.util.ArrayList;
import java.awt.event.*;
import javax.swing.*;

public class TestUI {
    private List<AbstractButton> toolBar;
    private TestButton testButton;

    public TestUI() {
        toolBar = new ArrayList<AbstractButton>();

        testButton = new TestButton("timing");
        toolBar.add(testButton);
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
            System.err.println(cmd + " pressed");
            JNICanvas.timing();
            System.err.println("timing completed");
        }
    }
}
