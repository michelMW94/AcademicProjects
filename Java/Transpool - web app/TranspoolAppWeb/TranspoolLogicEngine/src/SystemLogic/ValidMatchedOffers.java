package SystemLogic;

import java.util.LinkedList;
import java.util.Optional;

public class ValidMatchedOffers {
    private LinkedList<SingleValidMatchedOffers> validOffers = new LinkedList<SingleValidMatchedOffers>();

    public LinkedList<SingleValidMatchedOffers> getValidOffers() {
        return validOffers;
    }

    public void setValidOffers(LinkedList<SingleValidMatchedOffers> validOffers) {
        this.validOffers = validOffers;
    }

    public void AddOffer(SingleValidMatchedOffers validOffer)
    {
        validOffers.add(validOffer);
    }

    public SingleValidMatchedOffers FindSingleOfferById(Integer index)
    {
        Optional<SingleValidMatchedOffers> singleValidMatchedOffersOption = validOffers
                .stream()
                .filter(singleValidMatchedOffers -> singleValidMatchedOffers.getOfferNumber().equals(index) == true).findFirst();
        if(singleValidMatchedOffersOption.isPresent())
            return singleValidMatchedOffersOption.get();
        return null;
    }
}
