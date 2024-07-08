/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:07:06 by asalo             #+#    #+#             */
/*   Updated: 2024/07/08 17:32:31 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	*monitor(void *data_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) data_ptr;
	pthread_mutex_lock(&philo->data->write);
	printf("data val: %d", philo->data->dead);
	pthread_mutex_unlock(&philo->data->write);
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->done_eating >= philo->data->philo_nb)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void	*mortality(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == FALSE)
			print_status("died", philo);
		if (philo->meals_eaten == philo->data->meal_goal)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->done_eating++;
			philo->meals_eaten++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void	*philo_process(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->time_to_die = philo->data->death_time + get_time();
	if (pthread_create(&philo->thread, NULL, &mortality, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		eat(philo);
		print_status("is thinking", philo);
	}
	if (pthread_join(philo->thread, NULL))/*Why's this here in the first place??*/
		return ((void *)1);
	return (NULL);
}

int	launch_threads(t_data *data)
{
	pthread_t	t0;
	int			i;

	i = -1;
	data->start_time = get_time();
	if (data->meal_goal >= 1)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philos[0]))
			return (error("CREATE_TH", data));
	}
	while (++i < data->philo_nb)
	{
		if (pthread_create(&data->t_id[i], NULL, &philo_process, &data->philos[i]))
			return (error("CREATE_TH", data));
		better_sleep(1);
	}
	i = -1;
	while (++i < data->philo_nb)
	{
		if (pthread_join(data->t_id[i], NULL))
			return (error("JOIN_TH", data));
	}
	return (0);
}



















