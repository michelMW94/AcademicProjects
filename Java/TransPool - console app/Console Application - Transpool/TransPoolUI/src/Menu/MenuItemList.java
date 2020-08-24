package Menu;

import Logic.Exceptions.MessageException;

import java.util.ArrayList;
import java.util.Scanner;


public class MenuItemList extends ArrayList<MenuItem> {

    private int m_UserSelection = 0;

    public void Run() {
        Scanner scanner = new Scanner(System.in);
        Boolean userQuit = false;
        while (!userQuit) {
            ShowMenu();
            try {
                userQuit = !GetUserSelection();
                if (!userQuit) {
                    this.get(m_UserSelection - 1).Selected();
                }
            } catch (NumberFormatException ex) {
                System.out.println(String.format("Invalid input,You must enter a number between 1 to %d", this.size()));
            } catch (Exception ex) {
                System.out.println(ex.getMessage());
            }

            if (!userQuit) {
                System.out.println("Press Enter to go back menu");
                scanner.nextLine();
            }

        }

        System.out.println("Thanks for using our App, Hope to see you next time");
    }


    private void ShowXml()
    {

    }


    private void ShowMenu() {
        System.out.println("TransPool App :");
        int itemNum = 1;

        for (MenuItem item : this) {
            System.out.println(String.valueOf(itemNum)  + " - " + item.getText());
            itemNum++;
        }

        System.out.println("Type your selection number and press 'enter'. To quit type 'Q' and then 'enter' ");

    }

    private boolean GetUserSelection() throws MessageException {

        boolean userQuit = false;
        Scanner scanner = new Scanner(System.in);
        String userSelection = scanner.nextLine();
        if (!userSelection.equals("Q")) {
            m_UserSelection = Integer.valueOf(userSelection);
            if (!(m_UserSelection > 0 && m_UserSelection <= this.size())) {
                throw new MessageException(String.format("Invalid Input, Please select a number between 1 to %d", this.size()));
            }
        }
            else
            {
                m_UserSelection = 0;
                userQuit = true;
            }

        return !userQuit;
    }

}

