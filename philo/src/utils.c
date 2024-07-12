/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:10:25 by asalo             #+#    #+#             */
/*   Updated: 2024/07/12 10:14:34 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static void	smart_sleep(unsigned int time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 1000000);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/**
 * @brief	Prints the action of the philosopher if the process running,
 *			else returns an error state (1).
*/
int	put_action(t_philo *philos, char *action)
{
	int	state;

	pthread_mutex_lock(&philos->data->writing);
	if (ft_process_status(philos, 'g', FALSE))
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

/**
 * @brief	Puts a philo to sleep for a specified duration
 *			and checks the process status periodically
 *			and perform the sleep action.
*/
int	ft_sleep(t_philo *philo, long long time, char *action)
{
	long long	timer;
	t_bool		status;

	if (put_action(philo, action) == 1)
		return (1);
	status = TRUE;
	timer = get_time();
	while (status)
	{
		if (get_time() - timer >= time)
			break ;
		status = ft_process_status(philo, 'g', FALSE);
		smart_sleep(50);
	}
	return (0);
}
