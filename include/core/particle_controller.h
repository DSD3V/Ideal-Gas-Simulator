#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"
#include <vector>
#include <map>

using std::vector;
using std::multimap;

namespace idealgas {
    class ParticleController {
        public:
            /* Parameterized constructor: initializes particles_ with locations within box bounds */
            ParticleController(const size_t box_width, const glm::vec2& top_left, const float border_width);

            /* Initializes particles_ with the passed in particles and bounds, mainly for testing */
            ParticleController(vector<Particle>& particles, const float x_min, const float x_max, const float y_min, const float y_max);
            
            /* Updates positions and velocities of particles */
            void UpdateParticles();
            
            /* Returns list of particles */
            vector<Particle>& GetParticles();
            
            /* Speeds up or slows down particles; speed up if speed_up is true, else slow down */
            void ChangeSpeeds(const bool should_speed_up);
            
        private:
            /* List of particles */
            vector<Particle> particles_;

            /* Maps particle position magnitudes to particles, allows for O(nlog(n)) collision checking */
            multimap<float, Particle*> pos_particle_map_;
            
            /* Helper method for adding particles of a specific type to particles_ */
            void SetParticles(const size_t type, const size_t num, const float mass, const float radius, const cinder::Colorf color);
            
            /* Helper methods for updating particle positions / velocities */
            void CheckWallCollision(Particle& p);
            void CheckParticleCollision(Particle& p);
            float DistBtwnPoints(const Particle& p1, const Particle& p2);
            void UpdateVelocities(Particle& p1, Particle& p2);
            //p1: particle whose velocity is being updated, p2 collided with p1
            void UpdateVelocity(Particle& p1, Particle& p2);
            
            /* Initial velocity for all particles */
            const glm::vec2 kMinInitialVel = glm::vec2(-2.5, -2.5);
            const glm::vec2 kMaxInitialVel = glm::vec2(2.5, 2.5);
            
            /* Percent amount to increase or decrease velocity by */
            const float kVelChange = 1.10f;
            
            /* Bounds for possible particle positions */
            const float kXMin;
            const float kXMax;
            const float kYMin;
            const float kYMax;
            
            /* Number, radius, mass, and color of each of 3 possible particles */
            const size_t kType1 = 1;
            const size_t kType2 = 2;
            const size_t kType3 = 3;
            
            const size_t kNumP1 = 40;
            const size_t kNumP2 = 20;
            const size_t kNumP3 = 15;

            const float kP1Mass = 10;
            const float kP2Mass = 50;
            const float kP3Mass = 300;
            
            const float kP1Radius = 10;
            const float kP2Radius = 20;
            const float kP3Radius = 30;
            
            const cinder::Colorf kP1Color = cinder::Colorf(0, 0.1f, 1);
            const cinder::Colorf kP2Color = cinder::Colorf(1, 0, 0);
            const cinder::Colorf kP3Color = cinder::Colorf(0, 0.75f, 0);
    };
}