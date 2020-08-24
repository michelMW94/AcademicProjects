package Logic.CustomClasses;


import Logic.Exceptions.FileNotFoundException;
import Logic.Exceptions.NonXmlFileException;
import Logic.SystemEngine.*;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;
import java.io.File;
import java.time.LocalTime;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

public class TranspoolLogic {

    public static final String FILE_NAME = "ex1-small.xml";
    public static final int TEN = 10;
    public static final int ONE_HOUR = 60;
    public static final int ONE_DAY = 24;

    private TransPool TransPoolData;
    public List<Integer> currentTravelMatchedOffers;
    private ObjectFactory factory = new ObjectFactory();
    private TripRequests tripRequests = factory.createTripRequests();

    public TransPool getTransPoolData() { return TransPoolData; }
    public TripRequests getTripRequests() {
        return tripRequests;
    }
    public void setTripRequests(TripRequests value) {
        tripRequests = value;
    }

    public void makeMatchToRequest(List<TripOfferForPassenger> matchedOffers , Integer matchSelection, Integer tripRequestNumber)
    {
        if(matchSelection != 0) {
            Optional<TripOfferForPassenger>  offerToMatch = matchedOffers.stream()
                    .filter(tripOfferForPassenger -> tripOfferForPassenger.getOfferNumber().equals(matchSelection)).findFirst();
            Optional<TripRequest> requestToMatch = getTripRequestsByNumber(tripRequestNumber);

            requestToMatch.get().setMatchTrip(offerToMatch.get());
            ModifyTripCapacity(matchSelection);

        }
        currentTravelMatchedOffers = null;
    }

    public List<TripRequest> findMatchedRequests(TransPoolTrip transPoolTrip) {
        List<TripRequest> matchedRequests= tripRequests.get().stream()
                .filter(tripRequest -> tripRequest.getMatchTrip() != null)
                .filter(tripRequest -> tripRequest.getMatchTrip().getOfferNumber().equals(transPoolTrip.getOrderNumber())).collect(Collectors.toList());
        return matchedRequests;
    }

    private void ModifyTripCapacity(Integer matchSelection) {
        Optional<TransPoolTrip> tripToModify = TransPoolData.getPlannedTrips().getTransPoolTrip()
                .stream().filter(transPoolTrip -> transPoolTrip.getOrderNumber() == matchSelection).findFirst();
        tripToModify.get().setCapacity(tripToModify.get().getCapacity() - 1);
    }
    public void setCurrentTravelMatchedOffersNumbers(List<TripOfferForPassenger> matchedOffers) {
        currentTravelMatchedOffers = matchedOffers.stream()
                .map(tripOfferForPassenger -> tripOfferForPassenger.getOfferNumber()).collect(Collectors.toList());
    }
    public void ReadFromXml(File file) throws Exception {
        /** Inserting system data from xml file*/
            TransPoolData = fromXmlFileToObject(file);

    }

    private TransPool fromXmlFileToObject(File file) throws  Exception {

        try {

            /**Creates TransPool system from given xml file*/
            JAXBContext jaxbContext = JAXBContext.newInstance(TransPool.class);
            Unmarshaller jaxbUnmarshaller = jaxbContext.createUnmarshaller();
            TransPool transPool = (TransPool) jaxbUnmarshaller.unmarshal(file);
            /**Checks if the given TransPool system after creation*/
            checkTransPoolAfterCreation(transPool);
            transPool.getPlannedTrips().SetOrderNumber();
            return transPool;
        } catch (JAXBException jaxBException) {
            System.out.println(jaxBException.getLinkedException().getMessage());
            throw jaxBException;
        }
        catch (Exception exception) {
            throw exception;
        }

    }

    private static void checkTransPoolAfterCreation(TransPool transPool)  throws Exception{
        try {
            transPool.getMapDescriptor().getMapBoundries().checkMapBoundries();
            transPool.getMapDescriptor().checkStops();
            transPool.getMapDescriptor().checkPaths();
            transPool.checkTransPoolTrips();
        }
        catch (Exception e) {
            throw e;
        }
    }

    public void checkFileBeforeTransPoolCreation (File file) throws Exception {
        file.isFile();
        if(file.getPath().endsWith(".xml") == false)
            throw new NonXmlFileException(file.getName());
        else if(file.exists() == false)
            throw new FileNotFoundException(file.getName());
    }



    public List<Stop> getStops()
    {
        return TransPoolData.getMapDescriptor().getStops().getStop();
    }

