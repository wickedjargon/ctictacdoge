#include "DogeLib/Includes.h"

typedef enum {
    M_EMPTY,
    M_X,
    M_O
} Marker;

void draw_board(Marker board[3][3]) {
    Length window_len = getWindowLen();
    int board_length = imin(window_len.x, window_len.y);
    setTextSize(board_length/3);
    const uint thickness = 8;
    const Coord board_top_left = coordOffset(getWindowMid(), iC(-board_length/2, -board_length/2));
    setColor(WHITE);
    for (uint i = 1; i < 3; i++) {
        const Coord top_cord  = coordShift(board_top_left, DIR_R, (board_length/3)*i);
        const Coord left_cord = coordShift(board_top_left, DIR_D, (board_length/3)*i);
        const Length vertical_line_length   = iC(thickness, board_length);
        const Length horizontal_line_length = iC(board_length, thickness);
        fillRectCoordLength(top_cord, vertical_line_length);
        fillRectCoordLength(left_cord, horizontal_line_length);
    }
    for (uint x = 0; x < 3; x++) {
        for (uint y = 0; y < 3; y++) {
            if (board[x][y] == M_X) {
                setTextColor(RED);
                const Offset off = iC((board_length/3)*x, (board_length/3)*y);
                drawTextCoord("X", coordOffset(board_top_left, off));
            } else if (board[x][y] == M_O) {
                setTextColor(BLUE);
                const Offset off = iC((board_length/3)*x, (board_length/3)*y);
                drawTextCoord("O", coordOffset(board_top_left, off));
            }
        }
    }
}

void place_random_marker(Marker board[3][3], Marker marker) {
    int random_x;
    int random_y;
    do {
        random_x = rand() % 3;
        random_y = rand() % 3;
    } while (board[random_x][random_y] != M_EMPTY);
    board[random_x][random_y] = marker;
}

// TODO: `win_check` function: game over function
// x wins, y wins, tie
// M_X, M_O, M_EMPTY

bool is_full(Marker board[3][3]) {
    for (uint x = 0; x < 3; x++) {
        for (uint y = 0; y < 3; y++) {
            if (board[x][y] == M_EMPTY) {
                return false;
            }
        }
    }
    return true;
}

bool horzont_won(Makrer board[3][3], Marker player) {
    for (y = 0; y < 3; y++) {
        bool won = true;

        for (x = 0; x < 3; x++)
            if (board[x][y] != player)
                won = false;

        if(won)
            return true;
    }
    return false;
}

bool player_win(Marker board[3][3], Marker player) {
    if (vert_win(board, player)) {
        return true;
    } else if (horizont_won(board, player)) {
        return true;
    } else if (diag_won(board, player)) {
        return true;
    }

}

int main(void) {
    Marker board [3][3] = {0};
    /* board[0][0] = M_X; */
    /* board[1][1] = M_X; */
    /* board[2][2] = M_X; */
    /* board[0][1] = M_O; */
    Marker whose_turn = M_X;
    init();
    place_random_marker(board, M_X);
    place_random_marker(board, M_O);
    place_random_marker(board, M_X);
    while (1) {
        const uint T = frameStart();
        if (keyPressed(SDL_SCANCODE_Q) || keyPressed(SDL_SCANCODE_ESCAPE)) {
            exit(0);
        }

        draw_board(board);
        frameEnd(T)
    }
    return 0;
}
