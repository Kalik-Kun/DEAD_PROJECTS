//
// Created by arlik_null on 11.09.2021.
//

#include <string.h>
#include <iomanip>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


extern double precision;             // precision zero (that is, with what accuracy we count zero)
extern char *name_input_file;        // Name input file
extern long time_of_working_program; // global variable, it calculates time what program is working

enum type_answer {
    NO_SOLVE,
    ONE_SOLVE,
    TWO_SOLVE,
    INFINITY_SOLVE,
    ERROR,
};

struct answer {double x1, x2; int type_answer;}; /*x1 and x2 - solve of equation.
 *  type_answer - shows the type of the returned value there are three types:
 *  0 - no solve
 *  1 - one solve
 *  2 - two solve
 *  3 - infinity solves
 *  4 - error
 *
 *  when infinity or no solves x1 = 0 and x2 = 0
 */
struct var_equation {double a, b, c;};

answer                search_ans  (var_equation);                                    /* search roots of equation for unit test.
                                                                                                    *The function differs from the lower one in the absence of text output   */
void                  search_ans_for_user       ();                                                // search roots of equation for user

var_equation          input_var                 ();                                                //input varibale of equation
answer                calc_ans_with_two_roots   (const double , const double , const double );     // calculate answer when it have 2 roots
answer                calc_ans_with_one_root    (const double , const double );                    // calculate answer when it have 1 roots()
char                  unit_test                 ();                                                // func for unit test
char                  unit_test_check_equal     (var_equation, answer, const int);                 // circle comporation real answers and program answer
void                  time_program              ();                                                // time program work