#include "visualizer/box.h"

using namespace ci;

namespace idealgas {
    Box::Box(const size_t width, const glm::vec2& top_left, const float border_width, ParticleController& particle_controller)
    : kBoxWidth(width),
      kBoxTopLeft(top_left),
      kBoxBorderWidth(border_width),
      particle_controller_(particle_controller) {}

    void Box::UpdateBox() {
        // updates positions and velocities of all particles before re-drawing
        particle_controller_.UpdateParticles();
    }

    void Box::DrawBox() {
        DrawBorder();
        DrawParticles();
    }
    
    void Box::DrawBorder() {
        gl::color( Colorf(1, 1, 1) );
        Rectf box(kBoxTopLeft.x, kBoxTopLeft.y, kBoxTopLeft.x + kBoxWidth, kBoxTopLeft.y + kBoxWidth);
        gl::drawStrokedRect(box, kBoxBorderWidth);
    }
    
    void Box::DrawParticles() {
        for (Particle& p : particle_controller_.GetParticles()) {
            gl::color(p.color);
            gl::drawSolidCircle(p.pos, p.radius);
        }
    }
}