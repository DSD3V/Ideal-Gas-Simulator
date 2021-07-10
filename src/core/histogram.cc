#include "core/histogram.h"

namespace idealgas {
    Histogram::Histogram(vector<Particle*> particles)
    : particles_(particles) {
        UpdateHistogram();
    }

    void Histogram::UpdateHistogram() {
        SetXValues();
        SetBinFrequencies();
    }
    
    void Histogram::SetXValues() {
        x_values_.clear(); //x values will change for each frame
        
        //get the current min and max speed
        float min_speed = std::numeric_limits<float>::max();
        float max_speed = 0;
        
        for (Particle* p : particles_) {
            if (p->speed < min_speed) min_speed = p->speed;
            if (p->speed > max_speed) max_speed = p->speed;
        }
        
        //min will be displayed first, so push it in first  
        x_values_.push_back(min_speed);
        
        //each other value will be based on the previous + bin_increment
        float bin_increment = (max_speed - min_speed) / kNumBins;
        for (size_t i = 1; i < kNumBins; ++i) {
            x_values_.push_back(x_values_[i - 1] + bin_increment);
        }
        
        //push max speed in last
        x_values_.push_back(max_speed);
    }
    
    void Histogram::SetBinFrequencies() {
        bin_frequencies_.clear(); //frequencies will change for each frame
        
        //will store number of particles in each bin, initialized to all 0s
        vector<float> frequencies(kNumBins,0);
        
        for (Particle* p : particles_) {
            for (size_t i = 0; i < x_values_.size() - 1; ++i) {
                //x_values_ is ordered, so if current speed is <= the next, it's in the current bin
                if (p->speed <= x_values_[i + 1]) {
                    frequencies[i]++;
                    break; //each particle should only be in 1 bin, so break once it's found
                }
            }
        }
        
        //# of particles in bin / total # of particles = frequency as %
        for (float& freq : frequencies) {
            bin_frequencies_.push_back(freq / particles_.size());
        }
    }

    vector<float>& Histogram::GetXValues() { return x_values_; }
    vector<float>& Histogram::GetBinFrequencies() { return bin_frequencies_; }
    vector<Particle*>& Histogram::GetParticles() { return particles_; }
}