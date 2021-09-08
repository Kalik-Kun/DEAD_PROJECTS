//
// Created by arlik_null on 08.09.2021.
//

#include <iostream>
#include <math.h>

#define MAXSIZE  std::inf
#define PRECISION 16

class Equation_class {
private:
    double first, second, third;
public:

    Equation_class                      (double , double , double );
    ~Equation_class                     ();

    double calc_discr                   () const;
    std::pair<double, double> calc_ans   () const;
};
