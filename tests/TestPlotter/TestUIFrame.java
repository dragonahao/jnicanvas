import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class TestUIFrame extends JFrame {
    private JToolBar tool_bar_ = new JToolBar();
    private TestCanvas test_canvas_ = new TestCanvas();

    public TestUIFrame() {
        Container content_pane = getContentPane();
        content_pane.add(test_canvas_);
        // The preceding line works only if the following one
        // is commented out.  What's the right way to have both?
        content_pane.add(tool_bar_);
        // The next line does not work.
        setSize(new Dimension(500, 150));
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public void setToolBar(List<AbstractButton> tool_bar) {
        Iterator iter = tool_bar.iterator();
        while (iter.hasNext())
            tool_bar_.add((AbstractButton) iter.next());
    }
}
