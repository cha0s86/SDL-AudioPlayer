#define SDL_MAIN_HANDLED
#include <iostream>
#include <filesystem>
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

// Window constants
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Font size
#define FONT_SIZE 64

using namespace std;

// Some shitty Mix Chunk??? IDK what it does lol
Mix_Chunk* audioSample;

char* dropped_file_path;

int PlaySoundFromPath(char* dropped_file_path) {
	
	// Set up the audio stream (This is more important)
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
	
	// Set result to Mix_AllocateChannels for testing...
	Mix_AllocateChannels(4);
	
	// Setup path
	std::filesystem::path path(dropped_file_path);

	// Convert path to string...
	const char* fileName = path.filename().string().c_str();

	// Print loading message...
	// std::cout << "Loading file: " << fileName << std::endl;

	// Load waveforms (Important)
	audioSample = Mix_LoadWAV(fileName);

	Mix_PlayChannel(-1, audioSample, 0);

	return true;
}

int main() {

	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	SDL_Window* window = SDL_CreateWindow("My Window", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

	TTF_Init();

	//this opens a font style and sets a size
	TTF_Font* myFont = TTF_OpenFont("OpenSans.ttf", FONT_SIZE);

	// this is the color in rgb format,
	// maxing out all would give you the color white,
	// and it will be your text's color
	SDL_Color white = {255, 255, 255};

	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first
	SDL_Surface* messageSurface = TTF_RenderText_Solid(myFont, "Drop your audio files here", white); 

	// now you can convert it into a texture
	SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);

	// (0,0) is on the top left of the window/screen,
	// think a rect as the text's box,
	// that way it would be very simple to understand
	SDL_Rect messageRect; //create a rect
	messageRect.x = 0;  //controls the rect's x coordinate 
	messageRect.y = WINDOW_HEIGHT/2-FONT_SIZE/2; // controls the rect's y coordinte
	messageRect.w = WINDOW_WIDTH; // controls the width of the rect
	messageRect.h = FONT_SIZE; // controls the height of the rect

	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

	while (true) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				SDL_FreeSurface(messageSurface);
				SDL_DestroyTexture(messageTexture);
				SDL_DestroyWindow(window);
				SDL_Quit();
				break;
			}
			if (event.type == SDL_DROPFILE) {
				dropped_file_path = event.drop.file;
				// Play audio code here
				PlaySoundFromPath(dropped_file_path);
				SDL_free(dropped_file_path);
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
	
		// Now since it's a texture, you have to put RenderCopy
		// in your game loop area, the area where the whole code executes
		// you put the renderer's name first, the Message,
		// the crop size (you can ignore this if you don't want
		// to dabble with cropping), and the rect which is the size
		// and coordinate of your texture
		SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);
	
		// Render present buffer
		SDL_RenderPresent(renderer);
	}

	// Don't forget to free your surface and texture
    	Mix_CloseAudio();
    	SDL_Quit();

	return 0;
}
