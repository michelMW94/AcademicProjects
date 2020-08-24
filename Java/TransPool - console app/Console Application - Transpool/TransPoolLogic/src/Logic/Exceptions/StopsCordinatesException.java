package Logic.Exceptions;

public class StopsCordinatesException extends Exception {
    private String point;
    private String maxPoint;

    private final String EXCEPTION_MESSAGE = "Exception: The point %s  isn't in the map boundaries of %s range";
    public StopsCordinatesException (String point, String maxPoint) {
        this.point = point;
        this.maxPoint = maxPoint;
    }

    @Override
    public String getMessage() {
        return String.format(EXCEPTION_MESSAGE, point, maxPoint);
    }

}
