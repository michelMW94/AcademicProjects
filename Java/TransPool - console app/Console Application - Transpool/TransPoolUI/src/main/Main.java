/**

TransPool Project 1 , 03/05/2020
Eran Smmuel 205477383  , Michel Mitskevsky Weizmann 313588550

*/

package main;

import Menu.MenuUIForm;

public class Main
{
    public static void main(String[] args)
    {
        try {
            MenuUIForm menu = new MenuUIForm();
            System.out.println("Welcome To Transpool Application! \nFor using our Application you must enter xml path file first");
            while (!menu.ReadFromXmlFile()) {
            }
            menu.Run();
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }

    }

}
