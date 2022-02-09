#include "Game/Game.h"

Game::Game(){

}

void Game::init(SDL_Renderer* r, TextureManager* t, AudioPlayer* mp, PadState* padPtr){
	srand(time(0));

	renderer = r;

	textureManager = t;

	audioPlayer = mp;
	audioPlayer->playMusic("romfs:/assets/music/placeholder.mp3");
	
	pad = padPtr;

    cursorTex = textureManager->getTexture("romfs:/assets/boardCursor.png");

    // Init reversi board
    board.init(r, t);
}

void Game::startGame(int againstCPU){
    // Not against CPU but against other player
    if (againstCPU == 0){
        currentPlayer = 1;
    }
}

void Game::draw(){
    board.draw();
    renderTexture(renderer, cursorTex, 528+cX*108, 108+cY*108);
}

void Game::update(){
	u32 kDown = padGetButtonsDown(pad);
	u32 kHeld = padGetButtons(pad);

    updateCursor(kDown);
    if (kDown & HidNpadButton_A){
        if (board.canPlaceTile(cX, cY, currentPlayer)){
            board.placeTile(cX, cY, currentPlayer);
            // TODO: Add CPU player check
            switch (currentPlayer){
                case 1:
                    currentPlayer = 2;
                    break;
                case 2:
                    currentPlayer = 1;
                    break;
            }
            board.updatePossibilitySpace(currentPlayer);
        }
    }
}

void Game::updateCursor(u32 kDown){
    if (kDown & HidNpadButton_AnyUp){
        cY -= 1;
    }
    if (kDown & HidNpadButton_AnyDown){
        cY += 1;
    }
    if (kDown & HidNpadButton_AnyLeft){
        cX -= 1;
    }
    if (kDown & HidNpadButton_AnyRight){
        cX += 1;
    }
    if (cX < 0)
        cX += 8;
    if (cY < 0)
        cY += 8;
    if (cX > 7)
        cX -= 8;
    if (cY > 7)
        cY -= 8;
}