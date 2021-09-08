#include "equation.h"
#include <cstring>
#include <iomanip>

double calc_discr                     (double , double , double );
std::pair<double, double> calc_ans    (double , double , double );

int main() {
    double first_param = 0, second_param = 0, third_param = 0;
    int numb_ent_var = 0;
    std::pair<double, double> answer;
    std::printf("Hello It is a square equation\n"
                "Please enter 3 value a, b, c (ax^2 + bx + c)\n\n");
//    std::setprecision(PRECISION);
    
    while (numb_ent_var < 3) {
        char error_string[3];
        numb_ent_var = std::scanf("%lf%*c%lf%*c%lf",
                                  &first_param, &second_param, &third_param);
        if (numb_ent_var == 3) continue;

        std::printf("\n\nError in input\n"
                    "You enter %d variables\n"
                    "There are a: %lf, b: %lf, c: %lf\n"
                    "Please enter the variables as mentioned above\n"
                    "Do you want exit from program?\n"
                    "Enter Yes, if you want or another symbol if not.\n\n",
                    numb_ent_var, first_param, second_param, third_param);

        std::scanf("%3s", error_string);
        if (std::strcmp(error_string, "Yes") == 0) {
            printf("\nIt's end of the program\n");
            return 0;
        }
    }

    printf("You input: a: %lf, this b: %lf, this c: %lf", first_param, second_param, third_param);

    answer = calc_ans(first_param, second_param, third_param);


    printf("The equation have 2 answer:\nx1 = %lf\nx2 = %lf",
                                        answer.first, answer.second);
    return 0;
}



double calc_discr(double first, double second, double third) {
    double Discriminant;
    Discriminant = second * second - 4 * first * third;
    return Discriminant;
}

std::pair<double, double> calc_ans(double first, double second, double third) {
    double Discriminant = calc_discr(first, second, third);
    double x1, x2;

    x1 = (- second + std::sqrt(Discriminant)) / 2 * first;
    x2 = (- second - std::sqrt(Discriminant)) / 2 * first;

    return std::pair<double, double> {x1, x2};
}
