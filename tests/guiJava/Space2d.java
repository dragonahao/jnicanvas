public class Space2d
{
    public Space2dMode mode;
    public int option;
    public double intensity;
    public double depth;
    public double height;
    public double width;

    public enum Space2dMode { VERT, HORIZ };

    public int OPTION1 = 0x1;
    public int OPTION2 = 0x2;
    public int OPTION3 = 0x4;

    public double INTENSITY_SCALE = 100.;
    public double INTENSITY_MIN = 0.;
    public double INTENSITY_MAX = 100.;

    public double DEPTH_SCALE = 10.;
    public double DEPTH_MIN = 0.;
    public double DEPTH_MAX = 10.;

    public Space2d() {
        mode = Space2dMode.HORIZ;
        option = OPTION1 | OPTION3;
        intensity = 0.45;
        depth = 0.1;
        height = 100.246;
        width = 246.101;
    }

    public static void main(final String[] args) {
        Space2d space_2d = new Space2d();
        System.out.println("mode = " + space_2d.mode);
        System.out.println("option = " + space_2d.option);
        System.out.println("intensity = " + space_2d.intensity);
        System.out.println("depth = " + space_2d.depth);
        System.out.println("height = " + space_2d.height);
        System.out.println("width = " + space_2d.width);
    }
}
