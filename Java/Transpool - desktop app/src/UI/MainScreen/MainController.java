package UI.MainScreen;



import CustomClasses.TripRequest;
import SystemLogic.ModelLogic;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Tab;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

public class MainController {

    @FXML
    private Tab MapTab;

    @FXML
    private Tab RidesTab;

    @FXML
    private Tab OffersTab;

    @FXML
    private HBox HboxItem;

    @FXML
    private VBox VboxList;

    @FXML
    private TableColumn<TripRequest, Integer> OrderNumber;

    @FXML
    private TableColumn<TripRequest, String> FirstName;

    @FXML
    private TableColumn<TripRequest, String> LastName;

    @FXML
    private TableColumn<TripRequest, String> CurrentStop;

    @FXML
    private TableColumn<TripRequest, String> DestinitionStop;

    @FXML
    private TableView<TripRequest> Table;


    ModelLogic modelLogic = new ModelLogic();
    ObservableList<TripRequest> list = FXCollections.observableArrayList();

    @FXML
    private void initialize() {
    }


    @FXML
    void OnTabClicked(MouseEvent event) {
     if(RidesTab.isSelected())
     {

     }
    }



}
