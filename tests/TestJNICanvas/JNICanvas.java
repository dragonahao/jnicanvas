import java.awt.*;

public class JNICanvas extends Canvas {
    static {
        System.loadLibrary("JNICanvas");
    }

    public native void initialize();
    public native void paint(Graphics g);
    public native void dispose();
}
