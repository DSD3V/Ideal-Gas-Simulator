#pragma once

#include "cinder/gl/gl.h"
#include "core/particle_controller.h"
#include "core/histogram.h"

namespace idealgas {
    class Histograms {
    public:
        /* Initializes member variables and histograms_ using particles from particle_controller_ */
        Histograms(const size_t num, const size_t width, const size_t height, glm::vec2 top_left, ParticleController& particle_controller);
        /* Updates histograms every frame */
        void UpdateHistograms();
        /* Draws histograms every frame */
        void DrawHistograms();

    private:
        const size_t kNumHists;
        const size_t kHistWidth;
        const size_t kHistHeight;
        glm::vec2 hist_top_left_; //for first histogram, changes for other histograms
        
        /* Has info of particles needed for histograms */
        ParticleController& particle_controller_;
        
        /* Vector of Histograms that will be drawn */
        vector<Histogram> histograms_;
        
        /* Helper method for drawing a histogram */
        void DrawHistogram(Histogram& hist);
        void DrawHistBorder();
        void DrawHistTitle();
        void DrawXLabels(Histogram& hist);
        void DrawYLabels(Histogram& hist);
        void DrawBars(Histogram& hist);
    };
}