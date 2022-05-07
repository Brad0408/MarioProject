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
Mix_Music* g_music = nullptr;

Uint32 g_old_time;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void LoadMusic(string musicPath);


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
        //Initalise the mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            cout << "Mixer could not init. Error: " << Mix_GetError();
            return false;
        }

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

    //Clear up music
    Mix_FreeMusic(g_music);
    g_music = nullptr;
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

    case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
            //Press BackSpace to quit
        case SDLK_BACKSPACE:
            return true;
            break;
        }
    }

    //Switch Screens
    switch (e.type)
    {
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
            //Press '1' to Play Level 1
        case SDLK_1:
            game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
            break;

            //Press '2' to Play Level 2
        case SDLK_2:
            game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL2);
            break;

            //Press '3' to open the instruction screen
        case SDLK_3:
            game_screen_manager = new GameScreenManager(g_renderer, SCREEN_INSTRUCTIONS);
            break;

            //Press 'ESC' to go to Main Menu
        case SDLK_ESCAPE:
            game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);
            break;


        default:
            break;
        }
    }

    game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
    g_old_time = new_time;

    return false;
}

void LoadMusic(string musicPath)
{
    g_music = Mix_LoadMUS(musicPath.c_str());
    if (g_music == nullptr)
    {
        cout << "Failed to load music. Error: " << Mix_GetError() << endl;
    }
}

int main(int argc, char* args[])
{
    if (InitSDL())
    {
        LoadMusic("Music/Mario.mp3");
        if (Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(g_music, -1);
        }

        game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);
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
