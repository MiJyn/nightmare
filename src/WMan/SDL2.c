#include "../NWMan.h"
#include "../NGlobals.h"
#include "../NLog.h"

// SDL 2 implementation

#include <SDL2/SDL.h>

NWMan N_WMan_SDL2;

SDL_Window* sdl2_window;
SDL_GLContext sdl2_glcontext;

bool sdl2_init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    return true;
}

bool sdl2_destroy() {
    SDL_Quit();
    return true;
}


bool sdl2_create_window() {
    Ndebug("Creating window");
    sdl2_window = SDL_CreateWindow(
        N_win_title,
        N_win_pos.x,
        N_win_pos.y,
        N_win_size.x,
        N_win_size.y,
        SDL_WINDOW_OPENGL
    );
    if (sdl2_window == NULL) {
        return false;
    }
    Ndebug("Creating GL context");
    sdl2_glcontext = SDL_GL_CreateContext(sdl2_window);
    return true;
}

bool sdl2_destroy_window() {
    Ndebug("Destroying GL context");
    SDL_GL_DeleteContext(sdl2_glcontext);
    Ndebug("Destroying window");
    SDL_DestroyWindow(sdl2_window);
    return true;
}


void sdl2_swap_buffers() {
    SDL_GL_SwapWindow(sdl2_window);
}


bool sdl2_next_event(NWMan_event* event) {
   NWMan_event_type type;
    SDL_Event sev;

nextevent:

    if (!SDL_PollEvent(&sev)) {
        return false;
    }

    switch(sev.type) {
        case SDL_QUIT:
            type = N_WMAN_QUIT;
            break;
        case SDL_WINDOWEVENT:
            switch(sev.window.event) {
                case SDL_WINDOWEVENT_SHOWN:
                case SDL_WINDOWEVENT_HIDDEN:
                case SDL_WINDOWEVENT_EXPOSED:
                case SDL_WINDOWEVENT_RESTORED:
                case SDL_WINDOWEVENT_MINIMIZED:
                case SDL_WINDOWEVENT_MAXIMIZED:
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    type = N_WMAN_FOCUS;
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    type = N_WMAN_RESIZE;
                    break;
                default:
                    goto nextevent;
                    break;
            };
            break;
        case SDL_KEYUP:
        case SDL_KEYDOWN:
            type = N_WMAN_KEYBOARD;
            break;
        case SDL_MOUSEMOTION:
            type = N_WMAN_MOUSE_MOVE;
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            type = N_WMAN_MOUSE_BUTTON;
            break;
        case SDL_MOUSEWHEEL:
            type = N_WMAN_MOUSE_WHEEL;
            break;
        default:
            goto nextevent;
            break;
    };

    *event = NWMan_event_new(type);

    switch(type) {
        case N_WMAN_QUIT:
            break;
        case N_WMAN_FOCUS:
            switch(sev.window.event) {
                case SDL_WINDOWEVENT_SHOWN:
                case SDL_WINDOWEVENT_EXPOSED:
                case SDL_WINDOWEVENT_RESTORED:
                case SDL_WINDOWEVENT_MAXIMIZED:
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    event->window_focus = true;
                    break;
                default:
                    event->window_focus = false;
                    break;
            };
            break;
        case N_WMAN_RESIZE:
            event->window_size.x = sev.window.data1;
            event->window_size.y = sev.window.data2;
            break;
        case N_WMAN_KEYBOARD:
            event->keyboard.state = (sev.type == SDL_KEYDOWN);
            event->keyboard.key = sev.key.keysym.sym;
            break;
        case N_WMAN_MOUSE_MOVE:
            event->mouse_pos.x = sev.motion.x;
            event->mouse_pos.y = sev.motion.y;
            break;
        case N_WMAN_MOUSE_BUTTON:
            event->mouse_button.state = (sev.type == SDL_MOUSEBUTTONDOWN);
            switch(sev.button.button) {
                case SDL_BUTTON_LEFT:
                    event->mouse_button.id = N_WMAN_MOUSE_LEFT;
                    break;
                case SDL_BUTTON_RIGHT:
                    event->mouse_button.id = N_WMAN_MOUSE_RIGHT;
                    break;
                case SDL_BUTTON_MIDDLE:
                    event->mouse_button.id = N_WMAN_MOUSE_MIDDLE;
                    break;
                case SDL_BUTTON_X1:
                    event->mouse_button.id = 3;
                    break;
                case SDL_BUTTON_X2:
                    event->mouse_button.id = 4;
                    break;
            };
            break;
        case N_WMAN_MOUSE_WHEEL:
            event->mouse_wheel = sev.wheel.y; // XXX: Is this okay?
            break;
        default:
            goto nextevent;
            break;
    }

    return true;
}

uint sdl2_get_millis() {
    return SDL_GetTicks();
}

void sdl2_sleep(uint millis) {
    SDL_Delay(millis);
}


void NWMan_SDL2_init() {
    N_WMan_SDL2.init = sdl2_init;
    N_WMan_SDL2.destroy = sdl2_destroy;

    N_WMan_SDL2.create_window = sdl2_create_window;
    N_WMan_SDL2.destroy_window = sdl2_destroy_window;

    N_WMan_SDL2.swap_buffers = sdl2_swap_buffers;

    N_WMan_SDL2.next_event = sdl2_next_event;

    N_WMan_SDL2.get_millis = sdl2_get_millis;
    N_WMan_SDL2.sleep = sdl2_sleep;
}