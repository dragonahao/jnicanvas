import java.awt.*;

public class TestCanvas extends Canvas {
    static {
        System.loadLibrary("Paint");
    }

    
    private boolean changeColor;

    public void changeColor(boolean changeColor) {
        this.changeColor = changeColor;
    }
    
    
    
    
    
    public native void paint(Graphics g);
    

    
}
