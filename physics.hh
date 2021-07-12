#ifndef PHYSICS_HH_INCLUDED
#define PHYSICS_HH_INCLUDED

/// A class containing all the physics

#include "lattice-base.hh"
#include<cmath>

class IsingPhysics{
    // We can have a reference as a member variable, but it needs to be defined
    // before the actual constructor
private:
    LatticeBase & lattice_;

public:

    IsingPhysics(LatticeBase & lattice): lattice_ (lattice)
        {}

    double isingHamiltonian() const;
    double magnetisation() const;
    double neighbour_spin_sum(int i, int j) const;
    void set_beta(double beta){beta_ = beta;}
    void set_magnetic_field(double B){magnetic_field_ = B;}
    void set_J_coupling(double J){J_coupling_ = J;}
    double beta() const {return beta_;}
    double weighted_parittion_function() const;

    double delta_hamiltonian(int i, int j) const;

private:
    double beta_ = 1;
    double magnetic_field_ = -10;
    double J_coupling_ = 1;
};

// ======================= Metropolis-Hastings Algorithm ===========================

#include <random>

// The actual Metropolis Hastings simulation bit
// By this point it is expected that the user has already set up the seed of the generator
class IsingModelMetropolis{

/// How the class works:
/// The algorithm is based on the symmetric MH alg. (see https://en.wikipedia.org/wiki/Metropolis%E2%80%93Hastings_algorithm)
/// 1) Start with an imported lattice. This is y
/// 2) Uniformly pick a lattice spacing (proposal for flipping). This is g(x | y). N.B. g(x | y) = g(y | x) [is symmetric]
/// 3) Calculate the acceptance factor alpha = f(y)/f(x), where f(x) = exp(-beta * Hamiltonian(x)).
///    Due to the setup, alpha = exp(-beta * \Delta Hamiltonian(x,y)) [see above]
/// 4) Accept/reject alpha with u ~ Uniform(0,1). If accepted, then return x, otherwise return x

private:
    LatticeBase & lattice_;


public:
    IsingModelMetropolis(LatticeBase & lattice):
        lattice_ (lattice), physics_content_ {IsingPhysics(lattice)}
    {}

    void set_beta(double beta){physics_content_.set_beta(beta);}
    void set_magnetic_field(double B){physics_content_.set_magnetic_field(B);}
    void set_verbose_state(bool verbose){verbose_ = verbose;}
    double magnetisation() {return physics_content_.magnetisation();}
    void next_step();

private:
    IsingPhysics physics_content_;
    bool verbose_ = false;


};

#endif // PHYSICS_HH_INCLUDED
