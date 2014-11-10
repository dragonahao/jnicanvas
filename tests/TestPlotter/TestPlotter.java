public class TestPlotter {
    private static TestUIFrame testUIFrame_ = new TestUIFrame();

    public static void main(final String[] args) {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createUI(args);
            }
        });
    }

    public static void createUI(String[] args) {
        TestUI.init();

        testUIFrame_.setToolBar(TestUI.getToolBar());
        testUIFrame_.pack();
        testUIFrame_.setVisible(true);
    }
}
