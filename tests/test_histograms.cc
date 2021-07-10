#include <catch2/catch.hpp>
#include <limits>
#include "core/particle_controller.h"
#include "core/histogram.h"

namespace idealgas {
    /* - Each call to UpdateParticles and UpdateHistogram represents one unit of time, or frame
       - Bounds passed to ParticleController (0, 10, 0, 10) simulates a 10x10 box */
    
    TEST_CASE("Histogram updates correctly single particle moving no collisions") {
        SECTION("Check that histogram displays correct values when a single particle moves with no collisions") {
            glm::vec2 pos(5, 5);
            glm::vec2 vel(1, 1);

            Particle p(0, pos, vel, 1, 1, "Red");

            vector<Particle> v_pc = {p};

            ParticleController pc(v_pc, 0, 10, 0, 10);

            vector<Particle*> v = {&pc.GetParticles()[0]};

            Histogram h(v);

            //histogram before particle moves
            vector<float> expected_x_values = {1.4142f, 1.4142f, 1.4142f, 1.4142f, 1.4142f, 1.4142f, 1.4142f, 1.4142f, 1.4142f, 1.4142f};
            vector<float> expected_bin_freqs = {1, 0, 0, 0, 0, 0, 0, 0, 0};

            vector<float> actual_x_values = h.GetXValues();
            vector<float> actual_bin_freqs = h.GetBinFrequencies();

            for (size_t i = 0; i < actual_x_values.size(); ++i) {
                REQUIRE(actual_x_values[i] == Approx(expected_x_values[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs.size(); ++i) {
                REQUIRE(actual_bin_freqs[i] == expected_bin_freqs[i]);
            }

            pc.UpdateParticles();
            h.UpdateHistogram();
            pc.UpdateParticles();
            h.UpdateHistogram();

            actual_x_values = h.GetXValues();
            actual_bin_freqs = h.GetBinFrequencies();

            //histogram after particle moves - no changes
            for (size_t i = 0; i < actual_x_values.size(); ++i) {
                REQUIRE(actual_x_values[i] == Approx(expected_x_values[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs.size(); ++i) {
                REQUIRE(actual_bin_freqs[i] == expected_bin_freqs[i]);
            }
        }

        SECTION("Check that histogram displays correct values when two particles move with no collisions") {
            glm::vec2 pos1(1, 1);
            glm::vec2 vel1(1, 1);

            Particle p1(0, pos1, vel1, 1, 1, "Red");

            glm::vec2 pos2(9, 9);
            glm::vec2 vel2(-2, -2);

            Particle p2(0, pos2, vel2, 1, 1, "Red");

            vector<Particle> v_pc = {p1, p2};

            ParticleController pc(v_pc, 0, 10, 0, 10);

            vector<Particle*> v = {&pc.GetParticles()[0], &pc.GetParticles()[1]};

            Histogram h(v);

            //histogram before particles move
            //bin increment: 0.1571
            vector<float> expected_x_values = {1.4142f, 1.5713f, 1.7284f, 1.8855f, 2.0426f, 2.1997f, 2.3568f, 2.5139f, 2.671f, 2.8284f};
            vector<float> expected_bin_freqs = {0.5, 0, 0, 0, 0, 0, 0, 0, 0.5};

            vector<float> actual_x_values = h.GetXValues();
            vector<float> actual_bin_freqs = h.GetBinFrequencies();

            for (size_t i = 0; i < actual_x_values.size(); ++i) {
                REQUIRE(actual_x_values[i] == Approx(expected_x_values[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs.size(); ++i) {
                REQUIRE(actual_bin_freqs[i] == expected_bin_freqs[i]);
            }

            pc.UpdateParticles();
            h.UpdateHistogram();
            pc.UpdateParticles();
            h.UpdateHistogram();

            actual_x_values = h.GetXValues();
            actual_bin_freqs = h.GetBinFrequencies();

            //histogram after particles move - no changes
            for (size_t i = 0; i < actual_x_values.size(); ++i) {
                REQUIRE(actual_x_values[i] == Approx(expected_x_values[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs.size(); ++i) {
                REQUIRE(actual_bin_freqs[i] == expected_bin_freqs[i]);
            }
        }
    }

    TEST_CASE("Histogram updates correctly when 2 particles collide with walls") {
        SECTION("Check that histogram displays correct values when two particles collide with wall") {
            glm::vec2 pos1(5, 1);
            glm::vec2 vel1(1,-1);

            Particle p1(0, pos1, vel1, 1, 1, "Red");

            glm::vec2 pos2(5, 9);
            glm::vec2 vel2(2, 2);

            Particle p2(0, pos2, vel2, 1, 1, "Red");

            vector<Particle> v_pc = {p1, p2};

            ParticleController pc(v_pc, 0, 10, 0, 10);

            vector<Particle*> v = {&pc.GetParticles()[0], &pc.GetParticles()[1]};

            Histogram h(v);

            //histogram before particles collide with wall
            //bin increment: 0.1571
            vector<float> expected_x_values = {1.4142f, 1.5713f, 1.7284f, 1.8855f, 2.0426f, 2.1997f, 2.3568f, 2.5139f, 2.671f, 2.8284f};
            vector<float> expected_bin_freqs = {0.5, 0, 0, 0, 0, 0, 0, 0, 0.5};

            vector<float> actual_x_values = h.GetXValues();
            vector<float> actual_bin_freqs = h.GetBinFrequencies();

            for (size_t i = 0; i < actual_x_values.size(); ++i) {
                REQUIRE(actual_x_values[i] == Approx(expected_x_values[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs.size(); ++i) {
                REQUIRE(actual_bin_freqs[i] == expected_bin_freqs[i]);
            }

            pc.UpdateParticles();
            h.UpdateHistogram();
            pc.UpdateParticles();
            h.UpdateHistogram();

            actual_x_values = h.GetXValues();
            actual_bin_freqs = h.GetBinFrequencies();

            //histogram after particle collide with wall - wall collision doesn't change speed
            for (size_t i = 0; i < actual_x_values.size(); ++i) {
                REQUIRE(actual_x_values[i] == Approx(expected_x_values[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs.size(); ++i) {
                REQUIRE(actual_bin_freqs[i] == expected_bin_freqs[i]);
            }
        }
    }

    TEST_CASE("Histogram updates correctly when 2 particles of same mass collide with each other") {
        SECTION("Check that histogram displays correct values when two particles of same mass collide with each other head on") {
            glm::vec2 pos1(5, 5);
            glm::vec2 vel1(2,0);

            Particle p1(0, pos1, vel1, 1, 1, "Red");

            glm::vec2 pos2(6, 5);
            glm::vec2 vel2(-3, 0);

            Particle p2(0, pos2, vel2, 1, 1, "Red");

            vector<Particle> v_pc = {p1, p2};

            ParticleController pc(v_pc, 0, 10, 0, 10);

            vector<Particle*> v = {&pc.GetParticles()[0], &pc.GetParticles()[1]};

            Histogram h(v);

            //histogram before particles collide
            //bin increment: 0.1111
            vector<float> expected_x_values = {2, 2.1111f, 2.2222f, 2.3333f, 2.4444f, 2.5555f, 2.6666f, 2.7777f, 2.8888f, 3};
            vector<float> expected_bin_freqs = {0.5, 0, 0, 0, 0, 0, 0, 0, 0.5};

            vector<float> actual_x_values = h.GetXValues();
            vector<float> actual_bin_freqs = h.GetBinFrequencies();

            for (size_t i = 0; i < actual_x_values.size(); ++i) {
                REQUIRE(actual_x_values[i] == Approx(expected_x_values[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs.size(); ++i) {
                REQUIRE(actual_bin_freqs[i] == expected_bin_freqs[i]);
            }

            pc.UpdateParticles();
            h.UpdateHistogram();
            pc.UpdateParticles();
            h.UpdateHistogram();

            actual_x_values = h.GetXValues();
            actual_bin_freqs = h.GetBinFrequencies();

            //histogram after head-on same mass collision - collision doesn't change speed
            for (size_t i = 0; i < actual_x_values.size(); ++i) {
                REQUIRE(actual_x_values[i] == Approx(expected_x_values[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs.size(); ++i) {
                REQUIRE(actual_bin_freqs[i] == expected_bin_freqs[i]);
            }
        }
    }

    TEST_CASE("Histogram updates correctly when 2 particles of different masses collide with each other") {
        SECTION("Check that histogram displays correct values when two particles of different masses collide with each other head on") {
            glm::vec2 pos1(5, 5);
            glm::vec2 vel1(2,0);

            Particle p1(0, pos1, vel1, 1, 1, "Red");

            glm::vec2 pos2(6, 5);
            glm::vec2 vel2(-3, 0);

            Particle p2(0, pos2, vel2, 10, 1, "Red");

            vector<Particle> v_pc = {p1, p2};

            ParticleController pc(v_pc, 0, 10, 0, 10);

            vector<Particle*> v1 = {&pc.GetParticles()[0]};

            vector<Particle*> v2 = {&pc.GetParticles()[1]};

            //diff. masses = diff. particles = 2 histograms
            Histogram h1(v1);
            Histogram h2(v2);

            //histograms before particles collide
            vector<float> expected_x_values_h1 = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
            vector<float> expected_bin_freqs_h1 = {1, 0, 0, 0, 0, 0, 0, 0, 0};

            vector<float> expected_x_values_h2 = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
            vector<float> expected_bin_freqs_h2 = {1, 0, 0, 0, 0, 0, 0, 0, 0};

            vector<float> actual_x_values_h1 = h1.GetXValues();
            vector<float> actual_bin_freqs_h1 = h1.GetBinFrequencies();

            vector<float> actual_x_values_h2 = h2.GetXValues();
            vector<float> actual_bin_freqs_h2 = h2.GetBinFrequencies();

            for (size_t i = 0; i < actual_x_values_h1.size(); ++i) {
                REQUIRE(actual_x_values_h1[i] == Approx(expected_x_values_h1[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs_h1.size(); ++i) {
                REQUIRE(actual_bin_freqs_h1[i] == expected_bin_freqs_h1[i]);
            }

            for (size_t i = 0; i < actual_x_values_h2.size(); ++i) {
                REQUIRE(actual_x_values_h2[i] == Approx(expected_x_values_h2[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs_h2.size(); ++i) {
                REQUIRE(actual_bin_freqs_h2[i] == expected_bin_freqs_h2[i]);
            }

            pc.UpdateParticles();
            h1.UpdateHistogram();
            h2.UpdateHistogram();
            pc.UpdateParticles();
            h1.UpdateHistogram();
            h2.UpdateHistogram();

            //histogram after head-on different mass collision - p1 speeds up, p2 slows down

            expected_x_values_h1 = {7.09091f, 7.09091f, 7.09091f, 7.09091f, 7.09091f, 7.09091f, 7.09091f, 7.09091f, 7.09091f, 7.09091f};
            expected_bin_freqs_h1 = {1, 0, 0, 0, 0, 0, 0, 0, 0};

            expected_x_values_h2 = {2.09091f, 2.09091f, 2.09091f, 2.09091f, 2.09091f, 2.09091f, 2.09091f, 2.09091f, 2.09091f, 2.09091f};
            expected_bin_freqs_h2 = {1, 0, 0, 0, 0, 0, 0, 0, 0};

            actual_x_values_h1 = h1.GetXValues();
            actual_bin_freqs_h1 = h1.GetBinFrequencies();

            actual_x_values_h2 = h2.GetXValues();
            actual_bin_freqs_h2 = h2.GetBinFrequencies();
            
            for (size_t i = 0; i < actual_x_values_h1.size(); ++i) {
                REQUIRE(actual_x_values_h1[i] == Approx(expected_x_values_h1[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs_h1.size(); ++i) {
                REQUIRE(actual_bin_freqs_h1[i] == expected_bin_freqs_h1[i]);
            }
            for (size_t i = 0; i < actual_x_values_h2.size(); ++i) {
                REQUIRE(actual_x_values_h2[i] == Approx(expected_x_values_h2[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs_h2.size(); ++i) {
                REQUIRE(actual_bin_freqs_h2[i] == expected_bin_freqs_h2[i]);
            }
        }
        
        SECTION("Check that histogram displays correct values when two particles of different masses collide with each other one from behind") {
            glm::vec2 pos1(5, 5);
            glm::vec2 vel1(0,0);

            Particle p1(0, pos1, vel1, 1, 1, "Red");

            glm::vec2 pos2(8, 5);
            glm::vec2 vel2(-5, 0);

            Particle p2(0, pos2, vel2, 20, 2, "Red");

            vector<Particle> v_pc = {p1, p2};

            ParticleController pc(v_pc, 0, 10, 0, 10);

            vector<Particle*> v1 = {&pc.GetParticles()[0]};

            vector<Particle*> v2 = {&pc.GetParticles()[1]};

            //diff. masses = diff. particles = 2 histograms
            Histogram h1(v1);
            Histogram h2(v2);

            //histograms before particles collide
            vector<float> expected_x_values_h1 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            vector<float> expected_bin_freqs_h1 = {1, 0, 0, 0, 0, 0, 0, 0, 0};

            vector<float> expected_x_values_h2 = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
            vector<float> expected_bin_freqs_h2 = {1, 0, 0, 0, 0, 0, 0, 0, 0};

            vector<float> actual_x_values_h1 = h1.GetXValues();
            vector<float> actual_bin_freqs_h1 = h1.GetBinFrequencies();

            vector<float> actual_x_values_h2 = h2.GetXValues();
            vector<float> actual_bin_freqs_h2 = h2.GetBinFrequencies();

            for (size_t i = 0; i < actual_x_values_h1.size(); ++i) {
                REQUIRE(actual_x_values_h1[i] == Approx(expected_x_values_h1[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs_h1.size(); ++i) {
                REQUIRE(actual_bin_freqs_h1[i] == expected_bin_freqs_h1[i]);
            }
            for (size_t i = 0; i < actual_x_values_h2.size(); ++i) {
                REQUIRE(actual_x_values_h2[i] == Approx(expected_x_values_h2[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs_h2.size(); ++i) {
                REQUIRE(actual_bin_freqs_h2[i] == expected_bin_freqs_h2[i]);
            }

            pc.UpdateParticles();
            h1.UpdateHistogram();
            h2.UpdateHistogram();

            pc.UpdateParticles();
            h1.UpdateHistogram();
            h2.UpdateHistogram();

            pc.UpdateParticles();
            h1.UpdateHistogram();
            h2.UpdateHistogram();

            //histogram after different mass collision at an angle - p1 speeds up, p2 slows down

            expected_x_values_h1 = {9.52381f, 9.52381f, 9.52381f, 9.52381f, 9.52381f, 9.52381f, 9.52381f, 9.52381f, 9.52381f, 9.52381f};
            expected_bin_freqs_h1 = {1, 0, 0, 0, 0, 0, 0, 0, 0};

            expected_x_values_h2 = {4.52381f, 4.52381f, 4.52381f, 4.52381f, 4.52381f, 4.52381f, 4.52381f, 4.52381f, 4.52381f, 4.52381f};
            expected_bin_freqs_h2 = {1, 0, 0, 0, 0, 0, 0, 0, 0};

            actual_x_values_h1 = h1.GetXValues();
            actual_bin_freqs_h1 = h1.GetBinFrequencies();

            actual_x_values_h2 = h2.GetXValues();
            actual_bin_freqs_h2 = h2.GetBinFrequencies();
            
            for (size_t i = 0; i < actual_x_values_h1.size(); ++i) {
                REQUIRE(actual_x_values_h1[i] == Approx(expected_x_values_h1[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs_h1.size(); ++i) {
                REQUIRE(actual_bin_freqs_h1[i] == expected_bin_freqs_h1[i]);
            }
            for (size_t i = 0; i < actual_x_values_h2.size(); ++i) {
                REQUIRE(actual_x_values_h2[i] == Approx(expected_x_values_h2[i]).epsilon(0.001));
            }
            for (size_t i = 0; i < actual_bin_freqs_h2.size(); ++i) {
                REQUIRE(actual_bin_freqs_h2[i] == expected_bin_freqs_h2[i]);
            }
        }
    }
}