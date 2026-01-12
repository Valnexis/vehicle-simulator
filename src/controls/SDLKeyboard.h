#pragma once

#include <SDL2/SDL.h>
#include <iostream>

struct SDLKeyboardState {
    bool throttle = false; // W held
    bool brake    = false; // S held
    bool clutch   = false; // SHIFT held
    bool gearUp   = false; // X pressed this frame
    bool gearDown = false; // Z pressed this frame
    bool quit     = false; // Q held or window closed
};

class SDLKeyboard {
public:
    SDLKeyboard() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
            ok_ = false;
            return;
        }

        // IMPORTANT: window must be visible to receive focus & keyboard input.
        window_ = SDL_CreateWindow(
            "Vehicle Simulator (click here then use keys)",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            700, 180,
            SDL_WINDOW_SHOWN
        );

        if (!window_) {
            std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
            ok_ = false;
            return;
        }

        SDL_RaiseWindow(window_);
        ok_ = true;
    }

    ~SDLKeyboard() {
        if (window_) SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    bool ok() const { return ok_; }

    void poll(SDLKeyboardState& state) {
        state.gearUp = false;
        state.gearDown = false;

        // Process events (for one-shot presses & quit)
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                state.quit = true;
            }
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                switch (e.key.keysym.sym) {
                    case SDLK_x: state.gearUp = true; break;
                    case SDLK_z: state.gearDown = true; break;
                    default: break;
                }
            }
        }

        // Pump + read current held state (reliable for W/S/SHIFT/Q)
        SDL_PumpEvents();
        const Uint8* ks = SDL_GetKeyboardState(nullptr);

        state.throttle = ks[SDL_SCANCODE_W];
        state.brake    = ks[SDL_SCANCODE_S];
        state.clutch   = ks[SDL_SCANCODE_LSHIFT] || ks[SDL_SCANCODE_RSHIFT];

        // Q quits even if events are quirky
        if (ks[SDL_SCANCODE_Q]) state.quit = true;
    }

private:
    SDL_Window* window_ = nullptr;
    bool ok_ = false;
};