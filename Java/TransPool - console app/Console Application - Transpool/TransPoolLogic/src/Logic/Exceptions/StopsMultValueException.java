package Logic.Exceptions;

public class StopsMultValueException extends Exception {
    private String point;
    private final String EXCEPTION_MESSAGE = "Exception: The point %s  appears more than one time in the Stops ";
    public StopsMultValueException(String point) {this.point = point;}
    public String getMessage() {
        return String.format(EXCEPTION_MESSAGE, point);
    }

}
