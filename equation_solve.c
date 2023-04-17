#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// step of segment division when we try to find subsegment with different signs on edges
#define STEP 0.01

// accuracy with which we what to find solutions of equation func(x) = 0
#define SOLUTION_ACCURACY 1.e-12

// accuracy for value equals 0 
#define EPS 1.e-45

// additional array memory of solution array overflow
#define ALLOCATION_STEP 5


// definition of function for finding roots
double func(double x)
{
    return sin(cos(x)) - cos(sin(x)) - sin(1) + 1;
}


//function for printing first argument amount of numbers in array in its second argument 
void print_all_solutions(int number_of_solutions, double *solution_array)
{
    printf("\nList of solutions: \n");
    for (int i = 0; i < number_of_solutions; i++) printf("Solution #%d: %.12lf\n", i+1, solution_array[i]);
    printf("\n");
}

// function that can add number in forth argument in array in third argument
// first argument is actual size of array, second argument is allocated size of array
// first three arguments have addition * because we want to change them in this function
void add(int *number_of_solutions, int *allocated_memory_for_solutions, double **solution_array, double root)
{
    ++(*number_of_solutions);
    if (*allocated_memory_for_solutions == 0) 
    {
        *allocated_memory_for_solutions = ALLOCATION_STEP;
        *solution_array = (double *) malloc (*allocated_memory_for_solutions * sizeof(double));
    }
    else
    {
        if (*allocated_memory_for_solutions < *number_of_solutions)
        {
            *allocated_memory_for_solutions += ALLOCATION_STEP;
            *solution_array = (double *) realloc (*solution_array, *allocated_memory_for_solutions * sizeof(double));
        }
    }
    //printf("\n1 - %d 2 - %d\n", *number_of_solutions, *allocated_memory_for_solutions);
    (*solution_array)[*number_of_solutions - 1] = root; 
}


// function for finding a root of function in first argument in segment between second and third arguments
// method is dividing the segment by two, we choose a half with different signs on its edges
double finding_root_with_division_by_two(double (*func)(double), double left_iterator, double right_iterator)
{
    while (right_iterator - left_iterator > SOLUTION_ACCURACY)
    {
        double middle = (left_iterator + right_iterator) / 2;
        if (fabs(func(middle)) < EPS) return middle;
        if (func(left_iterator) * func(middle) < 0)
        {
            right_iterator = middle; 
        }
        else
        {
            left_iterator = middle;
        } 
    }
    return (left_iterator + right_iterator) / 2;    
}

// finction for partitioning segment between second arguments and third arguments, finding solutions on segments with different
// signes on its edges, function definition is in the first argument, number of solutions - in forth, array of solution - in fifth 
int find_solutions(double (*func)(double), double start_arg, double end_arg, int *number_of_solutions, double **solution_array)
{
    int allocated_memory_for_solutions = 0;
    double left_iterator = start_arg;
    double right_iterator = start_arg + STEP;
    while (right_iterator < end_arg + EPS)
    {
        if (fabs(func(left_iterator)) < EPS)
        {
            add(number_of_solutions, &allocated_memory_for_solutions, solution_array, left_iterator);
            left_iterator += STEP / 10;
            continue; 
        }
        if (func(left_iterator)*func(right_iterator) < -EPS)
        {
            double new_root = finding_root_with_division_by_two(func, left_iterator, right_iterator);
            add(number_of_solutions, &allocated_memory_for_solutions, solution_array, new_root);
        }
        left_iterator = right_iterator;
        right_iterator += STEP;                                                              
    }	
    return 0;
}

int main(void)
{
    double start_arg, end_arg;
    printf("Enter the segment for finding solutions: ");
    scanf("%lf %lf", &start_arg, &end_arg);
    if (end_arg < start_arg)
    {
        printf("\nWrong points order");
    }
    else
    {
        int number_of_solutions = 0;
        double *solution_array;
        int solution_finding_code;
        solution_finding_code = find_solutions(func, start_arg, end_arg, &number_of_solutions, &solution_array);
        print_all_solutions(number_of_solutions, solution_array);
        free(solution_array);
    }
    return 0;
}