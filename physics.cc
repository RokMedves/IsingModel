#include "physics.hh"

double IsingPhysics::neighbour_spin_sum(int i, int j) const{
    double spin_sum = 0;

    // box formation
    for(int k=-1; k < 2; ++k){
        for(int l=-1; l < 2; ++l){
            spin_sum += lattice_(i+k,j+l);
        }
    }
    /*
    // Do a nearest neighbour sum. First up & down, then left & right
    for(int k=-1; k < 2; ++k){
        spin_sum += lattice_(i+k,j);
    }
    for(int l=-1; l < 2; ++l){
        spin_sum += lattice_(i,j+l);
    }
    */
    return spin_sum;
}

double IsingPhysics::isingHamiltonian() const{
    double magnetic_term = 0;
    double neighbour_term = 0;

    // The magnetic term
    if(magnetic_field_ != 0){
        for(int i = 0; i < lattice_.xsize(); ++i){
            for(int j = 0; j < lattice_.ysize(); ++j){
                magnetic_term += double(lattice_(i,j));
            }
        }
        magnetic_term *= -magnetic_field_;
    }

    // The neighbour term
    for(int i = 0; i < lattice_.xsize(); ++i){
            for(int j = 0; j < lattice_.ysize(); ++j){
                neighbour_term += lattice_(i, j) * neighbour_spin_sum(i,j);
            }
        }
    // return the final result
    return magnetic_term + J_coupling_ * neighbour_term;
}


double IsingPhysics::magnetisation() const{
    /// returns the average spin per site

    double magnetisation = 0;
    for(int i = 0; i < lattice_.xsize(); ++i){
        for(int j = 0; j < lattice_.ysize(); ++j){
            magnetisation += lattice_(i, j);
        }
    }
    return magnetisation / lattice_.xsize() / lattice_.ysize();
}

double IsingPhysics::weighted_parittion_function() const{
    return exp(-beta_ * isingHamiltonian());
}


double IsingPhysics::delta_hamiltonian(int i, int j) const{
/// Return the difference in the Hamiltonian if the spin at
/// position (i,j) is flipped. \Delta H = H[(i,j) flipped] - H[not flipped]

    double magnetic_term_difference  = - 2 * lattice_(i, j) * magnetic_field_;
    double neighbour_term_difference = - 2 * lattice_(i, j) * neighbour_spin_sum(i, j);

    return neighbour_term_difference + magnetic_term_difference;
}


// =================================== Metropolis stuff =============================================

void IsingModelMetropolis::next_step(){

    // Get a lattice space to flip
    int i = rand() % lattice_.xsize();
    int j = rand() % lattice_.ysize();
    if(verbose_){std::cout << "trying to flip: (" << i << ", " << j << ")" << std::endl;}

    // Try to flip the selected spin
    double acceptance_ratio = exp(physics_content_.beta() * physics_content_.delta_hamiltonian(i,j));
    if (verbose_){std::cout << "acceptance ratio: " << acceptance_ratio << "\t (beta = " << physics_content_.beta() << ")" << std::endl;}

    // Accept or reject
    std::uniform_real_distribution<double> acc_rej_distribution{0.0,1.0};
    double accept_reject_factor=((double)rand()/(double)RAND_MAX);
    if(verbose_){std::cout << "acceptance factor: " << accept_reject_factor << std::endl;}

    // Approve the change if accepted. Otherwise leave the lattice unchanged
    if(accept_reject_factor <= acceptance_ratio){lattice_(i,j).flip();}
    if(verbose_){
        std:: cout << "Spin was: ";
        if(accept_reject_factor <= acceptance_ratio){std::cout << "flipped" << std::endl;}
        else{std::cout << "not flipped" << std::endl;}
    }
}
