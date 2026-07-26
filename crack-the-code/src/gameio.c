
#include "game.h"
#include "platform.h"
#include <stdint.h>

#define SCR_X_KEYB 20
#define SCR_Y_KEYB 190
#define BALL_SIZE 16
#define GUESS_STRIDE 18

void Game_renderGuessRow(int16_t xPos, int16_t yPos, uint16_t const * guessData) {
    int16_t xt = xPos;
    for (unsigned i = 0; i < codeSize; i++, xt += GUESS_STRIDE) {
        uint16_t thisGuess = guessData[i];
        if (thisGuess == 0xFFFF) {
            continue;
        }
        OamMan_SpriteX = xt;
        OamMan_SpriteY = yPos;
        OamMan_TileId = 2;
        OamMan_Flags = 0x31 | (thisGuess << 1);
        OamMan_addSprite();
    }
}

void Game_renderGuessResult(int16_t xPos, int16_t yPos, uint8_t const * resultData) {
    for (unsigned i = 0; i < codeSize; i++, xPos += 10) {
        uint8_t result = resultData[i];
        OamMan_SpriteX = xPos;
        OamMan_SpriteY = yPos;
        if (result == GUESSRESULT_CORRECTSPOT) {
            OamMan_TileId = 16;
            OamMan_Flags = 0x30 | (1 << 1);
        } else if (result == GUESSRESULT_INCORRECTSPOT) {
            OamMan_TileId = 17;
            OamMan_Flags = 0x30 | (2 << 1);
        } else {
            OamMan_TileId = 1;
            OamMan_Flags = 0x30 | (0 << 1);
        }
        OamMan_addSprite();
    }
}

void Game_renderState(uint16_t cursorPos) {
    uint16_t tempGuessRow[MAX_CODE_SIZE];
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
    Game_renderGuessRow(SCR_X_KEYB, SCR_Y_KEYB, guessKeyboard);
    for (unsigned i = 0; i < curGuess; i++) {
        for (unsigned j = 0; j < codeSize; j++) {
            tempGuessRow[j] = guesses[i][j];
        }
        Game_renderGuessRow(SCR_X_KEYB, 9 + 18 * i, tempGuessRow);
        Game_renderGuessResult(SCR_X_KEYB + GUESS_STRIDE * codeSize + 8, 9 + 18 * i + 4, guessResult[i]);
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
