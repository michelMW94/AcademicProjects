package Manager;

import SystemEngine.TransPool;
import SystemLogic.ModelLogic;
import UI.StartScreen.MyController;
import javafx.beans.property.SimpleStringProperty;

import javax.xml.bind.JAXBException;
import java.io.File;

public class TransPoolMenager {

    private SimpleStringProperty fileName;
    private MyController controller;
    private ModelLogic modelLogic = new ModelLogic();

    public ModelLogic getModelLogic() {
        return modelLogic;
    }

    public void setModelLogic(ModelLogic modelLogic) {
        this.modelLogic = modelLogic;
    }

    public String getFileName() {
        return fileName.get();
    }

    public void setFileName(String fileName) {
        this.fileName.set(fileName);
    }


    public TransPoolMenager() {
    }

    public void createTransPoolSystem(File file) throws Exception {
        try {
           TransPool transPool = modelLogic.fromXmlFileToObject(file);
           modelLogic.setTransPool(transPool);
        }
        catch (JAXBException jAXBException) {
          throw jAXBException;
        }
        catch (Exception exception) {
            throw exception;
        }
    }

    public SimpleStringProperty fileNameProperty() {
        return fileName;
    }

    public TransPoolMenager(MyController controller) {
        this.fileName = new SimpleStringProperty();
        this.controller = controller;
    }
}
