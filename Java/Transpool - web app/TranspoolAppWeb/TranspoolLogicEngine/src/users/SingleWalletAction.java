package users;

import java.time.LocalDateTime;

public class SingleWalletAction {
    private String actionMoneyType;
    private String actionDateTime;
    private float actionAmount;
    private float moneyBefore;
    private float moneyAfter;

    public SingleWalletAction(String actionMoneyType, String actionDateTime, float actionAmount, float moneyBefore, float moneyAfter) {
        this.actionMoneyType = actionMoneyType;
        this.actionDateTime = actionDateTime;
        this.actionAmount = actionAmount;
        this.moneyBefore = moneyBefore;
        this.moneyAfter = moneyAfter;
    }
}