    public TripOfferForPassenger CreateNewOffersForPassenger(TripRequest tripRequest, TransPoolTrip transPoolTrip ) {
        TripOfferForPassenger tripOfferForPassenger  = factory.createTripOfferForPassenger();
        tripOfferForPassenger.setOfferNumber(transPoolTrip.getOrderNumber());
        tripOfferForPassenger.setOwnerName(transPoolTrip.getOwner());
        String requestRoute = createSubRoute(transPoolTrip.getRoute().getPath(),tripRequest.getCurrentLocation(),tripRequest.getDestination());
        tripOfferForPassenger.setOfferCost(calculateRideCost(requestRoute,transPoolTrip.getPPK()));
        String arrivalTimeToStation = getArrivalTimeToStationTrip(tripRequest.getDepartureTimeHours(), tripRequest.getDepartureTimeMinutes(), requestRoute);
        tripOfferForPassenger.setEstimatedArrivalTime(arrivalTimeToStation);
        tripOfferForPassenger.setPassengerAvgFuelUtilization(getFuelAvgUtilization(requestRoute));
        return  tripOfferForPassenger;
    }

    public void CreateNewRequest(String i_PassengerName,String CurrentLocation, String Destination, Integer DepartureTimeHours , Integer DepartureTimeMinutes) {

        TripRequest NewTrip = factory.createTripRequest();
        NewTrip.setName(i_PassengerName);
        NewTrip.setCurrentLocation(CurrentLocation);
        NewTrip.setDestination(Destination);
        NewTrip.setDepartureTimeHours(DepartureTimeHours);
        NewTrip.setDepartureTimeMinutes(DepartureTimeMinutes);
        NewTrip.setOrderNumber(tripRequests.get().size());
        tripRequests.AddNewRequest(NewTrip);
    }

    public void CreateNewTranspoolTrip(String Owner,String Route, Integer HourStart , Integer ppk , Integer capacity) {
        TransPoolTrip newTranspoolTrip = factory.createTransPoolTrip();
        Logic.SystemEngine.Route route = factory.createRoute();
        Scheduling scheduling = factory.createScheduling();
        route.setPath(Route);
        scheduling.setHourStart(HourStart);

        newTranspoolTrip.setOrderNumber(TransPoolData.getPlannedTrips().getTransPoolTrip().size());
        newTranspoolTrip.setOwner(Owner);
        newTranspoolTrip.setRoute(route);
        newTranspoolTrip.setScheduling(scheduling);
        newTranspoolTrip.setPPK(ppk);
        newTranspoolTrip.setCapacity(capacity);
        TransPoolData.getPlannedTrips().AddNewTranspoolTrip(newTranspoolTrip);

    }

    public boolean stopIsExists(String name)
    {
        List<Stop> StopList = getStops();
        boolean ReturnValue = StopList.stream()
                .anyMatch(stop -> stop.getName().equals(name));
        if(!ReturnValue) {
            System.out.println("The Stop that you choose didn't exists, please enter a stop from the list above");
        }
        return ReturnValue;
    }

    public boolean requestNumberExsits(Integer input) {
        List<TripRequest> tripRequests = getTripRequests().getUnmatchedRTripRequests();
        boolean ReturnValue = tripRequests.stream().anyMatch(request -> request.getOrderNumber().equals(input) );
        if(!ReturnValue) {
            System.out.println("The Passenger Number that you choose doesn't exists, please enter a passenger number from the list above");
        }
        return ReturnValue;

    }
    
    public boolean matchedOffersChoose(Integer input) {
        boolean isOfferSelected = currentTravelMatchedOffers.stream().anyMatch(offerNumber -> offerNumber.equals(input));
        if(input == -1 || isOfferSelected == true)
            return true;
        else 
            return false;
    }
    
    public boolean maxNumberOffers(Integer input) {
        if (input >=1 && input <= getTransPoolData().getPlannedTrips().getTransPoolTrip().size())
            return true;
        else
            return false;
    }


    public boolean RouteCheck(String Route)
    {
        boolean RetVal;

        if(Route.contains(",")) {
            RetVal = createRouteStopsStringsList(Route).stream()
                    .allMatch(stop -> stopIsExists(stop));
        }
       else {
            System.out.println("you have enter only one stop");
            RetVal = false;
        }

       return RetVal;
    }


    private  List<String> createRouteStopsStringsList (String stopStringsList) {
        return Arrays.asList(stopStringsList.trim().split(",")).stream()
                .map(w -> w.trim())
                .collect(Collectors.toList());
    }

    public int calculateRideCost(String route,int ppk){
        int pathsSum = 0;
        List<String> routesList = createRouteStopsStringsList(route);
        for(int i = 0; i < routesList.size()-1; i++) {
            pathsSum += TransPoolData.getMapDescriptor().getPaths().FindPath(routesList.get(i),routesList.get(i+1)).getLength();
        }

        return ppk*pathsSum;
    }
    public float getFuelAvgUtilization(String route) {
        float sumFuelUtilization = 0;
        int numberOfPaths = 0;
        List<String> routesList = createRouteStopsStringsList(route);
        for(int i = 0; i < routesList.size()-1; i++) {
            Path foundedPath = TransPoolData.getMapDescriptor().getPaths().FindPath(routesList.get(i),routesList.get(i+1));
            numberOfPaths++;
            sumFuelUtilization += foundedPath.getFuelConsumption();
        }
        return sumFuelUtilization/ numberOfPaths;
    }

