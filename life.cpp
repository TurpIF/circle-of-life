#include "life.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

void changeMyLife(bool *** myLife, unsigned long width, unsigned long height)
{
    bool ** newLife = new bool * [width];
    for (unsigned long i = 0; i < width; i++) {
        newLife[i] = new bool [height];
        for (unsigned long j = 0; j < height; j++) {
            unsigned int nbN = 0;
            if (i >= 1 && (*myLife)[i - 1][j])  nbN++;
            if (j >= 1 && (*myLife)[i][j - 1])  nbN++;
            if (i < width - 1 && (*myLife)[i + 1][j])  nbN++;
            if (j < height - 1 && (*myLife)[i][j + 1])  nbN++;
            if (i >= 1 && j >= 1 && (*myLife)[i - 1][j - 1])  nbN++;
            if (i < width - 1 && j >= 1 && (*myLife)[i + 1][j - 1])  nbN++;
            if (i >= 1 && j < height - 1 && (*myLife)[i - 1][j + 1])  nbN++;
            if (i < width - 1 && j < height - 1 && (*myLife)[i + 1][j + 1])  nbN++;

            if (nbN == 3) newLife[i][j] = true;
            else if (nbN == 2) newLife[i][j] = (*myLife)[i][j];
            else    newLife[i][j] = false;
        }
    }

    for (unsigned long i = 0; i < width; i++)
        delete[] (*myLife)[i];
    delete[] *myLife;

    *myLife = newLife;

    /*for (unsigned int x = 0; x < width; x++) {
        for (unsigned int y = 0; y < height; y++) {
            (*myLife)[x][y] = std::rand() % 4 == 0;
        }
    }*/
}
