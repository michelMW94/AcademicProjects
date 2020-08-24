package Logic.Exceptions;

public class NonXmlFileException extends Exception {
    private String fileName;

    private final String EXCEPTION_MESSAGE = "Exception: The given file '%s' isn't of xml type";
    public NonXmlFileException(String fileName) {this.fileName = fileName;}
    @Override
    public String getMessage() {
        return String.format(EXCEPTION_MESSAGE, fileName);
    }
}
