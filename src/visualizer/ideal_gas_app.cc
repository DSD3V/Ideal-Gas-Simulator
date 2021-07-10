#include "visualizer/ideal_gas_app.h"

namespace idealgas {
    //initializes particle_controller_ and box_; reference to particle_controller_ gets passed to box_
    IdealGasApp::IdealGasApp()
    : particle_controller_(kBoxWidth, kBoxTopLeft, kBoxBorderWidth - 10),
      box_(kBoxWidth, kBoxTopLeft, kBoxBorderWidth, particle_controller_),
      histograms_(kNumHists, kHistWidth, kHistHeight, kHistTopLeft, particle_controller_) {}
    
    void IdealGasApp::update() {
        box_.UpdateBox();
        histograms_.UpdateHistograms();
    }

    void IdealGasApp::draw() {
        gl::clear();
        DrawTitle();
        box_.DrawBox();
        histograms_.DrawHistograms();
        DrawSpeedInfo();
    }

    void IdealGasApp::keyDown(KeyEvent event) {
        switch(event.getCode()) {
            case KeyEvent::KEY_1:
                //1 clicked, so should_speed_up is true
                particle_controller_.ChangeSpeeds(true);
                break;
            case KeyEvent::KEY_0:
                //0 clicked, so should_speed_up is false (speed down)
                particle_controller_.ChangeSpeeds(false);
                break;
        }
    }
    
    void IdealGasApp::DrawTitle() {
        Font title_font("Roboto", 35);
        gl::drawStringCentered("The All Time Greatest CS126 Ideal Gas Simulator",
                               glm::vec2(getWindowWidth() / 2, 14),
                               Colorf(1, 1, 1), title_font);
    }
    
    void IdealGasApp::DrawSpeedInfo() {
        Font speed_note_font("Roboto", 32);
        gl::drawStringCentered("Press 1 to speed up the particles or 0 to slow them down.",
                               glm::vec2(kBoxTopLeft.x + kBoxWidth / 2, getWindowHeight() - 59),
                               Colorf(1, 1, 1), speed_note_font);

        Font speed_warning("Roboto", 27);
        gl::drawStringCentered("Warning: When particles travel fast enough, unexpected things can happen.",
                               glm::vec2(kBoxTopLeft.x + kBoxWidth / 2, getWindowHeight() - 28),
                               Colorf(1, 1, 1), speed_warning);
    }
}