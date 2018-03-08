/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** Created by arthur,
*/

#ifndef PSU_PHILOSOPHER_2017_PHILOSOPHER_H
# define PSU_PHILOSOPHER_2017_PHILOSOPHER_H

#include <pthread.h>
#include "philosophers.h"

enum phi_state
{
	EATING,
	SLEEPING,
	THINKING,
	UNDEFINED
};

struct philosopher
{
	void (*eat)(struct philosopher *this);
	void (*think)(struct philosopher *this);
	void (*sleep)(struct philosopher *this);

	pthread_t thread_id;
	enum phi_state state;
	pthread_mutex_t *chopstick;
	pthread_mutex_t *waiting_mutex;
	pthread_barrier_t *waiting;
	unsigned int eat_counter;
	unsigned int think_counter;
	unsigned int sleep_counter;
	unsigned int *meal_counter;
	struct phi_params *params;
	struct philosopher *next;
	struct philosopher *previous;
};

# define RIGHT_CHOPSTICK(x) x->next->chopstick

# define UNDEFINED_THREAD_ID ((unsigned) -1)
# define EATING_TIME_LIMIT 50
# define THINKING_TIME_LIMIT 50

struct philosopher *into_the_golden_age_of_science(struct phi_params *params);
struct philosopher *just_out_of_school(struct phi_params *params,
				       struct philosopher *previous,
				       struct philosopher *next);
struct philosopher *add_new_member(struct philosopher *circle,
				   struct philosopher *new_member,
				   unsigned int tie_up_loose_end);
void thus_falls_the_vienna_circle(struct philosopher *circle);
void simulator(struct phi_params *params);

#endif /* !PSU_PHILOSOPHER_2017_PHILOSOPHER_H */
