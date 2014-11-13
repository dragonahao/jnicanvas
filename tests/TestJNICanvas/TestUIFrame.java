import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class TestUIFrame extends JFrame {
    private JToolBar toolBar = new JToolBar();

    public TestUIFrame() {
        JPanel content_pane = new JPanel(new BorderLayout());
        content_pane.setBorder(BorderFactory.createEtchedBorder());
        JNICanvas jniCanvas = new JNICanvas();
        content_pane.add(jniCanvas, BorderLayout.CENTER);
        content_pane.add(toolBar, BorderLayout.PAGE_END);
        setSize(500, 200);
//        jniCanvas.initialize();
        setContentPane(content_pane);
//        jniCanvas.dispose();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public void setToolBar(List<AbstractButton> toolBar_) {
        for (AbstractButton ab : toolBar_)
            toolBar.add(ab);
    }
}
