
#include "../src/game.c"
#include "../src/misc.c"
#include "../src/randxor.c"

void Game_getUserGuess() {}

#include <assert.h>

#define R_Correct (GUESSRESULT_CORRECTSPOT)
#define R_Kinda (GUESSRESULT_INCORRECTSPOT)
#define R_Wrong (GUESSRESULT_NOTINPUZZLE)

void makeGuess(int guessNum, int a, int b, int c, int d) {
    guessKeyboard[0] = a;
    guessKeyboard[1] = b;
    guessKeyboard[2] = c;
    guessKeyboard[3] = d;
    Game_updateGuessResult();
    assert(guesses[guessNum][0] == a);
    assert(guesses[guessNum][1] == b);
    assert(guesses[guessNum][2] == c);
    assert(guesses[guessNum][3] == d);
}

void checkResult(int guessNum, int a, int b, int c, int d) {
    assert(guessResult[guessNum][0] == a);
    assert(guessResult[guessNum][1] == b);
    assert(guessResult[guessNum][2] == c);
    assert(guessResult[guessNum][3] == d);
}

int main() {
    codeSize = 4;
    code[0] = 3;
    code[1] = 5;
    code[2] = 1;
    code[3] = 2;
    curGuess = 0;
    makeGuess(0, 3, 2, 1, 0);
    assert(codeSize == 4);
    assert(code[0] == 3);
    assert(code[1] == 5);
    assert(code[2] == 1);
    assert(code[3] == 2);
    checkResult(0, R_Correct, R_Correct, R_Kinda, R_Wrong);
    return 0;
}
