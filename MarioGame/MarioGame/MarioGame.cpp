#include <iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_mixer.h>

#include "constants.h"

//Global
SDL_Window* g_window = nullptr;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();

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
        //did the window get created?
        if (g_window == nullptr)
        {
            //window failed
            cout << "Window was not created. Error: " << SDL_GetError();
            return false;
        }
    }
}

void CloseSDL()
{
    //release the window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    IMG_Quit();
    SDL_Quit();
}

bool Update()
{
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
    return false;
}

int main(int argc, char* args[])
{
    if (InitSDL())
    {
        bool quit = false;

        //Game Loop
        while (!quit)
        {
            quit = Update();
        }
    }

    CloseSDL();

    return 0;
}