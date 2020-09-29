#include "WindowHandler.h"
#include "TextureHandler.h"
#include <string> using namespace std

bool Handlers::WindowHandler::init(const char* title, int xpos, int ypos, int height, int width)
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  width, height, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

void Handlers::WindowHandler::close()
{
    //Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

void Handlers::WindowHandler::CreateWindow(const char* title, int xpos, int ypos, int height, int width)
{
    //Start up SDL and create window
    if (!init(title, xpos, ypos, height, width))
    {
        //foutmelding ofzo?
        printf("Failed to initialize!\n");
    }
    else {
        //succes

    }
}

void Handlers::WindowHandler::DeleteWindow()
{
    close();
}

int main(int argc, char** argv) 
{
    Handlers::WindowHandler handler = Handlers::WindowHandler{};
    handler.CreateWindow("Dimitri", 0, 0, 720, 1000);

    std::string path = "D:/School - Programming/c++/Project/dimitri/Dimitri/Engines/Graphics/src/Handlers/img.png";
    Handlers::TextureHandler handler2 = Handlers::TextureHandler{};
    handler2.CreateRenderer(handler.gWindow);

    handler2.gTexture = handler2.loadTexture(path);
    handler2.UpdateScreen(handler.gWindow, handler2.gTexture, handler2.gRenderer);
    //Wait two seconds
    SDL_Delay(10000);

    handler.DeleteWindow();
    return 0;
}
