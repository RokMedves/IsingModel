#ifndef __LATTICE_HH___
#define __LATTICE_HH___

// Lattice containing spins

class LatticeBase{
private:
  // forward declaration of the data type
  typedef double spin;

public:
  LatticeBase(unsigned int n): _lattice_size {n}
  {
    _lattice = new spin[n];

    // set the lattice to a random state 
    initialize_lattice();
  }

  virtual ~LatticeBase() {
    delete _lattice;
  };

  void flip_spin(int i, int j);
  
  // overriden access specifier
  virtual spin& operator() (int i, int j) = 0;
  
private:

  unsigned int _lattice_size;
  spin* _lattice;

  void initialize_lattice();
};



#endif //__LATTICE_HH___
