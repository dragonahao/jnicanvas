import java.awt.*;

public class TestCanvas extends Canvas {
    
    private boolean showPts;
    
    public TestCanvas(boolean showPoints){
        
        showPts= showPoints;
        
    }
    
    
    static {
        System.loadLibrary("Paint");
    }
     
    
    
    public native void paint(Graphics g);
    

    
}
