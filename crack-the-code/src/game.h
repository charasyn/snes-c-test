#include <stdint.h>

#define MAX_GUESSES 16
#define MAX_CODE_SIZE 8
#define NUM_COLOURS 6

#define GUESSRESULT_CORRECTSPOT (2)
#define GUESSRESULT_INCORRECTSPOT (1)
#define GUESSRESULT_NOTINPUZZLE (0)

extern uint8_t guesses[MAX_GUESSES][MAX_CODE_SIZE];
extern uint8_t guessResult[MAX_GUESSES][MAX_CODE_SIZE];
extern uint16_t guessKeyboard[MAX_CODE_SIZE];
extern uint16_t code[MAX_CODE_SIZE];
extern uint16_t codeSize;
extern uint16_t curGuess;

uint16_t Game_main(uint16_t _codeSize, uint16_t allowedGuesses);

extern void Game_getUserGuess();
