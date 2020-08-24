//
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, v2.2.8-b130911.1802 
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a> 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2020.04.16 at 03:58:25 PM IDT 
//


package Logic.SystemEngine;

import Logic.Exceptions.PathException;
import Logic.Exceptions.RouteException;

import javax.xml.bind.annotation.*;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;


/**
 * <p>Java class for anonymous complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType>
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element ref="{}MapDescriptor"/>
 *         &lt;element ref="{}PlannedTrips" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {
    "mapDescriptor",
    "plannedTrips"
})
@XmlRootElement(name = "TransPool")
public class TransPool {

    @XmlElement(name = "MapDescriptor", required = true)
    protected MapDescriptor mapDescriptor;
    @XmlElement(name = "PlannedTrips")
    protected PlannedTrips plannedTrips;


    /**
     * Gets the value of the mapDescriptor property.
     * 
     * @return
     *     possible object is
     *     {@link MapDescriptor }
     *     
     */
    public MapDescriptor getMapDescriptor() {
        return mapDescriptor;
    }

    /**
     * Sets the value of the mapDescriptor property.
     * 
     * @param value
     *     allowed object is
     *     {@link MapDescriptor }
     *     
     */
    public void setMapDescriptor(MapDescriptor value) {
        this.mapDescriptor = value;
    }

    /**
     * Gets the value of the plannedTrips property.
     * 
     * @return
     *     possible object is
     *     {@link PlannedTrips }
     *     
     */
    public PlannedTrips getPlannedTrips() {
        return plannedTrips;
    }

    /**
     * Sets the value of the plannedTrips property.
     * 
     * @param value
     *     allowed object is
     *     {@link PlannedTrips }
     *     
     */
    public void setPlannedTrips(PlannedTrips value) {
        this.plannedTrips = value;
    }

    public void  checkTransPoolTrips() throws Exception{
        /**check trips routes*/
        checkRoutes();
        /**modify trips recurrences to 'OneTime'*/
        plannedTrips.transPoolTrip.stream().forEach(t -> t.scheduling.setRecurrences("OneTime"));

    }

    public void  checkRoutes() throws Exception{
        for(TransPoolTrip transPoolTrip: plannedTrips.transPoolTrip) {
            String pathString = transPoolTrip.route.path;
            List<String> route = Arrays.asList(pathString.trim()
                    .split(",")).stream().map(w-> w.trim()).collect(Collectors.toList());
            checkPathStation(route,pathString);
            checkPathExistence(route,pathString);
            duplicationStationInPath(route,pathString);
            }
    }
    private void  checkPathStation (List<String> paths, String pathString) throws Exception {
        Optional<String> unFoundedStation = paths.stream()
                .filter(station -> mapDescriptor.stops.findStopByName(station) == false).findFirst();
        if((unFoundedStation.isPresent()))
            throw new RouteException(unFoundedStation.get(),pathString, "doesn't exists in the system");

    }

    private void duplicationStationInPath (List<String> paths, String pathString) throws Exception {
        Optional<String> duplicatedFoundedStation = paths.stream()
                .filter(s -> Collections.frequency(paths,s) >1).findFirst();
        if(duplicatedFoundedStation.isPresent())
            throw new RouteException(duplicatedFoundedStation.get(),pathString, "appears more than ones");
    }
    private void checkPathExistence (List<String> paths, String pathString) throws Exception{
        for(int i = 0; i < paths.size()-1; i++) {
            if(mapDescriptor.paths.FindPath(paths.get(i),paths.get(i+1)) == null)
                throw new PathException(paths.get(i),paths.get(i+1),"doesn't exist in the system");

        }
    }
}
