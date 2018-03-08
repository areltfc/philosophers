/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** Created by arthur,
*/

#ifndef PSU_PHILOSOPHER_2017_PHILOSOPHERS_H
# define PSU_PHILOSOPHER_2017_PHILOSOPHERS_H

enum
{
	TRUE = 1,
	FALSE = 0
};

struct phi_params
{
	unsigned int phi_nb;
	unsigned int meals_max;
};

# define NORMAL_RETURN 0
# define ERR_EXIT 84
# define SEEK_HELP "Execute ./philo --help for help\n"
# define INVALID_ARG(x, y) fprintf(stderr, "%s: %s: invalid argument\n", x, y)
# define UNKNOWN_ARG(x, y) fprintf(stderr, "%s: %s: unknown argument\n", x, y)

# define PHI_NB_FLAG (1 << 0)
# define MEALS_MAX_FLAG (1 << 1)
# define MISSING_FLAG(x) fprintf(stderr, "%s: missing %s flag\n%s",	\
				 *av, x, SEEK_HELP)
# define MISSING_PHI_NB_FLAG if (!(done & PHI_NB_FLAG)) { MISSING_FLAG("-p"); }
# define MISSING_MEALS_MAX_FLAG if (!(done & MEALS_MAX_FLAG))	\
	{ MISSING_FLAG("-e"); }

# define STRCMP(x, y) (strcmp(x, y) == 0)

#endif /* !PSU_PHILOSOPHER_2017_PHILOSOPHERS_H */
