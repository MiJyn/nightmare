/*
    Copyright (c) 2014, Anonymous Meerkat <meerkatanonymous@gmail.com>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
          notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
          notice, this list of conditions and the following disclaimer in the
          documentation and/or other materials provided with the distribution.
        * Neither the name of the Nightmare Project nor the
          names of its contributors may be used to endorse or promote products
          derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL ANONYMOUS MEERKAT BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "NSpritesheet.h"

#include "NSprite.h"

#include <stdlib.h>

NSpritesheet* NSpritesheet_new(NSpritesheet_data* sprites) {
    NSpritesheet* sheet = malloc(sizeof(NSpritesheet));
    sheet->sprites = sprites;
    return sheet;
}

void NSpritesheet_destroy(NSpritesheet* sheet) {
    NSprite* sprite;
    for (size_t i = 0; (sprite = sheet->sprites[i].sprite); i++) {
        NSprite_destroy(sprite);
    }
    free(sheet);
}


bool NSpritesheet_update(NSpritesheet* sheet, size_t id) {
    NSprite* sprite;
    bool ret = false;
    for (size_t i = 0; (sprite = sheet->sprites[i].sprite); i++) {
        bool thingy = NSprite_update(sprite);
        if (i == id) {
            ret = thingy;
        }
    }
    return ret;
}

void NSpritesheet_draw(NSpritesheet* sheet, size_t id, NVec2i_t pos, NVec2i_t size, bool flip, float alpha) {
    NSprite_draw(sheet->sprites[id].sprite, pos, size, flip, alpha);
}
