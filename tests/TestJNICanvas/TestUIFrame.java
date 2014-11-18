import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class TestUIFrame extends JFrame {
    static final int X_SIZE = 500;
    static final int Y_SIZE = 200;

    private JToolBar toolBar = new JToolBar();
    private JNICanvas jniCanvas = new JNICanvas();
    private int canvasWidth, canvasHeight;

    public TestUIFrame() {
        JPanel contentPane = new JPanel(new BorderLayout());
        contentPane.setBorder(BorderFactory.createEtchedBorder());
        contentPane.add(jniCanvas, BorderLayout.CENTER);
        CanvasListener canvasListener = new CanvasListener();
        jniCanvas.addMouseListener(canvasListener);
        contentPane.add(toolBar, BorderLayout.PAGE_END);
        setSize(X_SIZE, Y_SIZE);
        setContentPane(contentPane);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private class CanvasListener implements MouseListener {
        public CanvasListener() {
        }

        public void mouseClicked(MouseEvent e) {
            System.err.println("entered mouseClicked()");
            // BUG:  This dimension is incorrect after resizing the window!
            Dimension dim = jniCanvas.getSize();
            System.err.println("width = " + dim.width + ", height = "
                    + dim.height);
            System.err.println("X = " + e.getX() + ", Y = " + e.getY());
            double x = 2.*e.getX()/dim.width - 1.;
            double y = - 2.*e.getY()/dim.height + 1.;
            System.err.println("x = " + x + ", y = " + y);
            jniCanvas.segment(x, y, x + .4, y + .4);
        }

        public void mouseEntered(MouseEvent e) {
            System.err.println("entered mouseEntered()");
        }

        public void mouseExited(MouseEvent e) {
            System.err.println("entered mouseExited()");
        }

        public void mousePressed(MouseEvent e) {
            System.err.println("entered mousePressed()");
        }

        public void mouseReleased(MouseEvent e) {
            System.err.println("entered mouseReleased()");
        }
    }

    public void setToolBar(List<AbstractButton> toolBar_) {
        for (AbstractButton ab : toolBar_)
            toolBar.add(ab);
    }
}
