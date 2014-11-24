import JNICanvas.TestUI;
import JNICanvas.TestUIFrame;

public class TestJNICanvas {

    public TestJNICanvas(String[] args) {
        TestUI testUI = new TestUI();
        TestUIFrame testUIFrame = new TestUIFrame();
        testUIFrame.setToolBar(testUI.getToolBar());
        testUIFrame.setVisible(true);
    }

    public static void main(final String[] args) {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new TestJNICanvas(args);
            }
        });
    }
}
