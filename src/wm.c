#include "wm.h"

#include "wm/sdl.h"
#include "wm/sdl2.h"

#include "log.h"

wm_s wm;

wm_event wm_event_new(enum wm_event_type type) {
    wm_event event;
    event.type = type;

    if (type == WM_QUIT) {
        event.window_quit = true;
    }

    return event;
}


bool wm_init() {
    wm_sdl_init();
    wm_sdl2_init();

    debug("Choosing WM backend");
    if (SDL_FOUND) {
        debug("Chosen SDL");
        wm = wm_sdl;
    } else if (SDL2_FOUND) {
        debug("Chosen SDL2");
        wm = wm_sdl2;
    } else {
        error("No backend chosen!");
        return false;
    }
    return wm.init();
}

bool wm_destroy() {
    return wm.destroy();
}