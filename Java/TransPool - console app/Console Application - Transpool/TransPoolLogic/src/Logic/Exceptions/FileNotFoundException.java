package Logic.Exceptions;

public class FileNotFoundException extends Exception {
    private String fileName;

    private final String EXCEPTION_MESSAGE = "Exception: The given file '%s' wasn't found";
    public FileNotFoundException(String fileName) {this.fileName = fileName;}
    @Override
    public String getMessage() {
        return String.format(EXCEPTION_MESSAGE, fileName);
    }
}
