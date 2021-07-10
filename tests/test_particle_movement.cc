#include <catch2/catch.hpp>
#include "core/particle_controller.h"
#include <limits>

namespace idealgas {
    /* - Each call to UpdateParticles represents one unit of time, or frame
       - Bounds passed to ParticleController (0, 10, 0, 10) simulates a 10x10 box */

    TEST_CASE("One particle moving with no collisions") {
        glm::vec2 pos(5, 5);
        glm::vec2 vel(1, 1);
        Particle p(0, pos, vel, 1, 1, "Red");

        vector<Particle> v = {p};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(8, 8);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Velocity doesn't change") {
            glm::vec2 expected_vel = glm::vec2(1, 1);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Two particles moving with no collisions") {
        glm::vec2 pos1(1, 1);
        glm::vec2 vel1(1, 0);
        Particle p1(0, pos1, vel1, 1, 1, "Red");

        glm::vec2 pos2(5, 5);
        glm::vec2 vel2(0, 1);
        Particle p2(0, pos2, vel2, 1, 1, "Red");

        vector<Particle> v = {p1, p2};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Particle 1 position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(3, 1);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Particle 1 velocity doesn't change") {
            glm::vec2 expected_vel = glm::vec2(1, 0);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }

        SECTION("Particle 2 position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(5, 7);
            glm::vec2 actual_pos = pc.GetParticles()[1].pos;

            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Particle 2 velocity doesn't change") {
            glm::vec2 expected_vel = glm::vec2(0, 1);
            glm::vec2 actual_vel = pc.GetParticles()[1].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Particle collides with top wall") {
        glm::vec2 pos(5, 1);
        glm::vec2 vel(0, -1);
        Particle p(0, pos, vel, 1, 1, "Red");

        vector<Particle> v = {p};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(5, 4);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Velocity gets negated") {
            glm::vec2 expected_vel = glm::vec2(0, 1);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Particle collides with bottom wall") {
        glm::vec2 pos(5, 9);
        glm::vec2 vel(0, 1);
        Particle p(0, pos, vel, 1, 1, "Red");

        vector<Particle> v = {p};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(5, 6);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Velocity gets negated") {
            glm::vec2 expected_vel = glm::vec2(0, -1);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Particle collides with left wall") {
        glm::vec2 pos(1, 5);
        glm::vec2 vel(-1, 0);
        Particle p(0, pos, vel, 1, 1, "Red");

        vector<Particle> v = {p};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(4, 5);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Velocity gets negated") {
            glm::vec2 expected_vel = glm::vec2(1, 0);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Particle collides with right wall") {
        glm::vec2 pos(9, 5);
        glm::vec2 vel(1, 0);
        Particle p(0, pos, vel, 1, 1, "Red");

        vector<Particle> v = {p};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(6, 5);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Velocity gets negated") {
            glm::vec2 expected_vel = glm::vec2(-1, 0);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Particle colliding with top wall at an angle") {
        glm::vec2 pos(5, 1);
        glm::vec2 vel(1, -1);
        Particle p(0, pos, vel, 1, 1, "Red");

        vector<Particle> v = {p};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(8, 4);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Velocity gets negated") {
            glm::vec2 expected_vel = glm::vec2(1, 1);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Particle colliding with bottom wall at an angle") {
        glm::vec2 pos(5, 9);
        glm::vec2 vel(1, 1);
        Particle p(0, pos, vel, 1, 1, "Red");

        vector<Particle> v = {p};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(8, 6);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Velocity gets negated") {
            glm::vec2 expected_vel = glm::vec2(1, -1);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Particle colliding with left wall at an angle") {
        glm::vec2 pos(1, 5);
        glm::vec2 vel(-1, 1);
        Particle p(0, pos, vel, 1, 1, "Red");

        vector<Particle> v = {p};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(4, 8);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Velocity gets negated") {
            glm::vec2 expected_vel = glm::vec2(1, 1);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Particle colliding with right wall at an angle") {
        glm::vec2 pos(9, 5);
        glm::vec2 vel(1, -1);
        Particle p(0, pos, vel, 1, 1, "Red");

        vector<Particle> v = {p};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(6, 2);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Velocity gets negated") {
            glm::vec2 expected_vel = glm::vec2(-1, -1);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Two particles collide straight on") {
        glm::vec2 pos1(4, 5);
        glm::vec2 vel1(1, 0);
        Particle p1(0, pos1, vel1, 1, 1, "Red");

        glm::vec2 pos2(5, 5);
        glm::vec2 vel2(-1, 0);
        Particle p2(0, pos2, vel2, 1, 1, "Red");

        vector<Particle> v = {p1, p2};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Particle 1 position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(1, 5);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Particle 1 velocity updates correctly") {
            glm::vec2 expected_vel = glm::vec2(-1, 0);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }

