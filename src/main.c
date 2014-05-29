#include "NGlobals.h"
#include "NLog.h"
#include "NWMan.h"
#include "wrap/gl.h"
#include "NRsc.h"
#include "NEngine.h"

int main(int argc, char** argv) {
    int ret = 0;

    bool okay;

    N_argc = argc;
    N_argv = argv;

    // Load
    Ndebug("Initializing global variables");
    NGlobals_init();

    Ndebug("Initializing window manager");
    NINDENT(okay = NWMan_init(argc, argv));

    if (!okay) {
        Nerror("Error initializing window manager!");
    }

    Ndebug("Creating window");
    NINDENT(okay = N_WMan.create_window());

    if (!okay) {
        Nerror("Error creating window!");
    }

    Ndebug("Initializing GLEW");
    if (glewInit() != GLEW_OK) {
        Nerror("Error initializing GLEW!");
    }

    Ndebug("Initializing paths");
    NINDENT(okay = NRsc_init());

    /*if (!okay) {
        return;
    }*/

    Ndebug("Loading engine");
    NINDENT(okay = NEngine_init());

    if (!okay) {
        Nerror("Error loading engine!");
    }

    // Game
    Nnewline();
    NEngine_run();

    // End
    Ndebug("Destroying engine");
    NEngine_destroy();

    Ndebug("Destroying paths");
    NINDENT(NRsc_destroy());

    Ndebug("Destroying window");
    NINDENT(N_WMan.destroy_window());

    Ndebug("Destroying window manager");
    NWMan_destroy();

    Ndebug("Destroying global variables");
    NGlobals_destroy();

    return ret;
}
