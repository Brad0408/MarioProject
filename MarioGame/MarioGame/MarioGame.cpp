#include <iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_mixer.h>

#include "constants.h"
#include "Commons.h"
#include "Texture2D.h"

//Global
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Texture2D* g_texture = nullptr;

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
        //did the window get created?
        if (g_window == nullptr)
        {
            //window failed
            cout << "Window was not created. Error: " << SDL_GetError();
            return false;
        }
    }

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

    //Load the backgorund texture
    g_texture = new Texture2D(g_renderer);

    if (!g_texture->LoadFromFile("Images/test.bmp"))
    {
        return false;
    }

}

void Render()
{
    //Clear the screen
    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(g_renderer);

    g_texture->Render(Vector2D(), SDL_FLIP_NONE);

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

    //Release the texture
    delete g_texture;
    g_texture = nullptr;
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
            Render();
            quit = Update();
        }
    }

    CloseSDL();

    return 0;
}
