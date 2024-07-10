/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:10:25 by asalo             #+#    #+#             */
/*   Updated: 2024/07/10 17:31:16 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static void	smart_sleep(unsigned int time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_sleep(t_philo *philo, long long time, char *action)
{
	long long	timer;
	t_bool		status;

	if (print_act(philo, action) == 1)
		return (1);
	status = TRUE;
	timer = get_time();
	while (status)
	{
		if (get_time() - timer >= time)
			break ;
		status = ft_is_processing(philo, 'g', FALSE);
		smart_sleep(50);
	}
	return (0);
}
