#ifndef LATTICE_BOUNDED_HH_INCLUDED
#define LATTICE_BOUNDED_HH_INCLUDED

#include "lattice-base.hh"

class LatticeBoundedSoft : public LatticeBase{

public:
    LatticeBoundedSoft(unsigned int sizex, unsigned int sizey):
        LatticeBase{sizex, sizey}
        {}

    virtual spin::Spin & operator()(int x, int y) const override{
        if((x < xsize() && y < ysize()) ||
           (x > -1 && y > -1)){
            //return 0;
            return spin_lattice_[x + y * ysize()];
           }else{
        return spin_lattice_[x + y * ysize()];
           }
    }

};

class LatticeBoundedHard : public LatticeBase{

public:
    LatticeBoundedHard(unsigned int sizex, unsigned int sizey):
        LatticeBase{sizex, sizey}
        {}

    virtual spin::Spin & operator()(int x, int y) const override{
        assert((x < xsize() && y < ysize()) && "Index too large");
        assert((x > -1 && y > -1) && "Index too small");
        return spin_lattice_[x + y * ysize()];
    }

};

#endif // LATTICE_BOUNDED_HH_INCLUDED