        SECTION("Particle 2 position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(8, 5);
            glm::vec2 actual_pos = pc.GetParticles()[1].pos;

            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Particle 2 velocity updates correctly") {
            glm::vec2 expected_vel = glm::vec2(1, 0);
            glm::vec2 actual_vel = pc.GetParticles()[1].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Two particles collide at an angle") {
        glm::vec2 pos1(4, 5);
        glm::vec2 vel1(1, -1);
        Particle p1(0, pos1, vel1, 1, 1, "Red");

        glm::vec2 pos2(6, 5);
        glm::vec2 vel2(-1, -1);
        Particle p2(0, pos2, vel2, 1, 1, "Red");

        vector<Particle> v = {p1, p2};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Particle 1 position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(1, 2);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Particle 1 velocity updates correctly") {
            glm::vec2 expected_vel = glm::vec2(-1, -1);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }

        SECTION("Particle 2 position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(9, 2);
            glm::vec2 actual_pos = pc.GetParticles()[1].pos;

            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Particle 2 velocity updates correctly") {
            glm::vec2 expected_vel = glm::vec2(1, -1);
            glm::vec2 actual_vel = pc.GetParticles()[1].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Particle touching but moving away from wall doesn't collide") {
        glm::vec2 pos(0, 5);
        glm::vec2 vel(1, 0);
        Particle p(0, pos, vel, 1, 1, "Red");

        vector<Particle> v = {p};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();

        SECTION("Particle position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(1, 5);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Particle velocity doesn't change") {
            glm::vec2 expected_vel = glm::vec2(1, 0);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Particles touching but moving away from each other don't collide") {
        glm::vec2 pos1(5, 5);
        glm::vec2 vel1(1, 0);
        Particle p1(0, pos1, vel1, 1, 1, "Red");

        glm::vec2 pos2(5, 5);
        glm::vec2 vel2(-1, 0);
        Particle p2(0, pos2, vel2, 1, 1, "Red");

        vector<Particle> v = {p1, p2};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();

        SECTION("Particle 1 position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(6, 5);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Particle 1 velocity updates correctly") {
            glm::vec2 expected_vel = glm::vec2(1, 0);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }

        SECTION("Particle 2 position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(4, 5);
            glm::vec2 actual_pos = pc.GetParticles()[1].pos;

            REQUIRE(actual_pos == expected_pos);
        }

        SECTION("Particle 2 velocity updates correctly") {
            glm::vec2 expected_vel = glm::vec2(-1, 0);
            glm::vec2 actual_vel = pc.GetParticles()[1].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Particles of different masses collide straight on") {
        glm::vec2 pos1(4, 5);
        glm::vec2 vel1(1, 0);
        Particle p1(0, pos1, vel1, 1, 1, "Red");

        glm::vec2 pos2(6, 5);
        glm::vec2 vel2(-1, 0);
        Particle p2(0, pos2, vel2, 2, 1, "Red");

        vector<Particle> v = {p1, p2};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Particle 1 position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(0.667, 5);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos.x == Approx(expected_pos.x).epsilon(0.01));
            REQUIRE(actual_pos.y == expected_pos.y);
        }

        SECTION("Particle 1 velocity updates correctly") {
            glm::vec2 expected_vel = glm::vec2(-1.667, 0);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel.x == Approx(expected_vel.x).epsilon(0.01));
            REQUIRE(actual_vel.y == expected_vel.y);
        }

        SECTION("Particle 2 position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(6.667, 5);
            glm::vec2 actual_pos = pc.GetParticles()[1].pos;

            REQUIRE(actual_pos.x == Approx(expected_pos.x).epsilon(0.01));
            REQUIRE(actual_pos.y == expected_pos.y);
        }

