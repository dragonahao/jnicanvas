import java.awt.*;
//import javax.swing.*;

public class TestCanvas extends Canvas {
    static {
        System.loadLibrary("Paint");
    }

    public native void paint(Graphics g);

/*
    public TestCanvas() {
        super(new BorderLayout());
    }
*/
}
