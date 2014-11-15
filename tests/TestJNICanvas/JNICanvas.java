import java.awt.*;

public class JNICanvas extends Canvas {
    static {
        System.loadLibrary("JNICanvas");
    }

//    public native void initialize();
    public native void paint(Graphics g);
    public native void segment(double x1, double y1, double x2, double y2);
//    public native void dispose();
}
