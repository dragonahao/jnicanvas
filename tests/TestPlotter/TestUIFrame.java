import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class TestUIFrame extends JFrame {
    private JPanel contentPane;
    private JToolBar toolBar_ = new JToolBar();
    private TestCanvas testCanvas_ = new TestCanvas();

    public TestUIFrame() {
        this.setBounds(0, 0, 500, 110);
        this.add(testCanvas_);
        // The preceding two lines work only if the following three
        // are commented out.  What's the right way to have both?
        contentPane = (JPanel) this.getContentPane();
        contentPane.setLayout(new FlowLayout());
        contentPane.add(toolBar_);
        this.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });
    }

    public void setToolBar(List<AbstractButton> toolBar) {
        Iterator it = toolBar.iterator();
        while (it.hasNext())
            toolBar_.add((AbstractButton) it.next());
    }
}
