#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>

#include "texture_loader.hpp"
#include "consts.h"

int main( int argc, char* args[] )
{
    // init
    SDL_Window* window = NULL;
    
    SDL_Surface* windowSurface = NULL;

    SDL_Renderer* renderer = NULL;
    
    SDL_Event e;
    
    LTexture bgTexture;
    LTexture tTexture;
    Mix_Music *bgMusic = NULL;
    TTF_Font* gFont = NULL;

    
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        window = SDL_CreateWindow( "Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            windowSurface = SDL_GetWindowSurface(window);
           
            if(renderer == NULL) {
                printf("Renderer could not be initialized! SDL_Error: %s\n", SDL_GetError());
            }else{
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
                
                int image_flag = IMG_INIT_PNG;
               
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                }
                
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                }
            }
        }
    }
   
    // load texture
    bgTexture.loadFromFile(renderer, "./SpaceShooter/Assets/bg.png");
    bgMusic = Mix_LoadMUS("./SpaceShooter/Assets/bgMusic.mp3");
    gFont = TTF_OpenFont( "./SpaceShooter/Assets/lazy.ttf", 28 );
    SDL_Color tColor = {0, 0, 0};
    tTexture.loadFromRendereredText(gFont, renderer, "nmsl?", tColor);
    
    // game loop
    bool quit = false;
    
    bgTexture.setAlpha(50);
    
    while(!quit) {
        
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }
        if( Mix_PlayingMusic() == 0 )
        {
            //Play the music
            Mix_PlayMusic( bgMusic, -1 );
        }
        
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        
        tTexture.render(renderer, 100, 100, 70, 70);
        
        bgTexture.render(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        
        SDL_RenderPresent(renderer);
    }

    // free operations
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    tTexture.free();
    TTF_CloseFont(gFont);
    gFont = NULL;
    window = NULL;
    renderer = NULL;
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

