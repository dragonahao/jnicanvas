public class Space2d
{
    public static enum Space2dMode { VERT, HORIZ };

    public static final int OPTION1 = 0x1;
    public static final int OPTION2 = 0x2;
    public static final int OPTION3 = 0x4;

    public static final double INTENSITY_SCALE = 100.;
    public static final double INTENSITY_MIN = 0.;
    public static final double INTENSITY_MAX = 100.;

    public static final double DEPTH_SCALE = 10.;
    public static final double DEPTH_MIN = 0.;
    public static final double DEPTH_MAX = 10.;

    public Space2dMode mode;
    public int option;
    public double intensity;
    public double depth;
    public double height;
    public double width;

    public Space2d() {
        mode = Space2dMode.HORIZ;
        option = OPTION1 | OPTION3;
        intensity = 0.45;
        depth = 0.1;
        height = 100.246;
        width = 246.101;
    }

    public static void main(final String[] args) {
        Space2d space2d = new Space2d();
        System.out.println("mode = " + space2d.mode);
        System.out.println("option = " + space2d.option);
        System.out.println("intensity = " + space2d.intensity);
        System.out.println("depth = " + space2d.depth);
        System.out.println("height = " + space2d.height);
        System.out.println("width = " + space2d.width);
    }
}
