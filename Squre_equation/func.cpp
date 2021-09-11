//
// Created by arlik_null on 11.09.2021.
//

#include "func.h"

long time_of_working_program = clock();

my_pair research_ans(const int mod, var_equation var) {

    double Discriminant = 0;
    int numb_ent_var = 0;
    my_pair answer = {0, 0};

    ////////////////////////////////////////////////////////////////////////////////////////
    /// SHARE OF PROGRAM FOR MODERATOR MOD                                               ///
    ///////////////////////////////////////////////////////////////////////////////////////

    if (mod == MODERATOR_MOD) {
        my_pair zero_answer = check_zero(mod, var);

        if (zero_answer.x1 != GOLD_NUMBER) return zero_answer;

        Discriminant = calc_discr(var);

        switch(check_discr(Discriminant)) {
            case -1:
                return {NOTHING_ANSWERS, NOTHING_ANSWERS};
            case 0:
                answer.x1 = calc_ans(var.a, var.b);
                return {answer.x1, answer.x1};
            default:
                break;
        }

        answer = calc_ans(var.a, var.b, Discriminant);
        return answer;
    }
    ////////////////////////////////////////////////////////////////////////////////////////
    /// SHARE OF PROGRAM FOR USER MOD                                                   ///
    ///////////////////////////////////////////////////////////////////////////////////////

    var = input_var();
    if (var.a == GOLD_NUMBER)  return {GOLD_NUMBER, GOLD_NUMBER};

    printf("You input: a: %lf, this b: %lf, this c: %lf\n",
           var.a, var.b, var.c);

    check_zero(mod, var);
    Discriminant = calc_discr(var);

    switch(check_discr(Discriminant)) {
        case -1:
            std::printf("Discriminant is Negative. Equations doesn't have equation.\n");
            return {GOLD_NUMBER, GOLD_NUMBER};
        case 0:
            answer.x1 = calc_ans(var.a, var.b);
            std::printf("The equation have 1 answer:\n x = %lf\n",
                        answer.x1);
            time_program();
            return {answer.x1, answer.x1};
        default:
            break;
    }

    answer = calc_ans(var.a, var.b, Discriminant);

    printf("The equation have 2 answer:\n"
           "x1 = %lf\n"
           "x2 = %lf\n"
           "END OF PROGRAM\n",
           answer.x1, answer.x2);

    time_program();

    return answer;
}

var_equation input_var() {
    var_equation var = {0, 0, 0};
    int check_number_input = 0;

    printf("\n\nУEnter 3 numbers\n"
           "that are the roots of the square equation\n");
    check_number_input =
            scanf("%lf%lf%lf", &var.a, &var.b, &var.c);

    if (check_number_input != 3) {
        printf("ERROR on input\n"
               "program doesn't read numbers\n"
               "Please reboot program\n\n");
        time_program();
        return {GOLD_NUMBER, GOLD_NUMBER, GOLD_NUMBER};
    }

    return var;
}

my_pair check_zero(const int mod, const var_equation var) {
    ////////////////////////////////////////////////////////////////////////////////////////
    /// SHARE OF PROGRAM FOR MODERATOR MOD                                               ///
    ///////////////////////////////////////////////////////////////////////////////////////
    if (mod == MODERATOR_MOD) {
        if (-PERCEPTION < var.a && var.a < PERCEPTION) {
            if (-PERCEPTION < var.b && var.b < PERCEPTION) {
                if (-PERCEPTION < var.c && var.c < PERCEPTION) {
                    return {INF_ANSWERS, INF_ANSWERS};
                }
                return {NOTHING_ANSWERS, NOTHING_ANSWERS};
            }
            return {-var.c / var.a, -var.c / var.a};
        }
        return {GOLD_NUMBER, GOLD_NUMBER};
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    /// SHARE OF PROGRAM FOR USER MOD                                                   ///
    ///////////////////////////////////////////////////////////////////////////////////////
    if (-PERCEPTION < var.a && var.a < PERCEPTION) {
        if (-PERCEPTION < var.b && var.b < PERCEPTION) {
            if (-PERCEPTION < var.c && var.c < PERCEPTION) {
                printf("The equation have infinity answers\n"
                       "The equation is not square.\n");
                time_program();
                return {INF_ANSWERS, INF_ANSWERS};
            }
            printf("The equation have 0 answer\n"
                   "The equation doesn't have answers\n");
            time_program();
            return {NOTHING_ANSWERS, NOTHING_ANSWERS};
        }
        printf("The equation have 1 answer\n"
               "The equation is not square. It's Linear\n"
               "x = %lf", -var.c/var.a);
        time_program();
        return {-var.c/var.a, -var.c/var.a};
    }
    return {GOLD_NUMBER, GOLD_NUMBER};
}

int check_discr(const double Discriminant) {
    if (Discriminant < 0)  return -1;
    if (Discriminant == 0) return  0;
    return 1;
}

double calc_discr (const var_equation var) {
    double Discriminant;
    Discriminant = var.b * var.b - 4 * var.a * var.c;
    return Discriminant;
}

my_pair calc_ans (const double a, const double b, const double Discriminant) {
    double x1, x2;

    x1 = (- b + std::sqrt(Discriminant)) / 2 * a;
    x2 = (- b - std::sqrt(Discriminant)) / 2 * a;

    return my_pair {x1, x2};
}

double calc_ans  (const double a, const double b) {
    double x = 0;
    if (b == 0) return 0;
    x = -b / 2 * a;
    return x;
}

char unit_test() {
    FILE* file_with_values_for_test;
    int size = 0;
    if ((file_with_values_for_test = fopen(FILENAME_INPUT, "r")) == NULL) {
        printf("\nERROR open file\n");
        return 0;
    }

    fscanf(file_with_values_for_test, "%d", &size);

    for (int i = 1; i <= size; i ++) {
        double a, b, c, x1, x2;
        fscanf(file_with_values_for_test, "%lf%lf%lf",
               &a, &b, &c);
        fscanf(file_with_values_for_test, "%lf%lf",
               &x1, &x2);
        if (unit_test_check_equal({a, b, c,}, {x1, x2}, i) == 0)
            return 0;
    }

    return 1;
}

char unit_test_check_equal (var_equation input_var, my_pair real_answer, const int number) {
    my_pair prog_answer = research_ans(MODERATOR_MOD, input_var);
    if (real_answer.x1 == prog_answer.x1 && real_answer.x2 == prog_answer.x2) {
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
                    "prog_answer: %lf, %lf\n"
                    "real_answer: %lf, %lf\n\n",
            input_var.a, input_var.b, input_var.c,
            prog_answer.x1, prog_answer.x2, real_answer.x1, real_answer.x2);

    return 0;
}

void time_program () {
    printf("END OF PROGRAM\n\n\nWorking Time of the Program:"
           " %f sec\nNumber Tacks: %ld\n",
           (float)time_of_working_program / CLOCKS_PER_SEC,
           time_of_working_program);
}