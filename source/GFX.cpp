#include "GFX.h"

void renderTexture(SDL_Renderer* renderer, image* tex, int destX, int destY){
    int w, h;
    SDL_QueryTexture(tex->texture, NULL, NULL, &w, &h);
	SDL_Rect dest;
	dest.x = destX;
	dest.y = destY;
    dest.w = w;
    dest.h = h;

	SDL_RenderCopy(renderer, tex->texture, NULL, &dest);
}

void renderTextureRotated(SDL_Renderer* renderer, image tex, int destX, int destY, double rotation){
    int w, h;
    SDL_QueryTexture(tex.texture, NULL, NULL, &w, &h);
	SDL_Rect dest;
	dest.x = destX-w/2;
	dest.y = destY-h/2;
	dest.w = w;
	dest.h = h;

	SDL_RenderCopyEx(renderer, tex.texture, NULL, &dest, rotation, NULL, SDL_FLIP_NONE);
}

void renderTextureScaled(SDL_Renderer* renderer, image tex, int destX, int destY, double scale){
    int w, h;
    SDL_QueryTexture(tex.texture, NULL, NULL, &w, &h);
	SDL_Rect dest;
	dest.x = destX;
	dest.y = destY;
	dest.w = round(w*scale);
	dest.h = round(h*scale);

	SDL_RenderCopy(renderer, tex.texture, NULL, &dest);
}

void renderTextureScaledRotated(SDL_Renderer* renderer, image tex, int destX, int destY, double scale, double rotation){	
    int w, h;
    SDL_QueryTexture(tex.texture, NULL, NULL, &w, &h);
	SDL_Rect dest;
	dest.x = destX-(w*scale)/2;
	dest.y = destY-(h*scale)/2;
	dest.w = round(w*scale);
	dest.h = round(h*scale);

	SDL_RenderCopyEx(renderer, tex.texture, NULL, &dest, rotation, NULL, SDL_FLIP_NONE);
}

void renderTextureScaledRotatedAlpha(SDL_Renderer* renderer, image tex, int destX, int destY, double scale, double rotation, double alpha, SDL_Rect* srcRect = nullptr){
	SDL_Rect dest;
	if (srcRect == nullptr){
		//Destination needs to have same size as texture
		int w, h;
    	SDL_QueryTexture(tex.texture, NULL, NULL, &w, &h);

		dest.x = destX-(w*scale)/2;
		dest.y = destY-(h*scale)/2;
		dest.w = round(w*scale);
		dest.h = round(h*scale);
	}else{
		dest.x = destX-srcRect->w*scale/2;
		dest.y = destY-srcRect->h*scale/2;
		dest.w = round(srcRect->w*scale);
		dest.h = round(srcRect->h*scale);
	}

	SDL_SetTextureAlphaMod(tex.texture, round(alpha*255));

	SDL_RenderCopyEx(renderer, tex.texture, srcRect, &dest, rotation, NULL, SDL_FLIP_NONE);
	SDL_SetTextureAlphaMod(tex.texture, 255);
}

void renderTextureCentered(SDL_Renderer* renderer, image tex, int destX, int destY){
	int w, h;
    SDL_QueryTexture(tex.texture, NULL, NULL, &w, &h);
	SDL_Rect dest;
	dest.x = destX-w/2;
	dest.y = destY-h/2;
    dest.w = w;
    dest.h = h;

	SDL_RenderCopy(renderer, tex.texture, NULL, &dest);
}

void renderFadeOverlay(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 1920;
	rect.h = 1080;

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &rect);
}

void renderText(SDL_Renderer* renderer, TTF_Font* fnt, int destX, int destY, string s){
    SDL_Color black = {0, 0, 0};  
    renderColorText(renderer, fnt, destX, destY, s, black);
}

void renderColorText(SDL_Renderer* renderer, TTF_Font* fnt, int destX, int destY, string s, SDL_Color col){
	if (fnt == NULL)
        return;
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended_Wrapped(fnt, s.c_str(), col, 1920-destX); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect dest;
	dest.x = destX;
	dest.y = destY;
	dest.w = surfaceMessage->w;
	dest.h = surfaceMessage->h;

    SDL_RenderCopy(renderer, Message, NULL, &dest); 

    //Free surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void renderTextCentered(SDL_Renderer* renderer, TTF_Font* fnt, int destX, int destY, string s){
	SDL_Color black = {0, 0, 0};  
    renderColorTextCentered(renderer, fnt, destX, destY, s, black);
}

void renderColorTextCentered(SDL_Renderer* renderer, TTF_Font* fnt, int destX, int destY, string s, SDL_Color col){
	int w,h;
	TTF_SizeText(fnt, s.c_str(), &w, &h);
	renderColorText(renderer, fnt, destX - (w/2), destY, s, col);
}