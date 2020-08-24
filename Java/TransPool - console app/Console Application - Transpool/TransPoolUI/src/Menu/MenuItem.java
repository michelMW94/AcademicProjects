package Menu;


public class MenuItem
{
    private ICommand m_Command;
    private String m_Text;


    public  MenuItem()
    {
      m_Command= null;
      m_Text = " ";
    }

    public MenuItem(String Text, ICommand command)
    {
        m_Command = command;
        m_Text= Text;
    }

    public ICommand getCommand() { return this.m_Command; }
    public void setCommand(ICommand command) { this.m_Command = command; }

    public String getText() { return this.m_Text; }
    public void setText(String text) { this.m_Text = text; }

    public void Selected() {
        if (m_Command != null) {
            m_Command.Execute();
        }
    }
}
