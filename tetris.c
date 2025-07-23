#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define PIECE_SIZE 4
#define GAME_SPEED 300000  // microseconds

// Tetris pieces (7 standard pieces)
int pieces[7][4][4][4] = {
    // I piece
    {{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
     {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
     {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}},
     {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}},
    
    // O piece
    {{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
     {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
     {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
     {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}},
    
    // T piece
    {{{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
     {{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
     {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}},
    
    // S piece
    {{{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
     {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
     {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}},
    
    // Z piece
    {{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
     {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
     {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}},
    
    // J piece
    {{{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
     {{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}}},
    
    // L piece
    {{{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}},
     {{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
     {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}}
};

typedef struct {
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    int current_piece;
    int current_rotation;
    int current_x;
    int current_y;
    int score;
    int lines_cleared;
    int level;
} GameState;

void init_ncurses() {
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(FALSE);
}

void cleanup_ncurses() {
    endwin();
}

void init_game(GameState *game) {
    memset(game->board, 0, sizeof(game->board));
    game->current_piece = rand() % 7;
    game->current_rotation = 0;
    game->current_x = BOARD_WIDTH / 2 - 2;
    game->current_y = 0;
    game->score = 0;
    game->lines_cleared = 0;
    game->level = 1;
}

int is_valid_position(GameState *game, int piece, int rotation, int x, int y) {
    for (int py = 0; py < PIECE_SIZE; py++) {
        for (int px = 0; px < PIECE_SIZE; px++) {
            if (pieces[piece][rotation][py][px]) {
                int board_x = x + px;
                int board_y = y + py;
                
                if (board_x < 0 || board_x >= BOARD_WIDTH || 
                    board_y >= BOARD_HEIGHT ||
                    (board_y >= 0 && game->board[board_y][board_x])) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void place_piece(GameState *game) {
    for (int py = 0; py < PIECE_SIZE; py++) {
        for (int px = 0; px < PIECE_SIZE; px++) {
            if (pieces[game->current_piece][game->current_rotation][py][px]) {
                int board_x = game->current_x + px;
                int board_y = game->current_y + py;
                if (board_y >= 0) {
                    game->board[board_y][board_x] = game->current_piece + 1;
                }
            }
        }
    }
}

int clear_lines(GameState *game) {
    int lines_cleared = 0;
    
    for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
        int full = 1;
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (!game->board[y][x]) {
                full = 0;
                break;
            }
        }
        
        if (full) {
            // Move all lines above down
            for (int move_y = y; move_y > 0; move_y--) {
                for (int x = 0; x < BOARD_WIDTH; x++) {
                    game->board[move_y][x] = game->board[move_y - 1][x];
                }
            }
            // Clear top line
            for (int x = 0; x < BOARD_WIDTH; x++) {
                game->board[0][x] = 0;
            }
            lines_cleared++;
            y++; // Check this line again
        }
    }
    
    return lines_cleared;
}

void spawn_new_piece(GameState *game) {
    game->current_piece = rand() % 7;
    game->current_rotation = 0;
    game->current_x = BOARD_WIDTH / 2 - 2;
    game->current_y = 0;
}

void draw_game(GameState *game) {
    clear();
    
    // Create display board
    int display[BOARD_HEIGHT][BOARD_WIDTH];
    memcpy(display, game->board, sizeof(display));
    
    // Add current piece to display
    for (int py = 0; py < PIECE_SIZE; py++) {
        for (int px = 0; px < PIECE_SIZE; px++) {
            if (pieces[game->current_piece][game->current_rotation][py][px]) {
                int board_x = game->current_x + px;
                int board_y = game->current_y + py;
                if (board_x >= 0 && board_x < BOARD_WIDTH && 
                    board_y >= 0 && board_y < BOARD_HEIGHT) {
                    display[board_y][board_x] = game->current_piece + 1;
                }
            }
        }
    }
    
    mvprintw(0, 0, "TETRIS - Ubuntu-BSD Edition");
    mvprintw(1, 0, "Score: %d  Lines: %d  Level: %d", 
             game->score, game->lines_cleared, game->level);
    
    // Draw border and board
    mvprintw(3, 0, "+");
    for (int i = 0; i < BOARD_WIDTH; i++) printw("-");
    printw("+");
    
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        mvprintw(4 + y, 0, "|");
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (display[y][x]) {
                printw("#");
            } else {
                printw(" ");
            }
        }
        printw("|");
    }
    
    mvprintw(4 + BOARD_HEIGHT, 0, "+");
    for (int i = 0; i < BOARD_WIDTH; i++) printw("-");
    printw("+");
    
    mvprintw(6 + BOARD_HEIGHT, 0, "Controls:");
    mvprintw(7 + BOARD_HEIGHT, 0, "Arrow Keys = move/rotate");
    mvprintw(8 + BOARD_HEIGHT, 0, "Space = drop, Q = quit");
    mvprintw(9 + BOARD_HEIGHT, 0, "A/D = left/right (alt)");
    
    refresh();
}

int main() {
    srand(time(NULL));
    init_ncurses();
    atexit(cleanup_ncurses);
    
    GameState game;
    init_game(&game);
    
    clock_t last_drop = clock();
    int drop_interval = 500000; // microseconds
    
    while (1) {
        draw_game(&game);
        
        // Handle input (non-blocking)
        int key = getch();
        if (key != ERR) {
            switch (key) {
                case 'q':
                case 'Q':
                case 27: // ESC
                    goto game_over;
                    
                case KEY_LEFT:
                case 'a':
                case 'A':
                    if (is_valid_position(&game, game.current_piece, 
                                        game.current_rotation, 
                                        game.current_x - 1, game.current_y)) {
                        game.current_x--;
                    }
                    break;
                    
                case KEY_RIGHT:
                case 'd':
                case 'D':
                    if (is_valid_position(&game, game.current_piece, 
                                        game.current_rotation, 
                                        game.current_x + 1, game.current_y)) {
                        game.current_x++;
                    }
                    break;
                    
                case KEY_DOWN:
                case 's':
                case 'S':
                    if (is_valid_position(&game, game.current_piece, 
                                        game.current_rotation, 
                                        game.current_x, game.current_y + 1)) {
                        game.current_y++;
                    }
                    break;
                    
                case KEY_UP:
                case 'w':
                case 'W': {
                    int new_rotation = (game.current_rotation + 1) % 4;
                    if (is_valid_position(&game, game.current_piece, 
                                        new_rotation, 
                                        game.current_x, game.current_y)) {
                        game.current_rotation = new_rotation;
                    }
                    break;
                }
                
                case ' ': // Space bar for instant drop
                    while (is_valid_position(&game, game.current_piece, 
                                           game.current_rotation, 
                                           game.current_x, game.current_y + 1)) {
                        game.current_y++;
                    }
                    break;
            }
        }
        
        // Auto drop timing
        clock_t now = clock();
        if ((now - last_drop) * 1000000 / CLOCKS_PER_SEC > drop_interval) {
            if (is_valid_position(&game, game.current_piece, 
                                game.current_rotation, 
                                game.current_x, game.current_y + 1)) {
                game.current_y++;
            } else {
                // Piece has landed
                place_piece(&game);
                
                int lines = clear_lines(&game);
                if (lines > 0) {
                    game.lines_cleared += lines;
                    game.score += lines * 100 * game.level;
                    game.level = game.lines_cleared / 10 + 1;
                    
                    // Increase speed
                    drop_interval = 500000 - (game.level - 1) * 50000;
                    if (drop_interval < 100000) drop_interval = 100000;
                }
                
                spawn_new_piece(&game);
                
                // Check game over
                if (!is_valid_position(&game, game.current_piece, 
                                     game.current_rotation, 
                                     game.current_x, game.current_y)) {
                    break;
                }
            }
            last_drop = now;
        }
        
        usleep(GAME_SPEED);
    }
    
game_over:
    clear();
    mvprintw(10, 5, "GAME OVER!");
    mvprintw(12, 5, "Final Score: %d", game.score);
    mvprintw(13, 5, "Lines Cleared: %d", game.lines_cleared);
    mvprintw(14, 5, "Level Reached: %d", game.level);
    mvprintw(16, 5, "Thanks for playing Ubuntu-BSD Tetris!");
    mvprintw(17, 5, "Created by funtech64 - may God bless you and change your day!! github.com/funtech64/tetris");
    mvprintw(19, 5, "Press any key to exit...");
    refresh();
    
    nodelay(stdscr, FALSE);  // Re-enable blocking for final keypress
    getch();
    
    return 0;
}
