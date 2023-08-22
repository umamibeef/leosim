#include <SDL.h>

#include <imgui.h>
#include <imgui_impl_sdlrenderer2.h>
#include <imgui_impl_sdl2.h>
#include <iostream>

struct ProgramInstance {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool exitSignal = false;
    bool showDemoWindow = true;
};

void pollEvents(ProgramInstance* instance)
{
    SDL_Event newEvent;
    while(SDL_PollEvent(&newEvent))
    {
        ImGui_ImplSDL2_ProcessEvent(&newEvent);
        if(newEvent.type == SDL_QUIT)
        {
            instance->exitSignal = true;
        }
    }
}

int main(int argc, char** argv) 
{
    std::cout << "hello world" << std::endl;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        std::cout << "SDL init failed" << std::endl;
        return -1;
    }

    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    ProgramInstance instance;
    instance.window = SDL_CreateWindow( "sample program", 
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1600,
            900,
            windowFlags);

    instance.renderer = SDL_CreateRenderer(instance.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    if(!instance.renderer)
    {
        std::cout << "SDL renderer create failed" << std::endl;
        return -1;
    }

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(instance.window, instance.renderer);
    ImGui_ImplSDLRenderer2_Init(instance.renderer);

    while (!instance.exitSignal) 
    {
        pollEvents(&instance);
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        /// ===== Draw your ImGui stuff here ====
        ImGui::ShowDemoWindow(&instance.showDemoWindow);

        ImGui::Render();

        SDL_RenderSetScale(instance.renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(instance.renderer, 25, 25, 25, 1.0);
        SDL_RenderClear(instance.renderer);

        // standard SDL2 drawing functions can go here.

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(instance.renderer);
    }

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(instance.renderer);
    SDL_DestroyWindow(instance.window);
    SDL_Quit();
}