/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_act.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:19:10 by asalo             #+#    #+#             */
/*   Updated: 2024/07/10 13:42:35 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	print_act(t_philo *philos, char *action)
{
	int	status;

	pthread_mutex_lock(&philos->data->writing);
	if (ft_is_processing(philos, 'g', FALSE))
	{/*gets the philo nb and action from philo list*/
		printf("%lld %d %s\n", get_time() - philos->data->start_time, \
				philos->index, action);
		status = 0;
	}
	else
		status = 1;
	pthread_mutex_unlock(&philos->data->writing);
	return (status);
}

int	put_forks_down(pthread_mutex_t *right, pthread_mutex_t *left)
{
	if (right != NULL)
		pthread_mutex_unlock(left);
	if (right != NULL)
		pthread_mutex_unlock(right);
	return (0);
}

int	pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->forks.right);
	if (print_act(philo, "has taken a fork") == 1)
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
	if (print_act(philo, "has taken a fork") == 1)
	{
		put_forks_down(philo->forks.right, philo->forks.left);
		return (1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	ft_last_meal(philo, 's', get_time());
	if (print_act(philo, EAT) == 1)
	{
		put_forks_down(philo->forks.right, philo->forks.left);
		return (1);
	}
	if (ft_sleep(philo, philo->data->time_to_eat, SLEEP) == 1)
	{
		put_forks_down(philo->forks.right, philo->forks.left);
		return (1);
	}
	put_forks_down(philo->forks.right, philo->forks.left);
	if (philo->data->meal_goal != -1)
	{
		if (philo->eating_nbr != philo->data->meal_goal)
		{
			philo->eating_nbr++;
			pthread_mutex_lock(&philo->data->meal_goal_total_mutex);
			philo->data->meal_goal_total--;
			pthread_mutex_unlock(&philo->data->meal_goal_total_mutex);
		}
	}
	if (ft_total_meals(philo, 'g', 0) == 0)
		ft_is_processing(philo, 's', FALSE);
	return (0);
}