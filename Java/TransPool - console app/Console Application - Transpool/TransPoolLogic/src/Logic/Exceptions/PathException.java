package Logic.Exceptions;

public class PathException extends Exception {
    private String from;
    private String to;
    private String exceptionReason;

    private final String EXCEPTION_MESSAGE = "Exception: The path  %s -> %s %s";
    public PathException(String from, String to, String exceptionReason) {
        this.from = from;
        this.to = to;
        this.exceptionReason = exceptionReason;
    }

    @Override
    public String getMessage() {
        return String.format(EXCEPTION_MESSAGE, from, to, exceptionReason);
    }
}
