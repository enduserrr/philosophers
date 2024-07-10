/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:07:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/10 17:39:27 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

t_bool	ft_is_processing(t_philo *philos, char method, t_bool n_w)
{
	t_bool	status;

	status = n_w;
	pthread_mutex_lock(&philos->data->process_state);
	if (method == 'g')
		status = philos->data->is_processing;
	else if (method == 's')
		philos->data->is_processing = n_w;
	pthread_mutex_unlock(&philos->data->process_state);
	return (status);
}

long long	ft_last_meal(t_philo *philos, char method, long long n_w)
{
	long long	meal;

	meal = n_w;
	pthread_mutex_lock(&philos->last_meal_mutex);
	if (method == 'g')
		meal = philos->last_meal;
	else if (method == 's')
		philos->last_meal = n_w;
	pthread_mutex_unlock(&philos->last_meal_mutex);
	return (meal);
}

int	ft_total_meals(t_philo *philos, char method, int n_w)
{
	int	meal;

	meal = n_w;
	if (method == 'g')
	{
		pthread_mutex_lock(&philos->data->meal_goal_total_mutex);
		meal = philos->data->meal_goal_total;
		pthread_mutex_unlock(&philos->data->meal_goal_total_mutex);
	}
	else if (method == 's')
	{
		pthread_mutex_lock(&philos->data->meal_goal_total_mutex);
		philos->data->meal_goal_total--;
		pthread_mutex_unlock(&philos->data->meal_goal_total_mutex);
	}
	return (meal);
}
