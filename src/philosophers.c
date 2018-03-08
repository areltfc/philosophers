/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** Created by arthur,
*/

#include <stdlib.h>
#include "philosopher.h"

struct philosopher *init_shared_attributes(struct philosopher *circle)
{
	unsigned int *meal_counter = malloc(sizeof(int));
	pthread_barrier_t *waiting = malloc(sizeof(pthread_barrier_t));
	pthread_mutex_t *waiting_mutex = malloc(sizeof(pthread_mutex_t));
	struct philosopher *it = circle;

	if (meal_counter == NULL || waiting == NULL || waiting_mutex == NULL) {
		thus_falls_the_vienna_circle(circle);
		return (NULL);
	}
	*meal_counter = 0;
	pthread_barrier_init(waiting, NULL, circle->params->phi_nb);
	pthread_mutex_init(waiting_mutex, NULL);
	for (unsigned int i = 0; i < circle->params->phi_nb; ++i) {
		it->meal_counter = meal_counter;
		it->waiting = waiting;
		it->waiting_mutex = waiting_mutex;
		it = it->next;
	}
	return (circle);
}

struct philosopher *into_the_golden_age_of_science(struct phi_params *params)
{
	struct philosopher *circle = just_out_of_school(params, NULL, NULL);
	struct philosopher *current = NULL;
	struct philosopher *prev = circle;

	if (circle == NULL)
		return (NULL);
	for (unsigned int i = 1; i < params->phi_nb; ++i) {
		current = just_out_of_school(params, prev, NULL);
		if (current == NULL) {
			thus_falls_the_vienna_circle(circle);
			return (NULL);
		}
		if (i == params->phi_nb - 1)
			circle = add_new_member(circle, current, TRUE);
		else
			circle = add_new_member(circle, current, FALSE);
		prev = current;
	}
	return (init_shared_attributes(circle));
}

struct philosopher *add_new_member(struct philosopher *circle,
				   struct philosopher *new_member,
				   unsigned int tie_up_loose_end)
{
	struct philosopher *it = circle;

	if (tie_up_loose_end) {
		circle->previous = new_member;
		new_member->next = circle;
	}
	for (; it->next != NULL; it = it->next);
	it->next = new_member;
	new_member->previous = it;
	return (circle);
}

