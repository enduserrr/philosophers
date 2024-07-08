/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:10:25 by asalo             #+#    #+#             */
/*   Updated: 2024/07/08 16:53:53 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static int ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && (s1[i] == s2[i]))
		i++;
	return (*(char *)s1 - *(char *)s2);
}

long long	get_time(void)/*change to long long*/
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error("gettimeofday() ERROR\n", NULL));
	return ((tv.tv_sec * (long long)1000) + (tv.tv_usec / 1000));
}

int better_sleep(unsigned int time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	print_status(char *s, t_philo *philo)
{
	unsigned long long	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp("died", s) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philo->id, s);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n",  time, philo->id, s);
	pthread_mutex_unlock(&philo->data->write);
}