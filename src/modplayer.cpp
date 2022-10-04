// modplayer.cpp : Defines the entry point for the application.
//

#include <Windows.h>
#include "modplayer.h"

#include "SDL.h"
#include <stdio.h>
#include <string.h>

#define POCKETMOD_IMPLEMENTATION
#include "pocketmod.h"

#include "text.h"

#define MAX_LOADSTRING 100
#define STR_ENDS_WITH(S, E) (strcmp(S + strlen(S) - (sizeof(E)-1), E) == 0)


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


static void audio_callback(void *userdata, Uint8 *buffer, int bytes)
{
  int i = 0;
  while (i < bytes) {
    i += pocketmod_render((pocketmod_context *)userdata, buffer + i, bytes - i);
  }
}


int main(int argc, char **argv)
{
    // TODO: Place code here.
    const Uint32 allowed_changes = SDL_AUDIO_ALLOW_FREQUENCY_CHANGE;
    Uint32 start_time;
    pocketmod_context context;
    SDL_AudioSpec format;
    SDL_AudioDeviceID device;
    SDL_RWops *mod_file;
    char *mod_data, *slash;
    size_t mod_size;

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
      printf("error: SDL_Init() failed: %s\n", SDL_GetError());
      return -1;
    }

    /* Initialize the audio subsystem */
    format.freq = 44100;
    format.format = AUDIO_F32;
    format.channels = 2;
    format.samples = 4096;
    format.callback = audio_callback;
    format.userdata = &context;
    device = SDL_OpenAudioDevice(NULL, 0, &format, &format, allowed_changes);
    if (!device) {
      printf("error: SDL_OpenAudioDevice() failed: %s\n", SDL_GetError());
      return -1;
    }
 
 //   char modfile[255] = "C:\\GIT-copy\\modplayer\\star_control2,tune1.mod";
    char modfile[255] = "C:\\GIT-copy\\Mirage_Demo_1998\\new-vampire.mod";
// tut's ned    char modfile[255] = "C:\\GIT-copy\\Mirage_Demo_1998\\STK.housetrain";
//    char modfile[255] = "C:\\GIT-copy\\Mirage_Demo_1998\\android.mod";
    //    char modfile[255] = "C:\\GIT-copy\\Mirage_Demo_1998\\wisdom.mod";
    //    char modfile[255] = "C:\\GIT\\star_control2_tune1.mod";

    /* Read the MOD file into a heap block */
    if (!(mod_file = SDL_RWFromFile(modfile, "rb"))) {
      printf("error: can't open '%s' for reading\n", modfile);
      return -1;
    }
    else if (!(mod_data = (char *)SDL_malloc(mod_size = SDL_RWsize(mod_file)))) {
      printf("error: can't allocate memory for '%s'\n", modfile);
      return -1;
    }
    else if (!SDL_RWread(mod_file, mod_data, mod_size, 1)) {
      printf("error: can't read file '%s'\n", modfile);
      return -1;
    }
    SDL_RWclose(mod_file);

    /* Initialize the renderer */
    if (!pocketmod_init(&context, mod_data, mod_size, format.freq)) {
      printf("error: '%s' is not a valid MOD file\n", modfile);
      return -1;
    }

    /* Strip the directory part from the source file's path 
    while ((slash = strpbrk(modfile, "/\\"))) {
      mod_file = (char *)(slash + 1);
    }*/

    /* Start playback */
    SDL_PauseAudioDevice(device, 0);
    start_time = SDL_GetTicks();


    const int windowHeight = 600;
    const int windowWidth = 800;
    SDL_Window *window = SDL_CreateWindow("modplayer 2022",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth,
      windowHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      SDL_Quit();
      return 2;
    }
    
    // We create a renderer with hardware acceleration, we also present according with the vertical sync refresh.
    SDL_Renderer *rndr = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    const int pointLocationx = windowWidth / 2;
    const int pointLocationy = windowHeight / 2;

    bool quit = false;
    SDL_Event event;

    loadText(800, 600);		// Bildschirm-Text (BTX) initialisieren
    while (!quit) {
        int chan_sample[4] = {static_cast<int>(context.channels[0].sample),static_cast<int>(context.channels[1].sample),
                              static_cast<int>(context.channels[2].sample),static_cast<int>(context.channels[3].sample) };

        std::string samplea = std::to_string(chan_sample[0]) + " " + std::to_string(context.samples[chan_sample[0]].length);
        std::string sampleb = std::to_string(static_cast<int>(context.channels[1].sample));
        std::string samplec = std::to_string(static_cast<int>(context.channels[2].sample));
        std::string sampled = std::to_string(static_cast<int>(context.channels[3].sample));

        int chan_vol[4] = { static_cast<int>(context.channels[0].volume),static_cast<int>(context.channels[1].volume),
                            static_cast<int>(context.channels[2].volume),static_cast<int>(context.channels[3].volume) };
        float chan_pos[4] = { static_cast<float>(context.channels[0].position),static_cast<float>(context.channels[1].position),
                            static_cast<float>(context.channels[2].position),static_cast<float>(context.channels[3].position) };

        /* Print some information during playback */
        int seconds = (SDL_GetTicks() - start_time) / 1000;
/*        printf("\rPlaying '%s' ", modfile);
        printf("[%d:%02d] ", seconds / 60, seconds % 60);
*///        printf("Press Ctrl + C to stop");
//        fflush(stdout);
//        SDL_Delay(500);

        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            quit = true;
          }
        }

        // We clear what we draw before
        SDL_RenderClear(rndr);
        // Set our color for the draw functions
        SDL_SetRenderDrawColor(rndr, 0xFF, 0xFF, 0xFF, 0xFF);
        // Now we can draw our point
