package Menu;

import Logic.CustomClasses.*;
import Logic.SystemEngine.Stop;
import Logic.SystemEngine.TransPoolTrip;

import javax.xml.bind.JAXBException;
import java.io.File;
import java.util.List;
import java.util.Scanner;
import java.util.function.Predicate;


public class MenuUIForm
{

    /** Fields */
    private MenuItemList m_Menu;
    TranspoolLogic SystemLogic;


    public void InitMenu() {
        /** Creation of the Menu Itemes */
       m_Menu = new MenuItemList(){
           {
               add(new MenuItem("Create New TransPoll from Xml file",() -> ReadNewXml()));
               add(new MenuItem("Create New Travel Request",() -> PrintNewRideRequest()));
               add(new MenuItem("Print Travel Offers",() -> PrintAllTravelOffers()));
               add(new MenuItem("Print Travel Requests",() -> PrintTravelRequests()));
               add(new MenuItem("Find Travel Match",() -> {
                   try {
                       CreateTravelMatch();
                   } catch (Exception e) {
                       e.printStackTrace();
                   }
               }));
               add(new MenuItem("Create New Travel offer ",() -> CreateNewTravelOffer()));
           }
       };

    }

    public void checkTransPoolExists() throws Exception {
        if(SystemLogic == null)
            throw new Exception("Exception: Choose number 1 in the main Menu to load A transPool before choosing this action");
    }
    public void CreateTravelMatch() {
        try {
            checkTransPoolExists();
            Integer numberOfOptionsOffers, tripRequestNumber;
            TripRequests tripRequests = SystemLogic.getTripRequests();
            if (tripRequests.get().size() == 0)
                System.out.println("There are no Travel Request");
            else {
                List<TripRequest> tripRequests1 = tripRequests.getUnmatchedRTripRequests();
                if (tripRequests1.isEmpty())
                    System.out.println("There are no un-Matched Travel Request");
                else CreateTravelMatchImp(tripRequests1);
            }
        }
        catch (Exception e) { System.out.println(e.getMessage()); }
    }

    private void CreateTravelMatchImp( List<TripRequest> tripRequests) {
        Integer numberOfOptionsOffers, tripRequestNumber, matchSelection = null;
        System.out.println("Here are the travel requests that weren't matched: ");
        tripRequests.forEach(this::printRequest);
        tripRequestNumber = GetIntInput("please Enter Trip Request Number : ", SystemLogic::requestNumberExsits);
        numberOfOptionsOffers = GetIntInput("please Enter what's the max Offers you want to get : ", SystemLogic::maxNumberOffers);
        List<TripOfferForPassenger> matchedOffers = SystemLogic.findMatchedTripOffers( numberOfOptionsOffers, tripRequestNumber);
        if(matchedOffers.size() == 0) {
            System.out.println("There is no Travel Matches for this Request");
        }
        else
        {
            System.out.println("Your Travel Matched Offers: " );
            matchedOffers.stream().forEach(this::PrintMatchedTravelOffers);
            SystemLogic.setCurrentTravelMatchedOffersNumbers(matchedOffers);
            matchSelection = GetIntInput("please Enter the Offer's Number you would like (Press -1 for none): ", SystemLogic::matchedOffersChoose);
            SystemLogic.makeMatchToRequest(matchedOffers,matchSelection, tripRequestNumber);
        }
    }
    private void PrintMatchedTravelOffers(TripOfferForPassenger matchedOffer) {
        System.out.println(matchedOffer.toString() );
    }
    public void Run() throws Exception {
        InitMenu();
        Execute();
    }

    public void Execute()
    {
        m_Menu.Run();
    }

    public void PrintAllTravelOffers(){
        try {
            checkTransPoolExists();
            System.out.println("Available travel offers: \n");
            SystemLogic.getTransPoolData().getPlannedTrips().getTransPoolTrip().forEach(this::PrintTravelOffer);
        }    catch (Exception e) { System.out.println(e.getMessage()); }
    }

    private void PrintTravelOffer(TransPoolTrip transPoolTrip) {
        System.out.println("Travel Offer number: " + transPoolTrip.getOrderNumber());
        System.out.println("Owner's name: " + transPoolTrip.getOwner());
        System.out.println("Travel path: "  +transPoolTrip.getRoute().toString());
        System.out.println("Travel cost: "  + SystemLogic.calculateRideCost(transPoolTrip.getRoute().getPath(),transPoolTrip.getPPK()));
        System.out.println("Departure time: " + SystemLogic.getDepartureTimeString(transPoolTrip.getScheduling().getHourStart(), 0));
        System.out.println("Arrival time: " + SystemLogic.getArrivalTimeToStationTrip(transPoolTrip.getScheduling().getHourStart(),0,transPoolTrip.getRoute().getPath()));
        System.out.println("Travel capacity: " + transPoolTrip.getCapacity());
        System.out.println("Fuel average utilization: " + SystemLogic.getFuelAvgUtilization(transPoolTrip.getRoute().getPath()));
        System.out.println("\n");
        PrintTransPoolTripMatchedRequests(transPoolTrip);
    }
    private void PrintTransPoolTripMatchedRequests(TransPoolTrip transPoolTrip) {
        List<TripRequest> matchedRequests = SystemLogic.findMatchedRequests(transPoolTrip);
        if(matchedRequests.size() > 0) {
            System.out.println("Passengers Numbers: ");
            matchedRequests.forEach(this::printMatchedRequestInfo);
        }
    }
    private void printMatchedRequestInfo(TripRequest tripRequest) {
        System.out.println("Passenger number: " + tripRequest.getOrderNumber());
        System.out.println("Passenger Departure Station: " + tripRequest.getCurrentLocation());
        System.out.println("Passenger Arrival Station: " + tripRequest.getDestination());
    }
    /** Need check */
    private File GetFile (String Msg)  throws Exception {
        Scanner scanner = new Scanner(System.in);
        String Input;
        File file;
        System.out.println(Msg);
        Input = scanner.nextLine();
        if (Input.equals("Q")) {
            System.out.println("Thank you for using our App");
            System.exit(0);
        } else {
            file = new File(Input);
            SystemLogic.checkFileBeforeTransPoolCreation(file);
            return file;
        }
        return null;
    }
    private void CreateTransPoolFromXml (File file) throws Exception {
        /** Inserting system data from xml file*/
        SystemLogic.ReadFromXml(file);

        /** Informing that the xml found correct*/
        System.out.println("The xml file was loaded without any exception. \n");
    }


