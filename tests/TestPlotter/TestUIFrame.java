import java.util.List;
import java.awt.*;
import javax.swing.*;

public class TestUIFrame extends JFrame {
    private JToolBar tool_bar_ = new JToolBar();

    public TestUIFrame(boolean showPoints) {
        JPanel content_pane = new JPanel(new BorderLayout());
        content_pane.setBorder(BorderFactory.createEtchedBorder());
        TestCanvas test_canvas_ = new TestCanvas(showPoints);
        content_pane.add(test_canvas_, BorderLayout.CENTER);
        content_pane.add(tool_bar_, BorderLayout.PAGE_END);
        setSize(500, 200);
        setContentPane(content_pane);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public void setToolBar(List<AbstractButton> tool_bar) {
        for (AbstractButton ab : tool_bar)
            tool_bar_.add(ab);
    }
}