        SECTION("Particle 2 velocity updates correctly") {
            glm::vec2 expected_vel = glm::vec2(0.333, 0);
            glm::vec2 actual_vel = pc.GetParticles()[1].vel;

            REQUIRE(actual_vel.x == Approx(expected_vel.x).epsilon(0.01));
            REQUIRE(actual_vel.y == expected_vel.y);
        }
    }

    TEST_CASE("Particles of different masses collide at an angle") {
        glm::vec2 pos1(4, 5);
        glm::vec2 vel1(1, -1);
        Particle p1(0, pos1, vel1, 1, 1, "Red");

        glm::vec2 pos2(6, 5);
        glm::vec2 vel2(-1, -1);
        Particle p2(0, pos2, vel2, 2, 1, "Red");

        vector<Particle> v = {p1, p2};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.UpdateParticles();
        pc.UpdateParticles();

        SECTION("Particle 1 position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(0.667, 3);
            glm::vec2 actual_pos = pc.GetParticles()[0].pos;

            REQUIRE(actual_pos.x == Approx(expected_pos.x).epsilon(0.01));
            REQUIRE(actual_pos.y == expected_pos.y);
        }

        SECTION("Particle 1 velocity updates correctly") {
            glm::vec2 expected_vel = glm::vec2(-1.667, -1);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel.x == Approx(expected_vel.x).epsilon(0.01));
            REQUIRE(actual_vel.y == expected_vel.y);
        }

        SECTION("Particle 2 position updates correctly") {
            glm::vec2 expected_pos = glm::vec2(6.667, 3);
            glm::vec2 actual_pos = pc.GetParticles()[1].pos;

            REQUIRE(actual_pos.x == Approx(expected_pos.x).epsilon(0.01));
            REQUIRE(actual_pos.y == expected_pos.y);
        }

        SECTION("Particle 2 velocity updates correctly") {
            glm::vec2 expected_vel = glm::vec2(0.333, -1);
            glm::vec2 actual_vel = pc.GetParticles()[1].vel;

            REQUIRE(actual_vel.x == Approx(expected_vel.x).epsilon(0.01));
            REQUIRE(actual_vel.y == expected_vel.y);
        }
    }

    TEST_CASE("Pressing 1 increases velocity of particles") {
        glm::vec2 pos1(4, 5);
        glm::vec2 vel1(1, 0);
        Particle p1(0, pos1, vel1, 1, 1, "Red");

        glm::vec2 pos2(6, 5);
        glm::vec2 vel2(-2, 0);
        Particle p2(0, pos2, vel2, 2, 1, "Red");

        vector<Particle> v = {p1, p2};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.ChangeSpeeds(true); //called when user presses 1 on keyboard

        SECTION("Particle 1 velocity increases") {
            glm::vec2 expected_vel = glm::vec2(1.10, 0);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel == expected_vel);
        }

        SECTION("Particle 2 velocity increases") {
            glm::vec2 expected_vel = glm::vec2(-2.20, 0);
            glm::vec2 actual_vel = pc.GetParticles()[1].vel;

            REQUIRE(actual_vel == expected_vel);
        }
    }

    TEST_CASE("Pressing 0 decreases velocity of particles") {
        glm::vec2 pos1(4, 5);
        glm::vec2 vel1(1, 0);
        Particle p1(0, pos1, vel1, 1, 1, "Red");

        glm::vec2 pos2(6, 5);
        glm::vec2 vel2(-2, 0);
        Particle p2(0, pos2, vel2, 2, 1, "Red");

        vector<Particle> v = {p1, p2};

        ParticleController pc(v, 0, 10, 0, 10);

        pc.ChangeSpeeds(false); //called when user presses 0 on keyboard

        SECTION("Particle 1 velocity decreases") {
            glm::vec2 expected_vel = glm::vec2(.909, 0);
            glm::vec2 actual_vel = pc.GetParticles()[0].vel;

            REQUIRE(actual_vel.x == Approx(expected_vel.x).epsilon(0.01));
            REQUIRE(actual_vel.y == expected_vel.y);
        }

        SECTION("Particle 2 velocity decreases") {
            glm::vec2 expected_vel = glm::vec2(-1.818, 0);
            glm::vec2 actual_vel = pc.GetParticles()[1].vel;

            REQUIRE(actual_vel.x == Approx(expected_vel.x).epsilon(0.01));
            REQUIRE(actual_vel.y == expected_vel.y);
        }
    }
}