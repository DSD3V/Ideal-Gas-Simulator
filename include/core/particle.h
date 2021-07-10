#pragma once

#include "cinder/gl/gl.h"
#include <string>

using std::string;

namespace idealgas {
    struct Particle {
        Particle(const size_t type, glm::vec2 pos, glm::vec2 vel, const float mass, const float radius, const cinder::Colorf color);
        const size_t type; //1, 2, or 3
        glm::vec2 pos;
        glm::vec2 vel;
        const float mass;
        const float radius;
        const cinder::Colorf color;
        float speed;
    };
}