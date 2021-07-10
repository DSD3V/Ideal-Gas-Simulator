#include "core/particle_controller.h"
#include <random>

namespace idealgas {
    ParticleController::ParticleController(const size_t box_width, const glm::vec2& top_left, const float border_width)
            : kXMin(top_left.x + border_width),
              kXMax(top_left.x + box_width - border_width),
              kYMin(top_left.y + border_width),
              kYMax(top_left.y + box_width - border_width) {
        srand(static_cast<unsigned>(time(nullptr)));
        SetParticles(kType1, kNumP1, kP1Mass, kP1Radius, kP1Color);
        SetParticles(kType2, kNumP2, kP2Mass, kP2Radius, kP2Color);
        SetParticles(kType3, kNumP3, kP3Mass, kP3Radius, kP3Color);
    }

    ParticleController::ParticleController(vector<Particle>& particles, const float x_min, const float x_max, const float y_min, const float y_max)
            : particles_(particles),
              kXMin(x_min),
              kXMax(x_max),
              kYMin(y_min),
              kYMax(y_max) {
        for (Particle& p : particles_) {
            pos_particle_map_.insert(std::make_pair(glm::length(p.pos), &p));
        }
    }

    void ParticleController::SetParticles(const size_t type, const size_t num, const float mass, const float radius, const cinder::Colorf color) {
        for (size_t i = 0; i < num; ++i) {
            /* Generate random initial pos. based on box width and vel. and add each type of particle to particles_ */
            float rand_x_pos = (((kXMax - radius) - (kXMin + radius)) * (static_cast<float>(rand()) / RAND_MAX)) + kXMin + radius;
            float rand_y_pos = (((kYMax - radius) - (kYMin + radius)) * (static_cast<float>(rand()) / RAND_MAX)) + kYMin + radius;
            float rand_x_vel = ((static_cast<float>(rand()) / RAND_MAX) * (kMaxInitialVel.x - kMinInitialVel.x)) + kMinInitialVel.x;
            float rand_y_vel = ((static_cast<float>(rand()) / RAND_MAX) * (kMaxInitialVel.y - kMinInitialVel.y)) + kMinInitialVel.y;
            glm::vec2 initial_pos = glm::vec2(rand_x_pos, rand_y_pos);
            glm::vec2 initial_vel = glm::vec2(rand_x_vel, rand_y_vel);
            Particle p(type, initial_pos, initial_vel, mass, radius, color);
            particles_.push_back(p);
            pos_particle_map_.insert(std::make_pair(glm::length(p.pos), &p));
        }
    }

    void ParticleController::UpdateParticles() {
        for (Particle& p : particles_) {
            CheckWallCollision(p);
            CheckParticleCollision(p);
            pos_particle_map_.erase(glm::length(p.pos));
            p.pos += p.vel;
            pos_particle_map_.insert(std::make_pair(glm::length(p.pos), &p));
            p.speed = glm::length(p.vel);
        }
    }

    void ParticleController::CheckWallCollision(Particle& p) {
        //particle is moving towards left or right wall and touching it
        if (p.pos.x <= kXMin + p.radius && p.vel.x < 0 || p.pos.x >= kXMax - p.radius && p.vel.x > 0) {
            p.vel.x *= -1;
            //particle is moving towards top or bottom wall and touching it
        } else if (p.pos.y <= kYMin + p.radius && p.vel.y < 0 || p.pos.y >= kYMax - p.radius && p.vel.y > 0) {
            p.vel.y *= -1;
        }
    }

    void ParticleController::CheckParticleCollision(Particle& p) {
        //differences in velocity and position of each particle
        glm::vec2 vel_diff;
        glm::vec2 pos_diff;

        //iterates through range of keys in map with positions where a collision is possible
        //lower bound: top-left of particle, upper bound: bottom-right. (since 0,0 position is at the top left)
        for (auto it = pos_particle_map_.lower_bound(sqrt(pow(p.pos.x - 2 * p.radius, 2) + pow(p.pos.y - 2 * p.radius, 2)));
             it != pos_particle_map_.upper_bound(sqrt(pow(p.pos.x + 2 * p.radius, 2) + pow(p.pos.y + 2 * p.radius, 2)));
             ++it) {
            //don't consider colliding with itself
            if (&p != it->second) {
                vel_diff = glm::vec2(p.vel.x - it->second->vel.x, p.vel.y - it->second->vel.y);
                pos_diff = glm::vec2(p.pos.x - it->second->pos.x, p.pos.y - it->second->pos.y);
                //only check for collision if 2 particles are moving towards each other
                if (glm::dot(vel_diff, pos_diff) < 0) {
                    //if particles are touching
                    if (DistBtwnPoints(p, *it->second) <= p.radius + it->second->radius) {
                        UpdateVelocities(p, *it->second);
                    }
                }
            }
        }
    }

    void ParticleController::UpdateVelocities(Particle& p1, Particle& p2) {
        Particle original_p1 = p1;
        UpdateVelocity(p1, p2); //updates p1's velocity
        UpdateVelocity(p2, original_p1); //updates p2's velocity
    }

    void ParticleController::UpdateVelocity(Particle& p1, Particle& p2) {
        //v1 - v2
        glm::vec2 vel_diff = glm::vec2(p1.vel.x - p2.vel.x, p1.vel.y - p2.vel.y);
        //p1 - p2
        glm::vec2 pos_diff = glm::vec2(p1.pos.x - p2.pos.x, p1.pos.y - p2.pos.y);

        //2m2 / m1 + m2
        float mass_fraction = ((2 * p2.mass) / (p1.mass + p2.mass));

        //(v1 - v2)dot(p1 - p2) / ||p1 - p2||^2
        float scalar_fraction = glm::dot(vel_diff, pos_diff) / pow(glm::length(pos_diff), 2);

        //(mass_fraction)(scalar_fraction) * (p1 - p2)
        glm::vec2 pos_times_scalar = glm::vec2(pos_diff.x * (mass_fraction) * (scalar_fraction),
                                               pos_diff.y * (mass_fraction) * (scalar_fraction));

        //v1 - pos_times_scalar
        p1.vel = glm::vec2(p1.vel.x - pos_times_scalar.x, p1.vel.y - pos_times_scalar.y);
    }

    void ParticleController::ChangeSpeeds(const bool should_speed_up) {
        for (Particle& p : particles_) {
            should_speed_up ? p.vel *= kVelChange : p.vel /= kVelChange;
            p.speed = glm::length(p.vel);
        }
    }

    float ParticleController::DistBtwnPoints(const Particle& p1, const Particle& p2) {
        return sqrt((pow(p1.pos.x - p2.pos.x, 2) + pow(p1.pos.y - p2.pos.y, 2)));
    }

    vector<Particle>& ParticleController::GetParticles() { return particles_; }
}