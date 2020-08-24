package UI.NewRideScreen;

import SystemLogic.ModelLogic;
import com.jfoenix.controls.JFXComboBox;
import com.jfoenix.controls.JFXDatePicker;
import com.jfoenix.controls.JFXTextField;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;

public class NewRideController {

    @FXML
    private JFXComboBox<String> TimeCombobox;

    @FXML
    private JFXDatePicker TimeDatePicker;

    @FXML
    private JFXTextField FirstNameTextField;

    @FXML
    private JFXTextField LastNameTextField;

    @FXML
    private JFXComboBox<String> CurrentStopComboBox;

    @FXML
    private JFXComboBox<String> DestinitionStopComboBox;

    ModelLogic modelLogic = new ModelLogic();


    @FXML
    private void initialize() {
        TimeCombobox.getItems().addAll("Future departure time","Desired arrival time");
        /*****
        for(Stop stop: SystemLogic.getStops())
        {
           CurrentStopComboBox.getItems().add(stop.getName());
           DestinitionStopComboBox.getItems().add(stop.getName());
        }

         */
    }

    @FXML
    void OnComboBoxClicked(ActionEvent event) {
        if(TimeCombobox.getValue().equals("Future departure time"))
        {
            TimeDatePicker.show();
            TimeDatePicker.setDisable(false);
            //TimeCombobox.setPromptText(TimeDatePicker.getTime().getHour() + ":" + TimeDatePicker.getTime().getMinute() );
        }
        if(TimeCombobox.getValue().equals("Desired arrival time"))
        {
            TimeDatePicker.show();
            TimeDatePicker.setDisable(false);
        }

    }

    @FXML
    void OnAddRequestClicked(ActionEvent event) {
        String FirstName = FirstNameTextField.getText();
        String LastName = LastNameTextField.getText();
    }

}
