import java.awt.*;
import java.awt.event.*;

public class MyCanvas extends Canvas {
    static {
        System.loadLibrary("Paint");
    }
    public native void paint(Graphics g);

    public static void main(String[] args) {
        Frame f = new Frame();
        f.setBounds(0, 0, 500, 110);
        f.add( new MyCanvas() );
        f.addWindowListener( new WindowAdapter() {
            public void windowClosing(WindowEvent ev) {
                System.exit(0);
            }
        } );
        f.setVisible(true);
    }
}
