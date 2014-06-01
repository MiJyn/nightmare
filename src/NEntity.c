#include "NEntity.h"

#include "NGlobals.h"
#include <stdlib.h>

#define en_ds ((float)N_delta) * entity->speed

NEntity* NEntity_new(NEntity_info info) {
    NEntity* entity = malloc(sizeof(NEntity));
    entity->pos = NPos2f0;
    entity->size = info.size;
    entity->sheet = info.sheet;
    entity->speed = info.speed;

    entity->state = 0;
    entity->facing_left = 0;

    return entity;
}

void NEntity_destroy(NEntity* entity) {
    // Is this seriously all we have to do? XD
    free(entity);
}


NPosi NEntity_distance(NEntity* entity, NEntity* other) {
    return abs(entity->pos.x - other->pos.x);
}


void NEntity_flip(NEntity* entity) {
    entity->facing_left = !entity->facing_left;
}

void NEntity_forward(NEntity* entity) {
    entity->pos.x += (entity->facing_left ? -1 : 1) * en_ds;
}

void NEntity_left(NEntity* entity) {
    if (!entity->facing_left) {
        NEntity_flip(entity);
    } else {
        NEntity_forward(entity);
    }
}

void NEntity_right(NEntity* entity) {
    if (entity->facing_left) {
        NEntity_flip(entity);
    } else {
        NEntity_forward(entity);
    }
}

void NEntity_move_towards(NEntity* entity, NEntity* other) {
    NPosf diff = other->pos.x - entity->pos.x;
    NPosf delta_speed;
    if ((entity->facing_left && diff > 0) || (!entity->facing_left && diff < 0)) {
        NEntity_flip(entity);
    } else if ((delta_speed = en_ds) > diff) {
        if (entity->facing_left) {
            entity->pos.x -= delta_speed;
        } else {
            entity->pos.x += delta_speed;
        }
    } else {
        NEntity_forward(entity);
    }
}


void NEntity_update(NEntity* entity) {
    NSpritesheet_update(entity->sheet);
    // TODO: CR
}

void NEntity_draw(NEntity* entity) {
    NSpritesheet_draw(entity->sheet, entity->state, Npos2i(entity->pos.x, entity->pos.y), !entity->facing_left);
}