package Logic.Exceptions;


public class  MessageException extends Exception {

   private String m_Msg;

    public MessageException(String s) {
        m_Msg = s;
    }

    @Override
    public String getMessage() {
        return m_Msg;
    }
}