//
// Created by arlik_null on 08.09.2021.
//

#include "equation.h"


Equation_class::Equation_class(double first, double second, double third) {
    this->first  = first;
    this->second = second;
    this->third  = third;
}

Equation_class::~Equation_class() {
    std::printf("Equation CLass was deleted");
}

double Equation_class::calc_discr() const {
    double Discriminant;
    Discriminant = this->second * this->second - 4 * this->first * this->third;
    return Discriminant;
}

std::pair<double, double> Equation_class::calc_ans() const {
    double Discriminant = calc_discr();
    double x1, x2;

    x1 = (- this->second + std::sqrt(Discriminant)) / 2*this->first;
    x2 = (- this->second - std::sqrt(Discriminant)) / 2*this->first;

    return std::pair<double, double> {x1, x2};
}

