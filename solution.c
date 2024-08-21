#include <stdio.h>

double calculateNextPrice();
double calculateDelta();
int doCalculations();
//definitions: arrayName__index1Name_index2Name_..._indexNName

int main(int argc, char** argv) {

    int n, T, c;
    scanf(" %d %d %d", &n, &T, &c);

    double* BuyPrice__buyer = malloc(sizeof(double) * n);
    double* MaxChocolateWeCanSell__buyer = malloc(sizeof(double) * n);
    for (int i = 0; i < n;i++) scanf(" %lf %lf", &BuyPrice__buyer[i], &MaxChocolateWeCanSell__buyer[i]);

    double** CoefficentOfMarketInfluence__buyer_day = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        CoefficentOfMarketInfluence__buyer_day[i] = malloc(sizeof(double) * T);
        for (int i2 = 0; i2 < T;i2++)
            scanf(" %lf", &CoefficentOfMarketInfluence__buyer_day[i][i2]);
    }
    double** RandomNoise__buyer_day = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        RandomNoise__buyer_day[i] = malloc(sizeof(double) * T);
        for (int i2 = 0; i2 < T;i2++)
            scanf(" %lf", &RandomNoise__buyer_day[i][i2]);
    }

    //they like making things complicated, don't they? First "block" is "0 lines" since it has i-1 lines
    double*** CoefficientOfBuyerInfluence__fromBuyer_toBuyer_day = malloc(sizeof(double**) * (n));
    for (int i = 0; i < n; i++) {
        if (i == 0) { CoefficientOfBuyerInfluence__fromBuyer_toBuyer_day[i] = NULL; continue; }
        CoefficientOfBuyerInfluence__fromBuyer_toBuyer_day[i] = malloc(sizeof(double**) * (i - 1));
        for (int i2 = 0; i2 < i - 1;i2++) {
            CoefficientOfBuyerInfluence__fromBuyer_toBuyer_day[i][i2] = malloc(sizeof(double*) * T);
            for (int i3 = 0; i3 < T;i3++)
                scanf(" %lf", &CoefficientOfBuyerInfluence__fromBuyer_toBuyer_day[i][i2][i3]);
        }
    }
    double* CoefficentOfNDaysAgo = malloc(sizeof(double) * T);
    for (int i = 0; i < T;i++) scanf(" %lf", &CoefficentOfNDaysAgo[i]);

    //do the stuff
    int** ChocolatesSold__buyer = malloc(sizeof(int*) * T);
    for (int i = 0;i < T;i++) {
        ChocolatesSold__buyer[i] = malloc(sizeof(int) * n);
        for (int i2 = 0;i2 < n;i2++) ChocolatesSold__buyer[i][i2] = doCalculations();
    }

    //output
    for (int i = 0; i < T;i++) {
        for (int i2 = 0;i < n;i++) { if (i2 != 0)putchar(' ');printf("%d", ChocolatesSold__buyer[i][i2]); }
        putchar('\n');
    }
}