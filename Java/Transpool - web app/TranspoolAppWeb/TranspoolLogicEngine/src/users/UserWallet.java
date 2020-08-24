package users;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class UserWallet {

    private float Money;
    private final List<SingleWalletAction> walletActions;


    public float getMoney() {
        return Money;
    }

    public  synchronized List<SingleWalletAction> getWalletActions() {
        return Collections.unmodifiableList(walletActions);
    }

    public UserWallet() {
        walletActions = new ArrayList<SingleWalletAction>();
        Money = 0;
    }

    public synchronized void addMoney(float moneyToAdd)
    {
        Money += moneyToAdd;
    }

    public synchronized void giveMoney (float moneyToGive)
    {
        Money += moneyToGive;
        if(Money < 0)
            Money = 0;
    }

    public synchronized void addWalletAction(String actionMoneyType, String actionDateTime, float actionAmount)
    {
        float moneyBefore = Money;
        switch(actionMoneyType) {
            case "Charging":
            case "Receiving":
                addMoney(actionAmount);
                break;
            case "Sending":
                giveMoney(actionAmount);
                break;
        }
        float moneyAfter = Money;
        walletActions.add(new SingleWalletAction(actionMoneyType,actionDateTime,actionAmount,moneyBefore,moneyAfter));
    }
}
