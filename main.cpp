#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include <iostream>

using namespace std;

//Screen Dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool initWindow();
//bool loadMedia();
void close();

//Set window and surface contained by the window
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int main(int argc, char *args[])
{
    if(!initWindow())
    {
        printf("Failed to initalise");
    }
    else
    {
        //loadmedia
        bool quit = false;
        SDL_Event e;
        while(!quit)
        {
            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }
                //Clear screen
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                //Render red square
                SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(renderer, &fillRect);

                //Update screen
                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
    return 0;
}

bool initWindow()
{
    bool success = true;

    //Initalise SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL coould not initalise SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create Window
        window = SDL_CreateWindow("SDL_Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Render screen
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if(renderer == NULL)
            {
                printf("Rendrer could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL Image could not initalise! SDL_Error: %s\n", SDL_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

void close()
{

    //Destroy window
    SDL_DestroyWindow(window);
    //Exit
    SDL_Quit();
}
