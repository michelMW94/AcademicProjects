package Logic.CustomClasses;

public class TripOfferForPassenger {

    private Integer offerNumber;
    private String ownerName;
    private Integer offerCost;
    private String estimatedArrivalTime;
    private Float passengerAvgFuelUtilization;

    public Integer getOfferNumber() {
        return offerNumber;
    }

    public void setOfferNumber(Integer offerNumber) {
        this.offerNumber = offerNumber;
    }

    public String getOwnerName() {
        return ownerName;
    }

    public void setOwnerName(String ownerName) {
        this.ownerName = ownerName;
    }

    public Integer getOfferCost() {
        return offerCost;
    }

    public void setOfferCost(Integer offerCost) {
        this.offerCost = offerCost;
    }

    public String getEstimatedArrivalTime() {
        return estimatedArrivalTime;
    }

    public void setEstimatedArrivalTime(String estimatedArrivalTime) {
        this.estimatedArrivalTime = estimatedArrivalTime;
    }

    public Float getPassengerAvgFuelUtilization() {
        return passengerAvgFuelUtilization;
    }

    public void setPassengerAvgFuelUtilization(Float passengerAvgFuelUtilization) {
        this.passengerAvgFuelUtilization = passengerAvgFuelUtilization;
    }

    @Override
    public String toString() {
        return "offer Number: " + offerNumber + "\n" +
                "Owner Name: " + ownerName + "\n" +
                "Offer Cost: " + offerCost  + "\n" +
                "Estimated Arrival Time: " + estimatedArrivalTime + "\n" +
                "Passenger Avg Fuel Utilization :" + passengerAvgFuelUtilization ;
    }
}
