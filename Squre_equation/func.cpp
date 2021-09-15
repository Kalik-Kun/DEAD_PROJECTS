//
// Created by arlik_null on 11.09.2021.
//

#include "func.h"

char *name_input_file = "/home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Squre_equation/values.txt";
long time_of_working_program = clock();
extern double precision = 0.0001;

////////////////////////////////////////////////////////////////////////////////////////
/// SHARE OF PROGRAM FOR USER MOD                                                   ///
///////////////////////////////////////////////////////////////////////////////////////

answer search_ans(var_equation var) {

    double Discriminant = NAN; // Discriminant of equation
    answer ans = {NAN, NAN, ERROR};   // answer that func return

    if (fabs(var.a) < precision) {
        if (fabs(var.b) < precision) {
            if (fabs(var.c) < precision) {
                return {0, 0, INFINITY_SOLVE}; // mean that you have infinity solve
            }
            return {0, 0, NO_SOLVE}; // mean that you don't have solve;
        }
        return {-var.c / var.b, -var.c / var.b, ONE_SOLVE};  // it's linear equation if a == 0
    }

    Discriminant = var.b * var.b - 4 * var.a * var.c;;

    if (fabs(Discriminant) < precision) return calc_ans_with_one_root(var.a, var.b);
    if (Discriminant < 0) return {0, 0, NO_SOLVE};

    return calc_ans_with_two_roots(var.a, var.b, sqrt(Discriminant));

}

void search_ans_for_user () {

    double Discriminant = NAN; // Discriminant of equation
    struct var_equation var = input_var(); // our variables
    answer ans = {NAN, NAN, ERROR}; // return answer of equation

    printf("You input: a: %lf, this b: %lf, this c: %lf\n",
           var.a, var.b, var.c);

    ans = search_ans(var);
    switch(search_ans(var).type_answer) {
        case NO_SOLVE:
            printf("The equation have 0 answer\n"
                   "The equation doesn't have answers\n");
            time_program();
            return;

        case ONE_SOLVE:
            std::printf("The equation have 1 answer:\n x = %lf\n",
                        ans.x1);
            time_program();
            return ;

        case TWO_SOLVE:
            ans = calc_ans_with_two_roots(var.a, var.b, Discriminant);
            printf("The equation have 2 answer:\n"
                   "x1 = %lf\n"
                   "x2 = %lf\n"
                   "END OF PROGRAM\n",
                   ans.x1, ans.x2);
            time_program();
            return ;

        case INFINITY_SOLVE:
            printf("The equation have infinity answers\n"
                   "The equation is not square.\n");
            time_program();
            return;

        case ERROR:
            printf("ERROR\n");
            time_program();
            return;
    }
}

var_equation input_var() {
    var_equation var = {0, 0, 0};
    int check_number_input = 0;  // check number input that you input just 3 variable

    printf("\n\nEnter 3 numbers\n"
           "that are the roots of the square equation\n");
    check_number_input =
            scanf("%lf%lf%lf", &var.a, &var.b, &var.c);

    if (check_number_input != 3) {
        printf("ERROR on input\n"
               "program doesn't read numbers\n"
               "Please reboot program\n\n");
        time_program();
        return {NAN, NAN, NAN};
    }

    return var;
}

answer calc_ans_with_two_roots(const double a, const double b, const double sqrt_Discriminant) {
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(sqrt_Discriminant));

    double x1 = (- b + sqrt_Discriminant) / (2 * a);
    double x2 = (- b - sqrt_Discriminant) / (2 * a);

    return answer {x1, x2, TWO_SOLVE};
}

answer calc_ans_with_one_root(const double a, const double b) {
    assert(isfinite(a));
    assert(isfinite(b));

    double x = 0;
    if (b == 0) return {0, 0, 0};
    x = -b / 2 * a;
    return {x, x, ONE_SOLVE};
}

////////////////////////////////////////////////////////////////////////////////////////
/// SHARE OF PROGRAM FOR UNIT TESTS                                            ///
///////////////////////////////////////////////////////////////////////////////////////

char unit_test() {
    FILE* file_with_values_for_test = nullptr;
    int size = 0;
    int type_answer = 0;
    if ((file_with_values_for_test = fopen(name_input_file, "r")) == NULL) {
        printf("\nERROR open file\n");
        return 0;
    }

    fscanf(file_with_values_for_test, "%d", &size);

    for (int i = 1; i <= size; i ++) {
        double a, b, c, x1, x2;
        fscanf(file_with_values_for_test, "%lf%lf%lf",
               &a, &b, &c);
        fscanf(file_with_values_for_test, "%lf%lf%d",
               &x1, &x2, &type_answer);
        if (unit_test_check_equal({a, b, c}, {x1, x2, type_answer}, i) == 0)
            return 0;
    }

    return 1;
}

char unit_test_check_equal (var_equation input_var, answer real_answer, const int number) {
    answer prog_answer = search_ans(input_var);

    if (real_answer.x1 == prog_answer.x1 && real_answer.x2 == prog_answer.x2
    && real_answer.type_answer == prog_answer.type_answer) {
        printf("\n\n___________________________________\n"
                          "___________________________________\n"
                          "UNIT TEST %d SUCCESSFULLY COMPLETED\n"
                          "___________________________________\n"
                          "___________________________________\n\n\n", number);
        return 1;
    }

    printf( "\n\n___________________________________\n"
                       "___________________________________\n"
                       "UNIT TEST %d FAILED\n"
                       "___________________________________\n"
                       "___________________________________\n\n\n", number);
    printf(  "input_var: %lf. %lf, %lf\n"
                    "prog_answer: %lf, %lf, %d\n"
                    "real_answer: %lf, %lf, %d\n\n",
            input_var.a, input_var.b, input_var.c,
            prog_answer.x1, prog_answer.x2, prog_answer.type_answer,
            real_answer.x1, real_answer.x2, real_answer.type_answer);

    return 0;
}

void time_program () {
    printf("END OF PROGRAM\n\n\nWorking Time of the Program:"
           " %f sec\nNumber Tacks: %ld\n",
           (float)time_of_working_program / CLOCKS_PER_SEC,
           time_of_working_program);
}