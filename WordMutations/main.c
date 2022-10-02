#include "headers.h"

int main(int argc, char **argv)
{
    problem problem;

    char *file_dict = NULL, *file_pals = NULL;

    char extension[] = "dict";
    file_dict = get_arguments(argc, argv, file_dict, extension);

    strcpy(extension, "pals");
    file_pals = get_arguments(argc, argv, file_pals, extension);

    readProblemFile(&problem, file_pals);

    free(file_pals);
    return EXIT_SUCCESS;
}