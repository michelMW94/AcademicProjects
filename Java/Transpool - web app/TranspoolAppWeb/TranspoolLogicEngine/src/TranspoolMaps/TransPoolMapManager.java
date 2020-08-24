package TranspoolMaps;

import SystemLogic.ModelLogic;

import java.util.*;

public class TransPoolMapManager {

    public synchronized SingleTransPoolMap FindMap(String MapName) {
        Optional<SingleTransPoolMap> singleTransPoolMap = transPoolMapList.stream()
                .filter(singleTransPoolMap1 -> singleTransPoolMap1.getMapName().equals(MapName)).findFirst();
        if(singleTransPoolMap.isPresent())
        {
            return singleTransPoolMap.get();
        }
        else
            return null;
    }

    private final List<SingleTransPoolMap> transPoolMapList;

    public TransPoolMapManager() {
        this.transPoolMapList =  new ArrayList<SingleTransPoolMap>();
    }

    public synchronized void addTransPoolMap(String userName, String mapName, int numStation, int numRoutes, int numOffers, int numRequests, String fileName, ModelLogic modelLogic)
    {
        transPoolMapList.add(new SingleTransPoolMap(userName, mapName, numStation, numRoutes, numOffers, numRequests, fileName, modelLogic));
    }


    public synchronized boolean isTransPoolUsersMapExists(String username) {
    return transPoolMapList.stream().anyMatch(c-> c.getUserName().equals(username));
    }


    public boolean isFileMapExists(String fileName)
    {
        return transPoolMapList.stream().anyMatch(c-> c.getFileName().equals(fileName));
    }
    public synchronized List<SingleTransPoolMap> getTransPoolMaps(){
        return Collections.unmodifiableList(transPoolMapList);
    }

    public boolean isMapNameExists(String mapName)
    {
        return transPoolMapList.stream().anyMatch(c-> c.getMapName().equals(mapName));
    }

    public int getVersion() {
        return transPoolMapList.size();
    }

    public synchronized void removeMap(String userName) {
        Optional<SingleTransPoolMap> singleTransPoolMap = transPoolMapList.stream()
                .filter(singleTransPoolMap1 -> singleTransPoolMap1.getUserName().equals(userName)).findFirst();
        if(singleTransPoolMap.isPresent())
        {
            transPoolMapList.remove(singleTransPoolMap.get());
        }
    }

    public synchronized void updateUserMap(String userName, String mapName, int numStation, int numRoutes, int numOffers, int numRequests, String fileName, ModelLogic modelLogic)
    {
        Optional<SingleTransPoolMap> singleTransPoolMap = transPoolMapList.stream()
                .filter(singleTransPoolMap1 -> singleTransPoolMap1.getUserName().equals(userName)).findFirst();
        if(singleTransPoolMap.isPresent())
        {
           singleTransPoolMap.get().setMapName(mapName);
           singleTransPoolMap.get().setFileName(fileName);
           singleTransPoolMap.get().setNumRoutes(numRoutes);
           singleTransPoolMap.get().setNumStation(numStation);
           singleTransPoolMap.get().setNumRequests(numRequests);
           singleTransPoolMap.get().setNumOffers(numOffers);
           singleTransPoolMap.get().setModelLogic(modelLogic);
        }
    }


}
