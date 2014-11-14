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
        // TODO:  The next three lines don't work.
        canvasWidth = jniCanvas.getWidth();
        canvasHeight = jniCanvas.getHeight();
        System.out.println("width = " + canvasWidth
            + ", height = " + canvasHeight);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private class CanvasListener implements MouseListener {
        public CanvasListener() {
        }

        public void mouseClicked(MouseEvent e) {
            System.out.println("clicked");
            System.out.println("X = " + e.getX() + ", Y = " + e.getY());
            double x = 2.*e.getX()/488 - 1.;
            double y = - 2.*e.getY()/140 + 1.;
            System.out.println("x = " + x + ", y = " + y);
            jniCanvas.segment(x, y, x + .4, y + .4);
        }

        public void mouseEntered(MouseEvent e) {
            System.out.println("entered");
        }

        public void mouseExited(MouseEvent e) {
            System.out.println("exited");
        }

        public void mousePressed(MouseEvent e) {
            System.out.println("pressed");
        }

        public void mouseReleased(MouseEvent e) {
            System.out.println("released");
        }
    }

    public void setToolBar(List<AbstractButton> toolBar_) {
        for (AbstractButton ab : toolBar_)
            toolBar.add(ab);
    }
}
