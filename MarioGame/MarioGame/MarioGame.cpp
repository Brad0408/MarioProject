#include <iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_mixer.h>

#include "constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

//Global
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;

Uint32 g_old_time;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();



//Setup SDL
bool InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL did not initalise. Error: " << SDL_GetError();
        return false;
    }
    else
    {
        //setup passed so we create window
        g_window = SDL_CreateWindow("Games Engine Creation",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

        if (g_renderer != nullptr)
        {
            //init PNG loading
            int imageFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imageFlags) & imageFlags))
            {
                cout << "SDL_Image could not initalise. Error: " << IMG_GetError();
                return false;
            }
        }
        else
        {
            cout << "Renderer could not initalise. Error: " << SDL_GetError();
            return false;
        }

        //did the window get created?
        if (g_window == nullptr)
        {
            //window failed
            cout << "Window was not created. Error: " << SDL_GetError();
            return false;
        }
        return true;
    }

}

void Render()
{
    //Clear the screen
    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(g_renderer);

    game_screen_manager->Render();

    //Update the screen
    SDL_RenderPresent(g_renderer);
}



void CloseSDL()
{
    //Release the window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    IMG_Quit();
    SDL_Quit();

    //Release the renderer
    SDL_DestroyRenderer(g_renderer);
    g_renderer = nullptr;

    //Destroy the game screen manager
    delete game_screen_manager;
    game_screen_manager = nullptr;
}

bool Update()
{
    Uint32 new_time = SDL_GetTicks();

    //Event Handler
    SDL_Event e;

    //Get Events
    SDL_PollEvent(&e);

    //Handle The Events
    switch (e.type)
    {
        //Click the 'X' to quit
    case SDL_QUIT:
        return true;
        break;

    case SDL_KEYUP:
        switch (e.key.keysym.sym)
        {
            //Press BackSpace to quit
        case SDLK_BACKSPACE:
            return true;
            break;
        }
    }

    game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
    g_old_time = new_time;

    return false;
}

int main(int argc, char* args[])
{
    if (InitSDL())
    {
        game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
        //Set the time
        g_old_time = SDL_GetTicks();

        bool quit = false;

        //Game Loop
        while (!quit)
        {
            Render();
            quit = Update();
        }
    }

    CloseSDL();

    return 0;
}
