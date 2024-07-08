/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:05:45 by asalo             #+#    #+#             */
/*   Updated: 2024/07/08 17:01:49 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static long	ft_atoll(const char *s)/*Meaby change to unsigned or make a check if the nb < 0*/
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	if (!s)
		return (0);
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -sign;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		if (res > 2147483647 || res < -2147483648)
			return (-1);
		res = res * 10 + *s - '0';
		s++; 
	}
	return ((long long)(sign * res));
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	data->philos[0].left_fork = &data->forks[0];
	data->philos[0].right_fork = &data->forks[data->philo_nb - 1];
	i = 1;
	while (i < data->philo_nb)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].meals_eaten = 0;
		data->philos[i].eating = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

int	init_data(int ac, char **av, t_data *data)
{
	data->philo_nb = (int) ft_atoll(av[1]);
	data->death_time = ft_atoll(av[2]);
	data->eat_time = ft_atoll(av[3]);
	data->sleep_time = ft_atoll(av[4]);
	if (ac == 6)
		data->meal_goal = (int) ft_atoll(av[5]);
	else
		data->meal_goal = -1;
	if (data->philo_nb <= 0 || data->philo_nb > 200 || data->death_time <= 0
		|| data->eat_time <= 0 || data->sleep_time <= 0)
		return (error("INPUT_FORMAT", NULL));
	data->dead = 0;
	data->done_eating = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}
