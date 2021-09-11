//
// Created by arlik_null on 11.09.2021.
//

#include <cstring>
#include <iomanip>
#include <stdio.h>
#include <time.h>
#include <math.h>


#define PERCEPTION      0.0001
#define GOLD_NUMBER     983564723252235
#define INF_ANSWERS     467370092834754
#define NOTHING_ANSWERS 389670239878574
#define MODERATOR_MOD   0
#define USER_MODE       1
#define FILENAME_INPUT  "/home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Squre_equation/values.txt"
extern long time_of_working_program; // global variable, it calculates time what program is working

struct my_pair      {double x1, x2;};
struct var_equation {double a, b, c;};

my_pair               research_ans          (const int , var_equation var = {0, 0, 0});                                           // research roots of equation
var_equation          input_var             ();
my_pair               check_zero            (const int, const var_equation);                             // char mean bool, check variable on zero
int                   check_discr           (const double );                                  // return int for switch in research_ans, check discriminant on zero
double                calc_discr            (const var_equation);                             // count discriminant
my_pair               calc_ans              (const double , const double , const double );    // calculate answer when we have 2 roots
double                calc_ans              (const double , const double );                   // calculate answer when we have 1 root
char                  unit_test             ();                                               // char mean bool, unit test program
char                  unit_test_check_equal (var_equation, my_pair, const int);
void                  time_program          ();                                               // time what program is working