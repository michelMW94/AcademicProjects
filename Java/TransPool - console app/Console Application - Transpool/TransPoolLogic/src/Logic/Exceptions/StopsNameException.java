package Logic.Exceptions;

public class StopsNameException  extends  Exception{
    private String stopName;

    public StopsNameException(String stopName) {this.stopName = stopName;}
    private final String EXCEPTION_MESSAGE = "Exception: The name '%s' is given to more than one Stop";
    public String getMessage() {
        return String.format(EXCEPTION_MESSAGE, stopName);
    }
}
