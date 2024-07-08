/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:19:10 by asalo             #+#    #+#             */
/*   Updated: 2024/07/08 16:53:44 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status("has taken a fork", philo);
	pthread_mutex_lock(philo->left_fork);
	print_status("has taken a fork", philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_status("is sleeping", philo);
	better_sleep(philo->data->sleep_time);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = TRUE;
	philo->time_to_die = get_time() + philo->data->death_time;
	print_status("is eating", philo);
	philo->meals_eaten++;
	better_sleep(philo->data->eat_time);
	philo->eating = FALSE;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}