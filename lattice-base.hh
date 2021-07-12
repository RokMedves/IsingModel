#ifndef LATTICE_BASE_HH_INCLUDED
#define LATTICE_BASE_HH_INCLUDED

#include <cassert>
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace spin{
    /// Definition of spin
    class Spin{
    public:

        Spin(double spin){
            assert((spin != spin_up || spin != spin_down) &&
                   "Initialised spin not spin down or up!");
            spin_state_ = spin;
        }

        Spin() : Spin{-0.5 + rand() % 2}{
            //create a random spin direction
            //std::srand(static_cast<unsigned int>(std::time(nullptr)));
            //redundant, but a bit takes into account Spin(double)'s operations
        }

        // Flip the spin
        Spin & flip(){
            spin_state_ = -spin_state_;
            return *this;
        }

        // implicit conversion operators
        operator double() const {return spin_state_;}
        operator float()  const {return spin_state_;}

        // arithmetic operators
        //Spin operator*(const Spin & spin)const{return Spin(spin_state_ * spin.spin_state_);} //THIS IS WRONG!!!
        //Spin &operator*=(const Spin & spin){spin_state_ = spin_state_ * spin.spin_state_; return *this;}
        Spin operator==(const Spin & spin){return spin_state_ == spin.spin_state_;}
        double operator+(double d){return (spin_state_ + d);}
        double operator*(double d){return (spin_state_ * d);}
        friend double operator+(double d, const Spin & s){return (d + s.spin_state_);}
        friend double operator*(double d, const Spin & s){return (d * s.spin_state_);}
        friend double& operator+=(double&d, const Spin & s){d += s.spin_state_; return d;}
        friend double& operator-=(double&d, const Spin & s){d -= s.spin_state_; return d;}
        friend double& operator*=(double&d, const Spin & s){d *= s.spin_state_; return d;}

        //setting up the sprites and printing
        void set_spin_up_sprite(char c){spin_up_sprite_ = c;}
        void set_spin_down_sprite(char c){spin_down_sprite_ = c;}

        friend std::ostream & operator<< (std::ostream & out, const Spin & spin){
            if (spin.spin_state_ == spin.spin_up){out << spin.spin_up_sprite_;}
            else{out << spin.spin_down_sprite_;}
            return out;
        }

    private:
        const double spin_up   =  0.5;
        const double spin_down = -0.5;
        static char spin_up_sprite_; //these are static such that setting it once will set it everywhere
        static char spin_down_sprite_;
        double spin_state_;
    };

}


/// A class which stores the 2D lattice.
/// Inherited types should specialise a periodic or continued lattice etc.
class LatticeBase {

public:

    LatticeBase(unsigned int sizex, unsigned int sizey):
        lattice_size_x_ {sizex}, lattice_size_y_ {sizey}
    {
        // create a 1D lattice with size x \times y
        // The entries are completely random
        spin_lattice_ = new spin::Spin [sizex * sizey];
    }

    unsigned int xsize() const {return lattice_size_x_;}
    unsigned int ysize() const {return lattice_size_y_;}

    /// setting the sprites of the lattice
    // THIS SEEMS SUPER UNSAFE!
    void set_spin_up_sprite(char c){spin_lattice_[0].set_spin_up_sprite(c);}
    void set_spin_down_sprite(char c){spin_lattice_[0].set_spin_down_sprite(c);}

    // Functions to add:
    // - a randomise lattice function. The implementation should
    //   only sample a bool and if true, then flip the given
    //   lattice point
    // - a flip spin at place function?

    virtual ~LatticeBase(){delete[] spin_lattice_;}
    /// What needs to be overloaded - the lattice access. A pure virtual function
    virtual spin::Spin & operator()(int x, int y) const = 0;

    friend std::ostream & operator<< (std::ostream & out, const LatticeBase& lattice){
        for(int i = 0; i < lattice.lattice_size_x_; ++i){
            for(int j = 0; j < lattice.lattice_size_y_; ++j){
                out << lattice(i, j);
            }
            out << std::endl;
        }
        return out;
    }

protected:
    spin::Spin* spin_lattice_;
private:
     const unsigned int lattice_size_x_;
     const unsigned int lattice_size_y_;

};

#endif // LATTICE_BASE_HH_INCLUDED
