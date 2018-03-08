/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** Created by arthur,
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "extern.h"
#include "philosopher.h"

static void display_help(void)
{
	fprintf(stderr, "USAGE\n      ");
	fprintf(stderr, "./philo -p nbr_p -e nbr_e\n\n");
	fprintf(stderr, "DESCRIPTION\n");
	fprintf(stderr, "      -p nbr_p  number of philosophers\n");
	fprintf(stderr, "      -e nbr_e  maximum number times a philosopher");
	fprintf(stderr, " eats before exiting the program\n");
}

static long verif_arg(const char *binary, const char *supposed_num,
		      unsigned int *storage, unsigned int minimum_required)
{
	long ret = strtol(supposed_num, NULL, 10);

	if (ret < minimum_required || ret > UINT_MAX) {
		INVALID_ARG(binary, supposed_num);
		return (-1);
	}
	*storage = (unsigned int) ret;
	return (ret);
}

static unsigned int check_type_of_arg(char **av, unsigned int *i,
				      struct phi_params *params, int *done)
{
	long ret = 0;

	if (STRCMP(*(av + *i), "-p")) {
		ret = verif_arg(*av, av[*i + 1], &(params->phi_nb), 2);
		if (ret < 0)
			return (ERR_EXIT);
		*done |= PHI_NB_FLAG;
		++*i;
	} else if (STRCMP(*(av + *i), "-e")) {
		ret = verif_arg(*av, av[*i + 1], &(params->meals_max), 1);
		if (ret < 0)
			return (ERR_EXIT);
		++*i;
		*done |= MEALS_MAX_FLAG;
	} else {
		UNKNOWN_ARG(*av, *(av + *i));
		return (ERR_EXIT);
	}
	return (0);
}

static unsigned int parse_args(unsigned int ac, char **av,
			       struct phi_params *params)
{
	int done = 0x0;
	long ret = 0;

	for (unsigned int i = 1; i < ac; ++i) {
		if (i + 1 < ac)
			ret = check_type_of_arg(av, &i, params, &done);
		if (ret == ERR_EXIT)
			return (ERR_EXIT);
	}
	if (!(done & PHI_NB_FLAG) || !(done & MEALS_MAX_FLAG)) {
		MISSING_PHI_NB_FLAG;
		MISSING_MEALS_MAX_FLAG;
		return (ERR_EXIT);
	}
	return (NORMAL_RETURN);
}

int main(int ac, char **av)
{
	unsigned int err;
	struct phi_params params;

	if (ac == 2 && strcmp(*(av + 1), "--help") == 0) {
		display_help();
		return (NORMAL_RETURN);
	}
	err = parse_args((unsigned) ac, av, &params);
	if (err || RCFStartup(ac, av) != 0)
		return (ERR_EXIT);
	simulator(&params);
	RCFCleanup();
	return (err);
}