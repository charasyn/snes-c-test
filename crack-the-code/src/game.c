
#include "game.h"
#include "misc.h"
#include "randxor.h"

uint8_t guesses[MAX_GUESSES][MAX_CODE_SIZE];
uint8_t guessResult[MAX_GUESSES][MAX_CODE_SIZE];
uint16_t guessKeyboard[MAX_CODE_SIZE];
uint16_t code[MAX_CODE_SIZE];
uint16_t codeSize;
uint16_t curGuess;

void Game_updateGuessResult() {
    uint16_t guessResultIdx = 0;
    uint16_t codeCopy[MAX_CODE_SIZE];
    uint16_t guessCopy[MAX_CODE_SIZE];
    for (unsigned i = 0; i < codeSize; i++) {
        codeCopy[i] = code[i];
        guesses[curGuess][i] = (guessCopy[i] = guessKeyboard[i]);
    }
    // Check if code == guess at [i], if so mark a correct spot and clear it
    // from the copy
    for (unsigned i = 0; i < codeSize; i++) {
        if (codeCopy[i] == guessCopy[i]) {
            guessResult[curGuess][guessResultIdx++] = GUESSRESULT_CORRECTSPOT;
            codeCopy[i] = 0xFFFF;
            guessCopy[i] = 0xFFFF;
        }
    }
    if (guessResultIdx == codeSize) {
        return;
    }
    // Sort the codeCopy and guessCopy
    InsertionSort(codeCopy, codeSize);
    InsertionSort(guessCopy, codeSize);
    {
        unsigned iCode = 0, iGuess = 0;
        while (iCode < codeSize && iGuess < codeSize) {
            uint16_t xCode = codeCopy[iCode];
            uint16_t xGuess = guessCopy[iGuess];
            if (xCode == 0xFFFF || xGuess == 0xFFFF) {
                // End of list condition reached; break out since there can be
                // no more guesses in the incorrect spot.
                break;
            }
            if (xCode == xGuess) {
                guessResult[curGuess][guessResultIdx++] = GUESSRESULT_INCORRECTSPOT;
                iCode++;
                iGuess++;
                continue;
            }
            if (xCode >= xGuess) {
                iGuess++;
                continue;
            } else {
                iCode++;
                continue;
            }
        }
    }
    while (guessResultIdx < codeSize) {
        guessResult[curGuess][guessResultIdx++] = GUESSRESULT_NOTINPUZZLE;
    }
}

uint16_t Game_main(uint16_t _codeSize, uint16_t allowedGuesses) {
    uint16_t gameResult = 0;
    if (_codeSize > MAX_CODE_SIZE) return 0xFFFF;
    if (allowedGuesses > MAX_GUESSES) return 0xFFFF;
    codeSize = _codeSize;
    curGuess = 0;
    // initialize code
    for (unsigned i = 0; i < codeSize; i++) {
        uint32_t digitRand = Random_step() * NUM_COLOURS;
        uint16_t digit = (digitRand >> 16);
        code[i] = digit;
    }
    // initialize keyboard
    for (unsigned i = 0; i < codeSize; i++) {
        guessKeyboard[i] = 0xFFFF;
    }

    while (curGuess < allowedGuesses) {
        // Allow user to input guess
        Game_getUserGuess();
        // Compute correctness of guess
        Game_updateGuessResult();
        gameResult = 1;
        for (unsigned i = 0; i < codeSize; i++) {
            if (guessResult[curGuess][i] != GUESSRESULT_CORRECTSPOT) {
                gameResult = 0;
                break;
            }
        }
        if (gameResult) {
            // User cracked the code!
            break;
        }
        // Advance guess to next
        curGuess += 1;
    }
    return gameResult;
}
