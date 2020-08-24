package Logic.CustomClasses;


public class TripRequest
{


  private String m_Name;
  private Integer OrderNumber;
  private String m_CurrentLocation;
  private String m_Destination;
  private Integer m_DepartureTimeHours;
  private Integer m_DepartureTimeMinutes;
  private TripOfferForPassenger m_MatchTrip;


  public Integer getDepartureTimeMinutes() {
    return m_DepartureTimeMinutes;
  }

  public void setDepartureTimeMinutes(Integer m_DepartureTimeMinutes) {
    this.m_DepartureTimeMinutes = m_DepartureTimeMinutes;
  }

  public String getName() {
    return m_Name;
  }
  public void setName(String value) {
    m_Name = value;
  }

  public String getCurrentLocation() {
    return m_CurrentLocation;
  }
  public void setCurrentLocation(String value) {
    m_CurrentLocation = value;
  }

  public String getDestination() {
    return m_Destination;
  }
  public void setDestination(String value) {
    m_Destination = value;
  }

  public Integer getDepartureTimeHours() {
    return m_DepartureTimeHours;
  }

  public void setDepartureTimeHours(Integer m_DepartureTimeHours) {
    this.m_DepartureTimeHours = m_DepartureTimeHours;
  }

  public TripOfferForPassenger getMatchTrip() {
    return m_MatchTrip;
  }

  public void setMatchTrip(TripOfferForPassenger m_MatchTrip) {
    this.m_MatchTrip = m_MatchTrip;
  }

  public Integer getOrderNumber() {
    return OrderNumber;
  }

  public void setOrderNumber(Integer orderNumber) {
    OrderNumber = orderNumber;
  }

}