#include "visualizer/histograms.h"
#include <sstream>

using namespace ci;

namespace idealgas {
    Histograms::Histograms(const size_t num, const size_t width, const size_t height, glm::vec2 top_left, ParticleController& particle_controller)
            : kNumHists(num), 
              kHistWidth(width),
              kHistHeight(height),
              hist_top_left_(top_left),
              particle_controller_(particle_controller) {
        
        //Vector storing vector of each type of particle, each to be passed into a Histogram object
        vector<vector<Particle*>> particle_vectors;
        for (size_t i = 0; i < kNumHists; ++i) {
            vector<Particle*> v;
            particle_vectors.push_back(v);
        }
        
        for (Particle& p : particle_controller_.GetParticles()) {
            switch(p.type) {
                case 1:
                    particle_vectors[0].push_back(&p);
                    break;
                case 2:
                    particle_vectors[1].push_back(&p);
                    break;
                case 3:
                    particle_vectors[2].push_back(&p);
                    break;
            }
        }
        
        //initializes histograms_ with histogram objects initialized with a vector of a certain type of particle
        for (size_t i = 0; i < kNumHists; ++i) {
            Histogram h(particle_vectors[i]);
            histograms_.push_back(h);
        }
    }

    void Histograms::UpdateHistograms() {
        for (Histogram& hist : histograms_) {
            hist.UpdateHistogram();
        }
    }

    void Histograms::DrawHistograms() {
        float first_top_left_y = hist_top_left_.y; //will temporarily change, so store in variable
        
        for (Histogram& hist : histograms_) {
            DrawHistogram(hist);
            //adds margin to the bottom of histogram
            hist_top_left_.y += kHistHeight + 73;
        }
        
        hist_top_left_.y = first_top_left_y;
    }

    void Histograms::DrawHistogram(Histogram& hist) {
        gl::color(hist.GetParticles()[0]->color);
        DrawHistBorder();
        DrawHistTitle();
        DrawXLabels(hist);
        DrawYLabels(hist);
        DrawBars(hist);
    }
    
    void Histograms::DrawHistBorder() {
        Rectf hist_border(hist_top_left_.x, hist_top_left_.y,
                          hist_top_left_.x + kHistWidth, hist_top_left_.y + kHistHeight);
        gl::drawStrokedRect(hist_border, 1);
    }
    
    void Histograms::DrawHistTitle() {
        Font title_font("Roboto", 23);
        gl::drawStringCentered("Distribution of Speeds",
                               glm::vec2(hist_top_left_.x + kHistWidth / 2, hist_top_left_.y - 22),
                               Colorf(1, 1, 1), title_font);

        gl::drawSolidCircle(glm::vec2(hist_top_left_.x + 102, hist_top_left_.y - 14), 7);
        gl::drawSolidCircle(glm::vec2(hist_top_left_.x + kHistWidth - 102, hist_top_left_.y - 14), 7);
    }
    
    void Histograms::DrawXLabels(Histogram& hist) {
        //draw main label "Speed"
        Font label_font("Roboto", 20);
        gl::drawStringCentered("Speed (px/frame)",
                               glm::vec2(hist_top_left_.x + kHistWidth / 2, hist_top_left_.y + kHistHeight + 22),
                               Colorf(1, 1, 1), label_font);
        //draw speeds
        Font speed_font("Roboto", 20);
        float top_left_x = hist_top_left_.x; //will change for each x label
        
        //make axis values have 2 decimals
        std::stringstream ss;
        ss.precision(2);
        
        for (float& f : hist.GetXValues()) {
            ss << std::fixed << f;
            gl::drawStringCentered(ss.str(), glm::vec2(top_left_x + 12, hist_top_left_.y + kHistHeight + 3),
                                   Colorf(1, 1, 1), speed_font);
            
            top_left_x += 42; //adds space for next value
            ss.str(string()); //clears stringstream
        }
    }
    
    void Histograms::DrawYLabels(Histogram& hist) {
        //draw main label "Frequency"
        Font label_font("Roboto", 20);
        gl::pushModelMatrix();
        gl::translate(hist_top_left_.x - 55, hist_top_left_.y + (kHistHeight / 2));
        gl::rotate(-1.57f);
        gl::drawStringCentered("Frequency (%)",
                               glm::vec2(0, 0),
                               Colorf(1, 1, 1), label_font);
        gl::popModelMatrix();
        
        //draw frequencies (as percentages)
        Font freq_font("Roboto", 20);
        float top_left_y = hist_top_left_.y; //will change for each y label
        vector<string> y_axis_labels = {"0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100"};
        
        for (string label : y_axis_labels) {
            gl::drawStringCentered(label,
                                   glm::vec2(hist_top_left_.x - 15, top_left_y + kHistHeight - 12),
                                   Colorf(1, 1, 1), freq_font);
            
            top_left_y -= 20; //adds space for next value
        }
    }
    
    void Histograms::DrawBars(Histogram& hist) {
        float top_left_x = hist_top_left_.x; //will change for each bar
        
        //height of each bar is bottom of histogram - frequency (%) * height of histogram (y decreases as you go "up")
        for (float& freq : hist.GetBinFrequencies()) {
            Rectf bar(top_left_x, (hist_top_left_.y + kHistHeight) - (freq * kHistHeight),
                      top_left_x + 45, hist_top_left_.y + kHistHeight);
            
            gl::drawSolidRect(bar);
            top_left_x += 45; //shift top left over to the end of the current bar
        }
    }
}