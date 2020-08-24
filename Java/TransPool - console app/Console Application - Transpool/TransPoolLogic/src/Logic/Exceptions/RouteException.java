package Logic.Exceptions;

public class RouteException extends Exception {
    private String path;
    private String station;
    private String exceptionReason;

    private final String EXCEPTION_MESSAGE = "Exception: The '%s' in the path '%s' %s";
    public RouteException(String path, String station, String exceptionReason) {
        this.path = path;
        this.station = station;
        this.exceptionReason = exceptionReason;
    }

    @Override
    public String getMessage() {
        return String.format(EXCEPTION_MESSAGE, path, station, exceptionReason);
    }
}
