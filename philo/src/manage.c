/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:07:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/10 16:50:35 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

e_bool	ft_is_processing(t_philo *philos, char method, e_bool new_value)
{
	e_bool	status;

	status = new_value;
	pthread_mutex_lock(&philos->data->status_mutex);
	if (method == 'g')
		status = philos->data->is_processing;
	else if (method == 's')
		philos->data->is_processing = new_value;
	pthread_mutex_unlock(&philos->data->status_mutex);
	return (status);
}

long long	ft_last_meal(t_philo *philos, char method, long long new_value)
{
	long long	meal;

	meal = new_value;
	pthread_mutex_lock(&philos->last_meal_mutex);
	if (method == 'g')
		meal = philos->last_meal;
	else if (method == 's')
		philos->last_meal = new_value;
	pthread_mutex_unlock(&philos->last_meal_mutex);
	return (meal);
}

int	ft_total_meals(t_philo *philos, char method, int new_value)
{
	int	meal;

	meal = new_value;
	if (method == 'g')
	{
		pthread_mutex_lock(&philos->data->meal_goal_total_mutex);
		meal = philos->data->meal_goal_total;
		pthread_mutex_unlock(&philos->data->meal_goal_total_mutex);
	}
	else if (method == 's')
	{
		pthread_mutex_lock(&philos->data->meal_goal_total_mutex);
		philos->data->meal_goal_total-- ;
		pthread_mutex_unlock(&philos->data->meal_goal_total_mutex);
	}
	return (meal);
}



















