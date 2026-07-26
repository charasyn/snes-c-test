#include "misc.h"
void InsertionSort(uint16_t * data, uint16_t count) {
    uint16_t numSorted = 1;
    uint16_t lastMax = data[0];
    uint16_t lastRead;
    while (numSorted < count) {
        lastRead = data[numSorted];
        if (lastMax <= lastRead) {
            numSorted += 1;
            lastMax = lastRead;
            continue;
        }
        // lastRead is less than lastMax
        // Find where in the sorted values to insert it
        uint16_t i = numSorted-1;
        uint16_t toInsert = lastRead;
        data[numSorted] = lastMax;
        while (i != 0) {
            lastRead = data[i-1];
            if (lastRead <= toInsert) {
                // Found the spot
                break;
            }
            data[i] = lastRead;
            i -= 1;
        }
        data[i] = toInsert;
        numSorted += 1;
    }
    return;
}
