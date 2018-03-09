/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** Created by ccastelain,
*/

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "extern.h"
#include "philosopher.h"

void has_eaten(struct philosopher *member)
{
	if (member->think_counter < member->sleep_counter
	    && pthread_mutex_trylock(member->chopstick) != 0) {
		member->think(member);
		pthread_mutex_unlock(member->chopstick);
	} else
		member->sleep(member);
}

void has_thought(struct philosopher *member)
{
	if (pthread_mutex_trylock(member->chopstick) != 0
	    && pthread_mutex_trylock(RIGHT_CHOPSTICK(member)) != 0) {
		member->eat(member);
		pthread_mutex_unlock(member->chopstick);
		pthread_mutex_unlock(RIGHT_CHOPSTICK(member));
	}
}

void has_slept(struct philosopher *member)
{
	if (member->eat_counter < member->think_counter
	    && pthread_mutex_trylock(member->chopstick) != 0
	    && pthread_mutex_trylock(RIGHT_CHOPSTICK(member)) != 0) {
		member->eat(member);
		pthread_mutex_unlock(member->chopstick);
		pthread_mutex_unlock(RIGHT_CHOPSTICK(member));
	} else if (pthread_mutex_trylock(member->chopstick) != 0) {
		member->think(member);
		pthread_mutex_unlock(member->chopstick);
	}
}

void *entering_thread(void *member_addr)
{
	struct philosopher *member = (struct philosopher *) member_addr;

	while (member->eat_counter < member->params->meals_max - 1) {
		if (member->state == SLEEPING)
			has_slept(member);
		else if (member->state == THINKING)
			has_thought(member);
		else
			has_eaten(member);
	}
	pthread_mutex_lock(member->waiting_mutex);
	++*(member->meal_counter);
	if (*(member->meal_counter) == member->params->phi_nb)
		member->eat(member);
	pthread_mutex_unlock(member->waiting_mutex);
	pthread_barrier_wait(member->waiting);
	pthread_exit(NULL);
}

void simulator(struct phi_params *params)
{
	struct philosopher *circle = into_the_golden_age_of_science(params);
	int ret;

	if (!circle)
		return;
	for (unsigned int i = 0; i < params->phi_nb; i++) {
		ret = pthread_create(&(circle->thread_id), NULL,
				     &entering_thread, (void *)(circle));
		if (ret == EAGAIN)
			abort();
		circle = circle->next;
	}
	for (unsigned int i = 0; i < params->phi_nb; i++) {
		pthread_join(circle->thread_id, NULL);
		circle = circle->next;
	}
	thus_falls_the_vienna_circle(circle);
}