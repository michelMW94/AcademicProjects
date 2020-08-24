package Logic.Exceptions;

public class OutofBoundriesStopPointException extends Exception {
    private int x;
    private int y;
    private int width;
    private int length;

    private final String EXCEPTION_MESSAGE = "Exception: The point (%s,%s) isn't in the map boundaries of (%s,%s) range";

    public OutofBoundriesStopPointException(int x, int y, int width, int length) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.length = length;
    }

    @Override
    public String getMessage() {
        return String.format(EXCEPTION_MESSAGE, x,y,width,length);
    }

}
