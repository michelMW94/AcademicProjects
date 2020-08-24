package main;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("/UI/StartScreen/TranspoolUi.fxml"));
        primaryStage.setTitle("Transpool");
        primaryStage.setMinWidth(450);
        primaryStage.setMinHeight(350);
        primaryStage.setScene(new Scene(root, 780, 500));
        primaryStage.show();


    }


    public static void main(String[] args) {
        launch(args);
    }
}