    public String getDepartureTimeString(int timeHours, int timeMinutes) {
        String timeHoursString, timeMinutesString;
        LocalTime localTime = LocalTime.of(timeHours,timeMinutes);
        return localTime.toString();
    }
    private int calculateTripDurationInMinutes(String route){
        int rideDurationMinutes = 0;
        List<String> routesList = createRouteStopsStringsList(route);
        for(int i = 0; i < routesList.size()-1; i++) {
            Path foundedPath = TransPoolData.getMapDescriptor().getPaths().FindPath(routesList.get(i),routesList.get(i+1));
            rideDurationMinutes += (foundedPath.getLength() * 60)/foundedPath.getSpeedLimit();
        }
        return rideDurationMinutes;

    }
    public String getArrivalTimeToStationTrip(int departTimeHours, int departTimeMinutes, String route){
        int rideDurationMinutes = calculateTripDurationInMinutes(route);
        LocalTime localTime = LocalTime.of(departTimeHours,departTimeMinutes);
        localTime = localTime.plusMinutes(rideDurationMinutes);
        return localTime.toString();
    }

    public List<TripOfferForPassenger> findMatchedTripOffers(Integer numberOfOptionsOffers, Integer tripRequestNumber) {
        Optional<TripRequest> tripRequest = getTripRequestsByNumber(tripRequestNumber);
        List<TripOfferForPassenger> matchedOffers= TransPoolData.getPlannedTrips().getTransPoolTrip().stream()
                .filter(transPoolTrip -> transPoolTrip.getCapacity() > 1)
                .filter(transPoolTrip -> validForTripRequest(tripRequest.get() , transPoolTrip))
                .map(transPoolTrip -> CreateNewOffersForPassenger(tripRequest.get(),transPoolTrip)).collect(Collectors.toList());
        return modifyOffersWithNumberOfOptions(matchedOffers, numberOfOptionsOffers);
    }

    private  List<TripOfferForPassenger> modifyOffersWithNumberOfOptions(List<TripOfferForPassenger> matchedOffers, Integer numberOfOptionsOffers )
    {
        if(matchedOffers.size() > numberOfOptionsOffers)
        {
            for(int i = matchedOffers.size() -1; i > numberOfOptionsOffers -1 ; i--)
                matchedOffers.remove(matchedOffers.size()-1);
        }
        return matchedOffers;

    }
    public Optional<TripRequest> getTripRequestsByNumber(Integer tripRequestNumber) {
       return  getTripRequests().get().stream().filter(tripRequest1 -> tripRequest1.getOrderNumber().equals(tripRequestNumber)).findFirst();
    }
    public boolean validForTripRequest (TripRequest tripRequest, TransPoolTrip transPoolTrip ) {
        String pathUntilRequestDepartureStation;
        List<String> stopsList = createRouteStopsStringsList(transPoolTrip.getRoute().getPath());
        Optional<String> departStation = findStopInRoute( stopsList, tripRequest.getCurrentLocation());
        Optional<String> arrivalStation = findStopInRoute( stopsList, tripRequest.getDestination());
        if(isRouteValidForRequest(stopsList,departStation,arrivalStation)) {
            pathUntilRequestDepartureStation = createSubRoute (transPoolTrip.getRoute().getPath(), stopsList.get(0), tripRequest.getCurrentLocation());
            String requestDepartureTime = getDepartureTimeString(tripRequest.getDepartureTimeHours(),tripRequest.getDepartureTimeMinutes());
            String offerDepartureTime = getArrivalTimeToStationTrip(transPoolTrip.getScheduling().getHourStart(),0,pathUntilRequestDepartureStation);
            if(offerDepartureTime.equals(requestDepartureTime))
            return  true;
        }
        return false;
    }
    private  Optional<String> findStopInRoute( List<String> stopsList, String stopToFind) {
        return stopsList.stream().filter(s -> s.equals(stopToFind)).findFirst();
    }

    private boolean isRouteValidForRequest(List<String> stopsList,  Optional<String> departStation, Optional<String> arrivalStation ){
        if (departStation.isPresent() && arrivalStation.isPresent()) {
            if (stopsList.indexOf(departStation.get()) < stopsList.indexOf(arrivalStation.get()))
                return true;
        }
       return false;
    }

    private String createSubRoute (String route, String departureStation, String arrivalStation) {
        if(departureStation.equals(arrivalStation))
            return departureStation;
        List<String> routesList = createRouteStopsStringsList(route);
        int departIndex = routesList.indexOf(departureStation);
        int arrivalIndex = routesList.indexOf(arrivalStation);
        routesList = routesList.subList(departIndex ,arrivalIndex + 1);
        return String.join(",",routesList);
    }
}

