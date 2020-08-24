package Tasks;

import Manager.TransPoolMenager;
import UI.UtilitisUI.Utilitis;

import javax.xml.bind.JAXBException;
import java.io.File;

public class TaskFile extends javafx.concurrent.Task<Boolean> {
    private TransPoolMenager transPoolMenager = new TransPoolMenager();
    private File file;
    private final String ERROR = "Error";

    public TaskFile(TransPoolMenager transPoolMenager, File _file) {
       this.transPoolMenager = transPoolMenager;
        this.file = _file;
    }

    protected Boolean call() throws Exception {
        this.updateMessage("Opening file");
        Thread.sleep(3000L);

        try {
            if (this.file != null) {
                this.updateMessage("Check if TransPool data is valid");
                Thread.sleep(3000L);
                this.transPoolMenager.createTransPoolSystem(this.file);

            }
            return true;
        } catch (JAXBException jAXBException) {
            this.updateMessage("Invlalid File");
            String allJaxbErrors = this.transPoolMenager.getModelLogic().getJaxbErrorsInString();
            Utilitis.showMessageToUser(allJaxbErrors, "Error", 0);
            return false;
        } catch (Exception exception) {
            this.updateMessage("Invlalid File");
            String allModelErrors = this.transPoolMenager.getModelLogic().getJaxbErrorsInString();
            Utilitis.showMessageToUser(allModelErrors, "Error", 0);
            return false;
        }
    }
}
