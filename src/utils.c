/*
 * utils.c
 * 29-12-14
 * Marcos Díez García
 *
 * Some miscellaneous functions.
 *
 * */
#include <stdlib.h>
#include <stdio.h>


void error(char *details)
{
        fputs("darwin Error: ", stderr);
        fputs(details, stderr);
        fputc('\n', stderr);
        exit(1);
}

void error_verbose(char *file_name, char *function_name, char *details)
{
        fputs("darwin Error: ", stderr);
        fprintf(stderr, "[FILE %s]", file_name);
        fprintf(stderr, "(FUNCTION %s) ", function_name);
        fputs(details, stderr);
        fputc('\n', stderr);
        exit(1);
}

