package users;

import java.util.Objects;

public class SingleUser {

    private String userName;
    private String userType;
    private UserWallet userWallet;

    public SingleUser(String userName, String userType) {
        this.userName = userName;
        this.userType = userType;
        this.userWallet = new UserWallet();
    }

    public String getUserName() {
        return userName;
    }

    public String getUserType() {
        return userType;
    }

    public UserWallet getUserWallet() {
        return userWallet;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof SingleUser)) return false;
        SingleUser that = (SingleUser) o;
        return Objects.equals(userName, that.userName) &&
                Objects.equals(userType, that.userType) &&
                Objects.equals(userWallet, that.userWallet);
    }

    @Override
    public int hashCode() {
        return Objects.hash(userName, userType, userWallet);
    }
}
