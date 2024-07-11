/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:07:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/11 09:55:55 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

/**
 * Update or get the process status. (Either ON or OFF)
 */
t_bool	ft_process_status(t_philo *philos, char cmd, t_bool n_w)
{
	t_bool	state;

	state = n_w;
	pthread_mutex_lock(&philos->data->process_state);
	if (cmd == 'g')
		state = philos->data->is_processing;
	else if (cmd == 'u')
		philos->data->is_processing = n_w;
	pthread_mutex_unlock(&philos->data->process_state);
	return (state);
}

/**
 * Update or get the time of philos last meal.
 */
long long	ft_last_meal(t_philo *philos, char cmd, long long n_w)
{
	long long	meal;

	meal = n_w;
	pthread_mutex_lock(&philos->last_meal_mutex);
	if (cmd == 'g')
		meal = philos->last_meal;
	else if (cmd == 'u')
		philos->last_meal = n_w;
	pthread_mutex_unlock(&philos->last_meal_mutex);
	return (meal);
}

/**
 * Used to 'g' (get) the meal goal or to 'u' (update) meal_goal.
 * If meal goal is given, meal_goal_total will decrese until it reaches zero.
 */
int	ft_total_meals(t_philo *philos, char cmd, int n_w)
{
	int	meal;

	meal = n_w;
	if (cmd == 'g')
	{
		pthread_mutex_lock(&philos->data->meal_goal_total_mutex);
		meal = philos->data->meal_goal_total;
		pthread_mutex_unlock(&philos->data->meal_goal_total_mutex);
	}
	else if (cmd == 'u')
	{
		pthread_mutex_lock(&philos->data->meal_goal_total_mutex);
		philos->data->meal_goal_total--;
		pthread_mutex_unlock(&philos->data->meal_goal_total_mutex);
	}
	return (meal);
}
