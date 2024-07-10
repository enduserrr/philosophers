/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:19:10 by asalo             #+#    #+#             */
/*   Updated: 2024/07/10 19:49:30 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	print_act(t_philo *philos, char *action)
{
	int	state;

	pthread_mutex_lock(&philos->data->writing);
	if (ft_is_processing(philos, 'g', FALSE))
	{
		printf("%lld %d %s\n", get_time() - philos->data->start_time,
			philos->index, action);
		state = 0;
	}
	else
		state = 1;
	pthread_mutex_unlock(&philos->data->writing);
	return (state);
}

int	forks_down(pthread_mutex_t *right, pthread_mutex_t *left)
{
	if (right != NULL)
		pthread_mutex_unlock(left);
	if (right != NULL)
		pthread_mutex_unlock(right);
	return (0);
}

int	forks_up(t_philo *philo)
{
	pthread_mutex_lock(philo->forks.right);
	if (print_act(philo, FORK) == 1)
	{
		pthread_mutex_unlock(philo->forks.right);
		return (1);
	}
	if (philo->data->philo_nb == 1)
	{
		ft_sleep(philo, philo->data->time_to_die, SLEEP);
		pthread_mutex_unlock(philo->forks.right);
		return (1);
	}
	pthread_mutex_lock(philo->forks.left);
	if (print_act(philo, FORK) == 1)
	{
		forks_down(philo->forks.right, philo->forks.left);
		return (1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	ft_last_meal(philo, 'u', get_time());
	if (print_act(philo, EAT) == 1)
	{
		forks_down(philo->forks.right, philo->forks.left);
		return (1);
	}
	if (ft_sleep(philo, philo->data->time_to_eat, SLEEP) == 1)
	{
		forks_down(philo->forks.right, philo->forks.left);
		return (1);
	}
	forks_down(philo->forks.right, philo->forks.left);
	if (philo->data->meal_goal != -1)
	{
		if (philo->eat_count != philo->data->meal_goal)
		{
			philo->eat_count++;
			pthread_mutex_lock(&philo->data->meal_goal_total_mutex);
			philo->data->meal_goal_total--;
			pthread_mutex_unlock(&philo->data->meal_goal_total_mutex);
		}
	}
	if (ft_total_meals(philo, 'g', 0) == 0)
		ft_is_processing(philo, 'u', FALSE);
	return (0);
}
