#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "box.h"
#include "histograms.h"

using namespace ci;
using namespace ci::app;

namespace idealgas {
    class IdealGasApp : public App {
        public:
            /* Default constructor: initializes particle_controller_, box_, and histograms_ */
            IdealGasApp();
            /* Updates state of box and histograms every frame */
            void update() override;
            /* Draws box and histograms every frame */
            void draw() override;
            /* Listens for keyDown to update particle speeds: 1 = speed up, 0 = slow down */
            void keyDown(KeyEvent event) override;
    
        private:
            /* Default values for box that stores particles */
            const size_t kMargin = 80;
            const size_t kBoxWidth = getWindowHeight() - (2 * kMargin);
            const glm::vec2 kBoxTopLeft = glm::vec2(kMargin - 30, kMargin);
            const float kBoxBorderWidth = 25;
            
            /* Default values for histograms that display particle info */
            const size_t kNumHists = 3;
            const size_t kHistWidth = 405;
            const size_t kHistHeight = 210;
            const glm::vec2 kHistTopLeft = glm::vec2(kMargin + kBoxWidth + 50, kMargin); //for 1st histogram
            
            /* Controls/stores particles; passed by reference to box_ and histograms_ */
            ParticleController particle_controller_;
            
            Box box_;
            Histograms histograms_;
            
            /* Drawing helper methods */
            void DrawTitle();
            void DrawSpeedInfo();
    };
}