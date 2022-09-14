// TODO: get player input
// TODO: implement turns
// TODO: a menu and game over screen

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


bool horzont_won(Marker board[3][3], Marker player) {
    for (uint y = 0; y < 3; y++) {
        bool won = true;

        for (uint x = 0; x < 3; x++)
            if (board[x][y] != player)
                won = false;

        if(won)
            return true;
    }
    return false;
}

bool vert_won(Marker board[3][3], Marker player) {
    for (uint x = 0; x < 3; x++) {
        bool won = true;

        for (uint y = 0; y < 3; y++)
            if (board[x][y] != player)
                won = false;

        if(won)
            return true;
    }
    return false;
}

bool diag_won(Marker board[3][3], Marker player) {
    bool won1 = true;
    bool won2 = true;
    for (uint i = 0; i < 3; i++) {
        if (board[i][i] != player)
            won1 = false;
        if (board[i][2-i] != player)
            won2 = false;

    }
    return won1 || won2;
}

bool player_won(Marker board[3][3], Marker player) {
    if (vert_won(board, player))
        return true;

    if (horzont_won(board, player))
        return true;

    if (diag_won(board, player))
        return true;

    return false;
}

int main(void) {
    Marker board [3][3] = {0};
    board[0][0] = M_O;
    board[1][1] = M_O;
    board[2][2] = M_O;
    board[0][1] = M_X;
    // Marker whose_turn = M_X;
    init();

    while (true) {
        const uint T = frameStart();

        if (keyPressed(SDL_SCANCODE_Q) || keyPressed(SDL_SCANCODE_ESCAPE))
            exit(0);

        Marker won = M_EMPTY;
        if((won = player_won(board, M_X) ? M_X : (player_won(board, M_O) ? M_O : M_EMPTY)) != M_EMPTY){
            printf("%s won!\n", won == M_X ? "X" : "O");
            return 0;
        } else if (is_full(board)) {
            printf("it's a tie game\n");
            return 0;
        }

        draw_board(board);

        frameEnd(T);
    }
    return 0;
}