//        SDL_RenderDrawPoint(rndr, pointLocationx, pointLocationy);
//        SDL_RenderDrawLine(rndr, 10, 10, 50, 25); // Draw a line
        doText(rndr, 20, 10, "nice, our sweet new mod player ...");
//          doText(rndr, 20, 20, "playing mod : " + std::string(reinterpret_cast<char*>(context.source)));
        doText(rndr, 20, 20, "playing " + std::string(modfile));
        char buf[100];
        sprintf(buf,"[%d:%02d] ", seconds / 60, seconds % 60);
        doText(rndr, 20, 30, buf);
        
        if (chan_pos[0] < 0.01f) samplea = "-";
        if (chan_pos[1] < 0.01f) sampleb = "-";
        if (chan_pos[2] < 0.01f) samplec = "-";
        if (chan_pos[3] < 0.01f) sampled = "-";

        SDL_Rect r = { 20, 100, 180, 100 };
        SDL_SetRenderDrawColor(rndr, 0x00, 0x6F, 0x00, 0x6F);
        if (chan_pos[0] > 0.0f) SDL_RenderFillRect(rndr, &r);
        r = { 210, 100, 180, 100 };
        SDL_SetRenderDrawColor(rndr, 0x00, 0x00, 0x6F, 0xFF);
        if (chan_pos[1] > 0.0f) SDL_RenderFillRect(rndr, &r);
        r = { 400, 100, 180, 100 };
        SDL_SetRenderDrawColor(rndr, 0x00, 0x6F, 0xFF, 0x00);
        if (chan_pos[2] > 0.0f) SDL_RenderFillRect(rndr, &r);
        r = { 590, 100, 180, 100 };
        SDL_SetRenderDrawColor(rndr, 0x00, 0x6F, 0x6F, 0xFF);
        if (chan_pos[3] > 0.0f) SDL_RenderFillRect(rndr, &r);
        // Set the color to what was before
        SDL_SetRenderDrawColor(rndr, 0x00, 0x00, 0x00, 0xFF);
        // .. you could do some other drawing here
        doText(rndr, 20 + 90, 150, samplea);
        doText(rndr, 210 + 90, 150, sampleb);
        doText(rndr, 400 + 90, 150, samplec);
        doText(rndr, 590 + 90, 150, sampled);
        // And now we present everything we draw after the clear.
        SDL_RenderPresent(rndr);
    }

    SDL_DestroyWindow(window);
    // We have to destroy the renderer, same as with the window.
    SDL_DestroyRenderer(rndr);
    SDL_Quit();

//    return (int) msg.wParam;
}

