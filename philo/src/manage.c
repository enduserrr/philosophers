/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:07:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/12 10:11:53 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

/**
 * @brief	Gets or updates the process status of philos
 *			based on the given cmd.
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
 * @brief	Gets or updates the last meal time of a philo
 *			based on the given cmd.
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
 * @brief	Gets or updates the total meal goal for all philos
 *			based on the given cmd.
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
