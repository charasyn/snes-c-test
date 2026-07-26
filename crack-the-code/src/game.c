
#include <stdint.h>

#include "misc.h"
#include "platform.h"
#include "randxor.h"

#define MAX_GUESSES 16
#define MAX_CODE_SIZE 8
#define NUM_COLOURS 6

uint8_t guesses[MAX_GUESSES][MAX_CODE_SIZE];
uint8_t guessResult[MAX_GUESSES][MAX_CODE_SIZE];
uint16_t guessKeyboard[MAX_CODE_SIZE];
uint16_t code[MAX_CODE_SIZE];
uint16_t codeSize;
uint16_t curGuess;

#define GUESSRESULT_CORRECTSPOT (2)
#define GUESSRESULT_INCORRECTSPOT (1)
#define GUESSRESULT_NOTINPUZZLE (0)

#define SCR_X_KEYB 20
#define SCR_Y_KEYB 190
#define BALL_SIZE 16
#define GUESS_STRIDE 18

void Game_renderState(uint16_t cursorPos) {
    uint16_t xt = cursorPos * GUESS_STRIDE + SCR_X_KEYB;
    OamMan_SpriteX = xt - 3;
    OamMan_SpriteY = SCR_Y_KEYB - 3;
    OamMan_TileId = 0;
    OamMan_Flags = 0x00;
    OamMan_addSprite();
    OamMan_SpriteX = xt + BALL_SIZE - 5;
    OamMan_Flags = 0x40;
    OamMan_addSprite();
    OamMan_SpriteX = xt - 3;
    OamMan_SpriteY = SCR_Y_KEYB + BALL_SIZE - 5;
    OamMan_TileId = 0;
    OamMan_Flags = 0x80;
    OamMan_addSprite();
    OamMan_SpriteX = xt + BALL_SIZE - 5;
    OamMan_Flags = 0xc0;
    OamMan_addSprite();
    xt = SCR_X_KEYB;
    for (unsigned i = 0; i < codeSize; i++, xt += GUESS_STRIDE) {
        uint16_t thisGuess = guessKeyboard[i];
        if (thisGuess == 0xFFFF) {
            continue;
        }
        OamMan_SpriteX = xt;
        OamMan_SpriteY = SCR_Y_KEYB;
        OamMan_TileId = 2;
        OamMan_Flags = 0x31 | (thisGuess << 1);
        OamMan_addSprite();
    }
}

void Game_getUserGuess() {
    uint16_t cursorPos = 0, lastCursorPos = 0;
    uint16_t inputDone = 0;
    Game_renderState(cursorPos);
    Platform_completeFrame();
    while(!inputDone) {
        if (Keys_Pressed & KEY_ADVANCE) {
            inputDone = 1;
            for (unsigned i = 0; i < codeSize; i++) {
                if (guessKeyboard[i] == 0xFFFF) {
                    inputDone = 0;
                    break;
                }
            }
            if (inputDone) {
                return;
            }
        }
        if (Keys_Pressed & KEY_LEFT) {
            cursorPos -= 1;
            if (cursorPos >= codeSize) {
                cursorPos = codeSize - 1;
            }
        }
        if (Keys_Pressed & KEY_RIGHT) {
            cursorPos += 1;
            if (cursorPos >= codeSize) {
                cursorPos = 0;
            }
        }
        if (Keys_Pressed & KEY_DOWN) {
            if ((++guessKeyboard[cursorPos]) >= NUM_COLOURS) {
                guessKeyboard[cursorPos] = 0;
            }
        }
        if (Keys_Pressed & KEY_UP) {
            if ((--guessKeyboard[cursorPos]) >= NUM_COLOURS) {
                guessKeyboard[cursorPos] = NUM_COLOURS - 1;
            }
        }
        Game_renderState(cursorPos);
        Platform_completeFrame();
    }
}

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
                continue;
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
    }
    return gameResult;
}
