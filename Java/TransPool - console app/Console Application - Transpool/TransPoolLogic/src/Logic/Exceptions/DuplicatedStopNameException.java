package Logic.Exceptions;

public class DuplicatedStopNameException extends  Exception{
    private String stopName;

    public DuplicatedStopNameException(String stopName) {this.stopName = stopName;}
    private final String EXCEPTION_MESSAGE = "Exception: The name '%s' is given to more than one Stop";
    public String getMessage() {
        return String.format(EXCEPTION_MESSAGE, stopName);
    }
}
