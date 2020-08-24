package Logic.Exceptions;

public class DuplicatedStopPointException extends Exception {
    private int x;
    private int y;
    private final String EXCEPTION_MESSAGE = "Exception: The point (%d,%d)  appears more than one time in the Stops ";

    public DuplicatedStopPointException(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public String getMessage() {
        return String.format(EXCEPTION_MESSAGE,x,y);
    }

}
