package users;

import java.util.*;
import java.util.stream.Collectors;


public class UserManager {

    private final List<SingleUser> usersList;


    public UserManager() {
        usersList = new ArrayList<SingleUser>();
    }

    public synchronized void addUser(String username, String type) {
        usersList.add(new SingleUser(username,type));
    }

    public synchronized List<SingleUser> getUsersList() {
        return Collections.unmodifiableList(usersList);
    }

    public synchronized SingleUser  getSingleUser(String username)
    {
        Optional<SingleUser> singleUser = usersList.stream()
                .filter(singleUser1 -> singleUser1.getUserName().equals(username)).findFirst();
        if(singleUser.isPresent())
            return singleUser.get();
        return null;
    }
    public synchronized List<String> getUserStringList() {
        return usersList.stream().map(user -> user.getUserType() + " " + user.getUserName()).collect(Collectors.toList());
    }

    public boolean isUserExists(String username) {
        Optional<SingleUser> singleUser = usersList.stream()
                .filter(singleUser1 -> singleUser1.getUserName().equals(username)).findFirst();
        if(singleUser.isPresent())
            return true;

        return false;
    }

}