    public void ReadNewXml()
    {
        while(!ReadFromXmlFile()){}
    }

    public boolean ReadFromXmlFile() {

        try
        {
            SystemLogic = new TranspoolLogic();
            File file;
            /** Creation of  xml File  */
            file = GetFile("Enter Xml File Name or press Q then Enter to quit the program: ");
            /** Creation of  new TransPool System */
            CreateTransPoolFromXml(file);
            return true;

        }
        catch (JAXBException jaxBException) {
            System.out.println(jaxBException.getLinkedException().getMessage());
            return false;
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
            return false;
        }
    }
    /** */

    public void PrintNewRideRequest()
    {
        try {
            checkTransPoolExists();

            String PassengerName, CurrentStop, Destination;
            Integer DepartureTimeHours, DepartureTimeMinutes;

            ShowAllStops();
            PassengerName = GetInput("please Enter Passenger Name : ", IOCheck::stringIsAName);
            CurrentStop = GetInput("please Enter your current stop:\nNotice: choose only from the stop list above, and write exactly as wrote there including upper case", SystemLogic::stopIsExists);
            Destination = GetInput("please Enter your Destination : ", SystemLogic::stopIsExists);
            while (Destination.equals(CurrentStop)) {
                System.out.println("you have choosed The Same Current and destination stops, please Select Again");
                CurrentStop = GetInput("please Enter your current stop, choose a stop from the list above", SystemLogic::stopIsExists);
                Destination = GetInput("please Enter your Destination : ", SystemLogic::stopIsExists);
            }
            DepartureTimeHours = GetIntInput("please Enter your Departure time hour (0 - 23) : ", IOCheck::HoursCheck);
            DepartureTimeMinutes = GetIntInput("please Enter your Departure time minutes (0 - 59) : ", IOCheck::MinutesCheck);
            SystemLogic.CreateNewRequest(PassengerName, CurrentStop, Destination, DepartureTimeHours, DepartureTimeMinutes);
            System.out.println("The Request has been Added");
        }  catch (Exception e) { System.out.println(e.getMessage()); }

    }

    public void CreateNewTravelOffer() {
        String Owner, Route;
        Integer DayStart , HourStart, ppk, Capacity;
        ShowAllStops();
        Owner = GetInput("please Enter Driver Name : ", IOCheck::stringIsAName );
        Route = GetInput("please Enter your Route : \n Notice: Choose Stops only from the list above and write exactly as wrote there including upper case ", SystemLogic::RouteCheck);
        HourStart = GetIntInput("please Enter your Departure time hour (0 - 23) : ", IOCheck::HoursCheck);
        ppk = GetIntInput("Please enter price per kilometer", IOCheck::ppkCheck);
        Capacity = GetIntInput("Please enter Capacity", IOCheck::HoursCheck);

        SystemLogic.CreateNewTranspoolTrip(Owner,Route ,HourStart,ppk,Capacity);
        System.out.println("Travel offer has been added");
    }

    private void printRequest(TripRequest request) {
        /** Can Use String format */

        System.out.println("Request number -  " + request.getOrderNumber());
        System.out.println("Name: " + request.getName());
        System.out.println("Current Location : " + request.getCurrentLocation());
        System.out.println("Destination: " + request.getDestination());
        System.out.println("DepartureTime : " + SystemLogic.getDepartureTimeString(request.getDepartureTimeHours(),request.getDepartureTimeMinutes()));
        System.out.println("\n");
        if(request.getMatchTrip() != null)
        {
            System.out.println(request.getMatchTrip().toString() );
        }
    }

    public void PrintTravelRequests() {
        try {
            checkTransPoolExists();
            TripRequests tripRequests = SystemLogic.getTripRequests();
            if (tripRequests.get().size() == 0)
                System.out.println("There is no Travel Request");
            else {
                tripRequests.get()
                        .stream()
                        .forEach((request) -> printRequest(request));
            }
        } catch (Exception e) { System.out.println(e.getMessage()); }
    }

  private String GetInput(String Msg , Predicate<String> predicate)
  {
      Scanner scanner = new Scanner(System.in);
      String Input;

      do {
          System.out.println(Msg);
          Input = scanner.nextLine();

      } while (!predicate.test(Input));

      return Input;
  }

    private Integer GetIntInput(String Msg , Predicate<Integer> predicate)
    {
        Scanner scanner = new Scanner(System.in);
        Integer Input;
        System.out.println(Msg);
        do {
            while (!scanner.hasNextInt()) {
                System.out.println("Please enter only Integer number");
                scanner.next();
            }
            Input = scanner.nextInt();

        } while (!predicate.test(Input));

        return Input;
    }
    private  void ShowAllStops() {
        int counter = 1;
        System.out.println("The stops are :");
        List<Stop> StopList = SystemLogic.getStops();
        for(Stop singleStop: StopList) {
            System.out.println(counter + "- " + singleStop);
            counter++;
        }
    }
}

