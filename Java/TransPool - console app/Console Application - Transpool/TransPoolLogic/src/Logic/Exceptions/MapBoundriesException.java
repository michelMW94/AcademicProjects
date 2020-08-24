package Logic.Exceptions;

import Logic.SystemEngine.MapBoundries;

public class MapBoundriesException extends Exception {
    private int givenSize;
    private String sizeParam;

    private final String EXCEPTION_MESSAGE = "Exception: The given %s of value %d isn't in the range of " + MapBoundries.MINIMUM_SIZE +" to " + MapBoundries.MAXIMUM_SIZE;

    public MapBoundriesException(int givenSize,String sizeParam) {
        this.givenSize = givenSize;
        this.sizeParam = sizeParam;
    }
    @Override
    public String getMessage() {
        return String.format(EXCEPTION_MESSAGE, sizeParam, givenSize);
    }





}
