#include <stdio.h>

double calculateNextPrice();
double calculateDelta();

int main(int argc, char** argv) {

    int n, T, c;
    scanf(" %d %d %d", &n, &T, &c);

    double* P = malloc(sizeof(double) * n);
    double* L = malloc(sizeof(double) * n);
    for (int i = 0; i < n;i++) scanf(" %lf %lf", &P[i], &L[i]);

    double** k = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        k[i] = malloc(sizeof(double) * T);
        for (int i2 = 0; i2 < T;i2++)
            scanf(" %lf", &k[i][i2]);
    }
    double** noise = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        noise[i] = malloc(sizeof(double) * T);
        for (int i2 = 0; i2 < T;i2++)
            scanf(" %lf", &noise[i][i2]);
    }
    double*** alpha = malloc(sizeof(double**) * (n)); //they like making things complicated, don't they? First "block" is "0 lines" since it has i-1 lines
    for (int i = 0; i < n; i++) {
        if (i == 0) { alpha[i] = NULL; continue; }
        alpha[i] = malloc(sizeof(double**) * (i - 1));
        for (int i2 = 0; i2 < i - 1;i2++) {
            alpha[i][i2] = malloc(sizeof(double*) * T);
            for (int i3 = 0; i3 < T;i3++)
                scanf(" %lf", &alpha[i][i2][i3]);
        }
    }
    double* beta = malloc(sizeof(double) * T);
    for (int i = 0; i < T;i++) scanf(" %lf", &beta[i]);

    //do the stuff
    //output

}