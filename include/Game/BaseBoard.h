#ifndef REVERSI_NX_BASEBOARD_H
#define REVERSI_NX_BASEBOARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "GFX.h"
#include "TextureManager.h"

class BaseBoard {
    public:
        BaseBoard();
        // 0 = empty, 1 = white, 2 = black
        int state[8][8];
        bool canPlaceTile(int x, int y, int col);
        void placeTile(int x, int y, int col);
        void resetBoard();
    private:
        void fillDirection(int x, int y, int dx, int dy, int length, int col);
};

#endif //REVERSI_NX_BASEBOARD_H
