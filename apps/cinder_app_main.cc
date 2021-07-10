#include <visualizer/ideal_gas_app.h>

using idealgas::IdealGasApp;

void prepareSettings(IdealGasApp::Settings* settings) {
    settings->setResizable(false);
    settings->setWindowSize(1300, 900);
    settings->setFrameRate(60.0f);
}

CINDER_APP(IdealGasApp, ci::app::RendererGl, prepareSettings)