#pragma once

#include <vector>
#include "particle.h"

using std::vector;

namespace idealgas {
    class Histogram {
        public:
            /* Initializes particles_ vector with passed in particles */
            Histogram(vector<Particle*> particles);
            
            /* Updates the values displayed by the histogram */
            void UpdateHistogram();

            /* Getters */
            vector<float>& GetXValues();
            vector<float>& GetBinFrequencies();
            vector<Particle*>& GetParticles();
            
        private:
            /* List of particles whose info will be displayed by this histogram */
            vector<Particle*> particles_;
            
            /* List of x values of histogram (bin values, which are speeds) */
            vector<float> x_values_;
            
            /* List of frequencies as percentages for each bin in x_values_, used to determine height of hist bars */
            vector<float> bin_frequencies_;
            
            /* Number of bins (bars) on histogram */
            const size_t kNumBins = 9;
            
            /* Helper methods for updating histogram */
            void SetXValues();
            void SetBinFrequencies();
    };
}