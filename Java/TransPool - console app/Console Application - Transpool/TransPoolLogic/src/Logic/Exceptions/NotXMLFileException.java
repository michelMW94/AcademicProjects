package Logic.Exceptions;

public class NotXMLFileException extends Exception {
    private String fileName;

    private final String EXCEPTION_MESSAGE = "Exception: he given file ' %s ' isn't of xml type";
    public NotXMLFileException(String fileName) {this.fileName = fileName;}
    @Override
    public String getMessage() {
        return String.format(EXCEPTION_MESSAGE, fileName);
    }
}
