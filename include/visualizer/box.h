#pragma once

#include "cinder/gl/gl.h"
#include "core/particle_controller.h"

namespace idealgas {
    class Box {
        public:
            /* Constructs box with given width, top left corner, and border and initializes member variables */
            Box(size_t width, const glm::vec2& top_left, const float border_width, ParticleController& particle_controller);
            /* Updates particles every frame */
            void UpdateBox();
            /* Draws particles every frame */
            void DrawBox();
    
        private:
            /* Default values for box, set in parent class ideal_gas_app */
            const float kBoxBorderWidth;
            const size_t kBoxWidth;
            const glm::vec2 kBoxTopLeft;
            
            /* Stores and updates all particles in the box */
            ParticleController& particle_controller_;
            
            /* Helper methods for drawing */
            void DrawBorder();
            void DrawParticles();
    };
}