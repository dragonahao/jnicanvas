public class TestPlotter {

    public TestPlotter(String[] args) {
        TestUIFrame test_ui_frame = new TestUIFrame(true);
        
        TestUIFrame testUIFrame2 = new TestUIFrame(false);
        

        
        TestUI test_ui = new TestUI();
        test_ui_frame.setToolBar(test_ui.getToolBar());
        test_ui_frame.setVisible(true);
        testUIFrame2.setVisible(true);
    }

    public static void main(final String[] args) {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new TestPlotter(args);
            }
        });
    }
}
