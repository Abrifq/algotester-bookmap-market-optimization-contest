#include <stdio.h>
#include <string.h>
#include <math.h>

double calculateNextPrice(double currentPrice, double priceDelta);
double calculateDelta(int buyer, int day);
int doCalculations();
int getRemainingBuyerBuyCapacity(int buyer, int onDay);
int getRemainingBoxes(int onDay);
//definitions: arrayName__index1Name_index2Name_..._indexNName

int Buyers, Days, BoxesOfChocolate;
double** BuyPrice__buyer_day;
int* MaxChocolateWeCanSell__buyer;
double** CoefficentOfMarketInfluence__buyer_day;
double** RandomNoise__buyer_day;
double*** CoefficientOfBuyerInfluence__fromBuyer_toBuyer_day;
double* CoefficentOfNDaysAgo;
int** ChocolatesSold__day_buyer;
int main(int argc, char** argv) {

    scanf(" %d %d %d", &Buyers, &Days, &BoxesOfChocolate);

    BuyPrice__buyer_day = malloc(sizeof(double*) * Buyers);
    MaxChocolateWeCanSell__buyer = malloc(sizeof(int) * Buyers);
    for (int i = 0; i < Buyers;i++) {
        BuyPrice__buyer_day[i] = malloc(sizeof(double) * Days);
        memset(&BuyPrice__buyer_day[i], 0, sizeof(double) * Days); //just in case we read it

        scanf(" %lf %d", &BuyPrice__buyer_day[i][0], &MaxChocolateWeCanSell__buyer[i]);
    }

    CoefficentOfMarketInfluence__buyer_day = malloc(sizeof(double*) * Buyers);
    for (int i = 0; i < Buyers; i++) {
        CoefficentOfMarketInfluence__buyer_day[i] = malloc(sizeof(double) * Days);
        for (int i2 = 0; i2 < Days;i2++)
            scanf(" %lf", &CoefficentOfMarketInfluence__buyer_day[i][i2]);
    }
    RandomNoise__buyer_day = malloc(sizeof(double*) * Buyers);
    for (int i = 0; i < Buyers; i++) {
        RandomNoise__buyer_day[i] = malloc(sizeof(double) * Days);
        for (int i2 = 0; i2 < Days;i2++)
            scanf(" %lf", &RandomNoise__buyer_day[i][i2]);
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
    CoefficentOfNDaysAgo = malloc(sizeof(double) * Days);
    for (int day = 0; day < Days;day++) scanf(" %lf", &CoefficentOfNDaysAgo[day]);

    //do the stuff
    ChocolatesSold__day_buyer = malloc(sizeof(int*) * Days);
    for (int day = 0;day < Days;day++) {
        ChocolatesSold__day_buyer[day] = malloc(sizeof(int) * Buyers);
        for (int i2 = 0;i2 < Buyers;i2++) ChocolatesSold__day_buyer[day][i2] = doCalculations();
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
    return (BuyPrice__buyer_day[buyer][day] * (1 - (1 / ((__DBL_EPSILON__, (CoefficentOfMarketInfluence__buyer_day[buyer][day] * (ChocolatesSold__day_buyer)))))))
        + (RandomNoise__buyer_day[buyer][day] * BuyPrice__buyer_day[buyer][day])
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