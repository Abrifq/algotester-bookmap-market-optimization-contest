#include <stdio.h>
#include <string.h>
#include <math.h>

//thank god that:
//god gave me some brain power to attempt this
//Zeal exists, which helps me significantly on looking up C functions
//bracket pair colors are a thing in VSCode
//and also variable renaming, and also auto parenthesis closing
//and also god haven't let me go insane... yet... or did he? (cue VSauce sfx)

double calculateNextPrice(double currentPrice, double priceDelta);
double calculateDelta(int buyer, int day);
int getRemainingBuyerBuyCapacity(int buyer, int onDay);
int getRemainingBoxes(int onDay);

int Buyers, Days, BoxesOfChocolate;
//definitions: arrayName__index1Name_index2Name_..._indexNName
double** BuyPrice__buyer_day;
double** PriceDelta__buyer_day; //omg i need this in the formula AAAAAAA
int* MaxChocolateWeCanSell__buyer;
double** CoefficentOfMarketInfluence__buyer_day;
double** RandomNoise__buyer_day;
double*** CoefficientOfBuyerInfluence__fromBuyer_toBuyer_day;
double* CoefficentOfThePreviousOrders__daysAgo;
int** ChocolatesSold__day_buyer;
int main(int argc, char** argv) {

    scanf(" %d %d %d", &Buyers, &Days, &BoxesOfChocolate);

    BuyPrice__buyer_day = malloc(sizeof(double*) * Buyers);
    MaxChocolateWeCanSell__buyer = malloc(sizeof(int) * Buyers);
    for (int buyer = 0; buyer < Buyers;buyer++) {
        BuyPrice__buyer_day[buyer] = malloc(sizeof(double) * Days);
        memset(&BuyPrice__buyer_day[buyer], 0, sizeof(double) * Days); //just in case we read it

        scanf(" %lf %d", &BuyPrice__buyer_day[buyer][0], &MaxChocolateWeCanSell__buyer[buyer]);
    }
    PriceDelta__buyer_day = malloc(sizeof(double*) * Buyers);
    for (int buyer = 0;buyer < Buyers;buyer++) {
        PriceDelta__buyer_day[buyer] = malloc(sizeof(double) * Days);
        memset(&PriceDelta__buyer_day[buyer], 0, sizeof(double) * Days);
    }

    CoefficentOfMarketInfluence__buyer_day = malloc(sizeof(double*) * Buyers);
    for (int buyer = 0; buyer < Buyers; buyer++) {
        CoefficentOfMarketInfluence__buyer_day[buyer] = malloc(sizeof(double) * Days);
        for (int day = 0; day < Days;day++)
            scanf(" %lf", &CoefficentOfMarketInfluence__buyer_day[buyer][day]);
    }
    RandomNoise__buyer_day = malloc(sizeof(double*) * Buyers);
    for (int buyer = 0; buyer < Buyers; buyer++) {
        RandomNoise__buyer_day[buyer] = malloc(sizeof(double) * Days);
        for (int day = 0; day < Days;day++)
            scanf(" %lf", &RandomNoise__buyer_day[buyer][day]);
    }

    //they like making things complicated, don't they? First "block" is "0 lines" since it has i-1 lines
    CoefficientOfBuyerInfluence__fromBuyer_toBuyer_day = malloc(sizeof(double**) * (Buyers));
    for (int i = 0; i < Buyers; i++) {
        if (i == 0) { CoefficientOfBuyerInfluence__fromBuyer_toBuyer_day[i] = NULL; continue; }
        CoefficientOfBuyerInfluence__fromBuyer_toBuyer_day[i] = malloc(sizeof(double**) * (i - 1));
        for (int i2 = 0; i2 < i - 1;i2++) {
            CoefficientOfBuyerInfluence__fromBuyer_toBuyer_day[i][i2] = malloc(sizeof(double*) * Days);
            for (int i3 = 0; i3 < Days;i3++)
                scanf(" %lf", &CoefficientOfBuyerInfluence__fromBuyer_toBuyer_day[i][i2][i3]);
        }
    }
    CoefficentOfThePreviousOrders__daysAgo = malloc(sizeof(double) * Days);
    for (int day = 0; day < Days;day++) scanf(" %lf", &CoefficentOfThePreviousOrders__daysAgo[day]);

    //do the stuff
    ChocolatesSold__day_buyer = malloc(sizeof(int*) * Days);
    for (int day = 0;day < Days;day++) {
        ChocolatesSold__day_buyer[day] = malloc(sizeof(int) * Buyers);
        memset(ChocolatesSold__day_buyer[day], 0, sizeof(int) * Buyers);
    }

    //output
    for (int day = 0; day < Days;day++) {
        for (int buyer = 0;day < Buyers;day++) { if (buyer != 0)putchar(' ');printf("%d", ChocolatesSold__day_buyer[day][buyer]); }
        putchar('\n');
    }
}

double calculateNextPrice(double currentPrice, double PriceChange) {
    return currentPrice + PriceChange;
}

//i moved all of the variables to global to avoid passing it HERE again, lol.
//4 seconds is already too low, i don't think we can afford copy-by-value that much.
//also i thank god auto brackets and bracket pair colorization exists.
double calculateDelta(int buyer, int day) {
    double buyerInfluenceSum = 0, previousDaysSum = 0;
    for (int previousBuyer = 0; previousBuyer < buyer; previousBuyer++)
        buyerInfluenceSum += (
            (CoefficientOfBuyerInfluence__fromBuyer_toBuyer_day[buyer][previousBuyer][day] * PriceDelta__buyer_day[previousBuyer][day])
            / log(
                fmax(__DBL_EPSILON__,
                    fabs(BuyPrice__buyer_day[buyer][day] - BuyPrice__buyer_day[previousBuyer][day])
                )
            ));
    for (int daysAgo = 0; daysAgo < day - 1; daysAgo++)
        previousDaysSum += CoefficentOfThePreviousOrders__daysAgo[daysAgo] * ChocolatesSold__day_buyer[day - daysAgo][buyer];

    return
        (
            BuyPrice__buyer_day[buyer][day]
            * (
                1 -
                (1 /
                    (
                        pow(__DBL_EPSILON__,
                            (CoefficentOfMarketInfluence__buyer_day[buyer][day] * (
                                ChocolatesSold__day_buyer[day][buyer] / getRemainingBuyerBuyCapacity(buyer, day)
                                )
                                )
                        )
                        )
                    )
                )
            )
        + (
            RandomNoise__buyer_day[buyer][day]
            * BuyPrice__buyer_day[buyer][day]
            )
        + buyerInfluenceSum
        + previousDaysSum;
}

int getRemainingBoxes(int onDay) {
    int sum = 0;
    for (int buyer = 0; buyer < Buyers;buyer++)
        for (int day = 0;day < onDay;day++)sum += ChocolatesSold__day_buyer[day][buyer];
    return BoxesOfChocolate - sum;
}

int getRemainingBuyerBuyCapacity(int buyer, int onDay) {
    int sum = 0;
    for (int day = 0;day < onDay;day++)sum += ChocolatesSold__day_buyer[day][buyer];
    return MaxChocolateWeCanSell__buyer[buyer] - sum;
}