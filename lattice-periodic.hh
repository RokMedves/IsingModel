#ifndef LATTICE_PERIODIC_HH_INCLUDED
#define LATTICE_PERIODIC_HH_INCLUDED

#include "lattice-base.hh"

class LatticePeriodic : public LatticeBase{


public:
    LatticePeriodic(unsigned int sizex, unsigned int sizey):
        LatticeBase{sizex, sizey}
        {}

    virtual spin::Spin & operator()(int x, int y) const override{
        /// For a periodic lattice:
        ///
        /// Both negative and positive values must be considered.
        /// Wlog look at the example for x
        /// First, [x % lattice size] to get rid of the period.
        /// Second, if x > 0, start counting up from 0. Otherwise,
        /// count down from the lattice size.
        /// Equivalently this can be achieved by first trimming,
        /// then adding a lattice size, and trimming again.

        int x_steps = (xsize() + (x % xsize())) % xsize();
        int y_steps = (ysize() + (y % ysize())) % ysize();
        return spin_lattice_[x_steps + y_steps * ysize()];
    }

};


#endif // LATTICE_PERIODIC_HH_INCLUDED
