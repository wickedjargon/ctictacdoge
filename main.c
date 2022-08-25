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
    const uint thickness = 8;
    const Coord top_left = coordOffset(getWindowMid(), iC(-length/2, -length/2));
    setColor(WHITE);
    for (uint i = 1; i < 3; i++) {
        const Coord top = coordShift(top_left, DIR_R, (length/3)*i);
        const Coord left = coordShift(top_left, DIR_D, (length/3)*i);
        fillRectCoordLength(top, iC(thickness, length));
        fillRectCoordLength(left, iC(length, thickness));
    }
    for (uint x = 0; x < 3; x++) {
        for (uint y = 0; y < 3; y++) {
            if (board[x][y] == M_X) {
                setTextColor(RED);
                const Offset off = iC((length/3)*x, (length/3)*y);

                drawTextCoord("X", coordOffset(top_left, off));

            } else if (board[x][y] == M_X) {
                setTextColor(BLUE);
            }
        }
    }
}

int main(void) {
    Marker board [3][3] = {0};
    board[0][0] = M_X;
    board[1][1] = M_X;
    board[2][2] = M_X;

    init();
    while (1) {
        const uint T = frameStart();

        draw_board(board);
        setTextSize(16);
        setTextColor(WHITE);
        frameEnd(T);
    }
    return 0;
}

