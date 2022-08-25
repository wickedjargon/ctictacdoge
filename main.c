#include "DogeLib/Includes.h"

typedef enum {
    M_EMPTY,
    M_X,
    M_O
} Marker;

void draw_board(Marker board[3][3]) {
    Length window_len = getWindowLen();
    int length = imin(window_len.x, window_len.y);
    setTextSize(length/3);
    for (uint x = 0; x < 3; x++) {
        for (uint y = 0; y < 3; y++) {
            if (board[x][y] == M_X) {
                setColor(RED);
            }

        }
    }
}

int main(void) {
    int w = 4;
    int* x = &w;
    *x = 10;
    Marker board [3][3] = {0};
    printf("%p \n%i\n", (void *) x, *x);
    printf("%i\n", w);
    init();
    while (1) {
        const uint T = frameStart();
        draw_board(board);
        setTextSize(16);
        setTextColor(WHITE);
        drawTextCenteredCoord("hello world", getWindowMid());
        frameEnd(T);
    }
    return 0;
}

