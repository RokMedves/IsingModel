#include "lattice-bounded.hh"
#include "lattice-periodic.hh"
#include "physics.hh"

#include<ctime>

// These definitions need to be here, otherwise each inclusion
// of lattice-base.hh means we're defining this again, which yields a compiler error
char spin::Spin::spin_down_sprite_ = 'd';
char spin::Spin::spin_up_sprite_ = 'u';

void test_individual_classes(){
    // Initialise the random number generator
    srand( time( NULL ) );


    std::cout << "hello" << std::endl;
    LatticeBoundedSoft latticeb(5, 5);
    LatticePeriodic latticep(5, 5);
    std::cout << latticeb;

    std::cout << std::endl;
    latticeb.set_spin_down_sprite(' ');
    latticep.set_spin_up_sprite('.');

    std::cout << latticeb;

    // testing the physics
    IsingPhysics physics {latticep};
    std::cout << physics.weighted_parittion_function() << std::endl;
    std::cout << physics.magnetisation() << std::endl;

    // Doing the Metropolis stuff
    IsingModelMetropolis simulation {latticep};
    simulation.set_verbose_state(true);
    simulation.next_step();
    std::cout << latticep << std::endl;
}

#include <cstdlib>   // For clearing the screen
#include <windows.h> // For sleep()

int main(int argc, char* argv[]){

    //test_individual_classes();

    srand( time( NULL ) );

    LatticePeriodic latticep(20, 20);
    latticep.set_spin_down_sprite(' ');
    latticep.set_spin_up_sprite('.');

    IsingModelMetropolis simulation {latticep};
    simulation.set_verbose_state(false);
    double beta;
    std::cin >> beta;
    simulation.set_beta(beta);
    simulation.set_magnetic_field(0);

    // A frame-by-frame simulation
/*
    for(int i = 0; i < 500; ++i){
        if(i % 100 == 0){
            std::cout << std::endl << std::endl << "i: " << i << std::endl;
            std::cout << latticep << std::endl;
        }
        simulation.next_step();
    }
*/

    // A smooth simulation
    unsigned int i = 0;
    const unsigned int simulation_steps = 25;
    const unsigned int wait_interval = 50;
    while(true){
        // Clear the screen
        std::system("cls");

        // Print the new lattice
        std::cout << "i: " << i << std::endl;
        std::cout << latticep << std::endl;
        std::cout << "magnetisation: " << simulation.magnetisation() << std::endl;
        // Do the next step and sleep
        for(int j = 0; j < simulation_steps; ++j){
            simulation.next_step();
            ++i;
        }
        Sleep(wait_interval);
    }

    return 0;
}
