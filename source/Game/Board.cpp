#include "Game/Board.h"

void Board::init(SDL_Renderer* r, TextureManager* t){
    resetBoard();
    updatePossibilitySpace(1);

    renderer = r;
    textureManager = t;

    boardTex = textureManager->getTexture("romfs:/assets/board/board.png");
    blackTileTex = textureManager->getTexture("romfs:/assets/board/diskBlack.png");
    whiteTileTex = textureManager->getTexture("romfs:/assets/board/diskWhite.png");
    possTileTex = textureManager->getTexture("romfs:/assets/board/diskPossible.png");
}

void Board::draw(){
    renderTexture(renderer, boardTex, 528, 108);
    for (int x = 0; x < 8; x++){
        for (int y = 0; y < 8; y++) {
            if (state[x][y] == 0){
                if (possSpace[x][y]){
                    renderTexture(renderer, possTileTex, 532+x*108, 112+y*108);
                }
            }else if (state[x][y] == 1){
                renderTexture(renderer, blackTileTex, 532+x*108, 112+y*108);
            }else{
                renderTexture(renderer, whiteTileTex, 532+x*108, 112+y*108);
            }
        }
    }
}

void Board::updatePossibilitySpace(int col){
    for (int x = 0; x < 8; x++){
        for (int y = 0; y < 8; y++){
            possSpace[x][y] = canPlaceTile(x,y,col);
        }
    }
}