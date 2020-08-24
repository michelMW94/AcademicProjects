package TranspoolMaps;

import SystemEngine.TransPool;
import SystemLogic.ModelLogic;

import java.util.Objects;

public class SingleTransPoolMap {

    private String userName;
    private String mapName;
    private int numStation;
    private int numRoutes;
    private int numOffers;
    private int numRequests;
    private String fileName;
    private ModelLogic modelLogic;
    private int numMatchedRequest;




    public SingleTransPoolMap(String userName, String mapName, int numStation, int numRoutes, int numOffers, int numRequests, String fileName, ModelLogic modelLogic) {
        this.userName = userName;
        this.mapName = mapName;
        this.numStation = numStation;
        this.numRoutes = numRoutes;
        this.numOffers = numOffers;
        this.numRequests = numRequests;
        this.fileName = fileName;
        this.modelLogic = modelLogic;
        this.numMatchedRequest = 0;

    }

    public int getNumMatchedRequest() {
        return numMatchedRequest;
    }

    public void setNumMatchedRequest(int numMatchedRequest) {
        this.numMatchedRequest = numMatchedRequest;
    }

    public ModelLogic getModelLogic() {
        return modelLogic;
    }

    public void setModelLogic(ModelLogic modelLogic) {
        this.modelLogic = modelLogic;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getMapName() {
        return mapName;
    }

    public void setMapName(String mapName) {
        this.mapName = mapName;
    }

    public int getNumStation() {
        return numStation;
    }

    public void setNumStation(int numStation) {
        this.numStation = numStation;
    }

    public int getNumRoutes() {
        return numRoutes;
    }

    public void setNumRoutes(int numRoutes) {
        this.numRoutes = numRoutes;
    }

    public int getNumOffers() {
        return numOffers;
    }

    public void setNumOffers(int numOffers) {
        this.numOffers = numOffers;
    }

    public int getNumRequests() {
        return numRequests;
    }

    public void setNumRequests(int numRequests) {
        this.numRequests = numRequests;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof  SingleTransPoolMap)) return false;
        SingleTransPoolMap that = ( SingleTransPoolMap) o;
        return Objects.equals(userName, that.userName);
    }

    @Override
    public int hashCode() {
        return Objects.hash(userName);
    }
}
