/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** Created by arthur,
*/

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "extern.h"
#include "philosopher.h"

static void eating_method(struct philosopher *this)
{
	lphilo_take_chopstick(this->chopstick);
	lphilo_take_chopstick(RIGHT_CHOPSTICK(this));
	lphilo_eat();
	usleep(EATING_TIME_LIMIT);
	this->state = EATING;
	++(this->eat_counter);
	lphilo_release_chopstick(this->chopstick);
	lphilo_release_chopstick(RIGHT_CHOPSTICK(this));
}

static void thinking_method(struct philosopher *this)
{
	lphilo_take_chopstick(this->chopstick);
	lphilo_think();
	usleep(THINKING_TIME_LIMIT);
	this->state = THINKING;
	++(this->think_counter);
	lphilo_release_chopstick(this->chopstick);
}

static void sleeping_method(struct philosopher *this)
{
	lphilo_sleep();
	this->state = SLEEPING;
	++(this->sleep_counter);
}

struct philosopher *just_out_of_school(struct phi_params *params,
				       struct philosopher *previous,
				       struct philosopher *next)
{
	struct philosopher *new_member = malloc(sizeof(struct philosopher));
	pthread_mutex_t *chopstick = malloc(sizeof(pthread_mutex_t));

	if (new_member == NULL || chopstick == NULL)
		return (NULL);
	pthread_mutex_init(chopstick, NULL);
	new_member->eat = &eating_method;
	new_member->think = &thinking_method;
	new_member->sleep = &sleeping_method;
	new_member->thread_id = UNDEFINED_THREAD_ID;
	new_member->chopstick = chopstick;
	new_member->state = UNDEFINED;
	new_member->eat_counter = 0;
	new_member->think_counter = 0;
	new_member->sleep_counter = 0;
	new_member->params = params;
	new_member->previous = previous;
	new_member->next = next;
	return (new_member);
}

static void free_mallocd_philo(struct philosopher *philosopher)
{
	pthread_mutex_destroy(philosopher->chopstick);
	free(philosopher->chopstick);
	free(philosopher);
}

void thus_falls_the_vienna_circle(struct philosopher *circle)
{
	struct philosopher *last_member = circle->previous;

	for (struct philosopher *it = circle, *itis = NULL;
	     it != last_member;) {
		itis = it;
		it = it->next;
		free_mallocd_philo(itis);
	}
	if (last_member) {
		pthread_mutex_destroy(last_member->waiting_mutex);
		pthread_barrier_destroy(last_member->waiting);
		free(last_member->waiting_mutex);
		free(last_member->waiting);
		free(last_member->meal_counter);
		free_mallocd_philo(last_member);
	}
}