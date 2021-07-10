#include "core/particle.h"

namespace idealgas {
    Particle::Particle(const size_t type, glm::vec2 pos, glm::vec2 vel, const float mass, const float radius, const cinder::Colorf color)
    : type(type),
      pos(pos),
      vel(vel),
      radius(radius),
      mass(mass),
      color(color),
      speed(glm::length(vel)) {}
}