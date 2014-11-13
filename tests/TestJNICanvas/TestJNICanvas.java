public class TestJNICanvas {

    public TestJNICanvas(String[] args) {
        TestUIFrame testUIFrame = new TestUIFrame();
        TestUI testUI = new TestUI();
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
