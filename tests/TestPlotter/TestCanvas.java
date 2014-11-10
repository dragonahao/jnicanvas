import java.awt.*;

public class TestCanvas extends Canvas {
    static {
        System.loadLibrary("Paint");
    }

    public native void paint(Graphics g);
}
