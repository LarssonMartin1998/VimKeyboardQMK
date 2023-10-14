#pragma once

enum layers {
    MAC, // This and WIN are both default layers controlled by the dip_switch on the keyboard.
    WIN,
    VIM,
    FN,
    GAME,
};

enum layer_state {
    LS_BASE = 0,
    LS_VIM,
    LS_FN,
    LS_GAME,
};
