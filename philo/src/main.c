/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:51:21 by asalo             #+#    #+#             */
/*   Updated: 2024/07/08 17:38:44 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static int	one_philo(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->t_id[0], NULL, &philo_process, &data->philos[0]))
		return (error("CREATE_TH", data));
	pthread_detach(data->t_id[0]);
	while (data->dead == 0)
		usleep(0);
	clean_exit(data);
	return (0);
}

static int	allocate(t_data *data)
{
	data->t_id = malloc(sizeof(pthread_t) * data->philo_nb);
	if (!data->t_id)
		return (error(ALLOC_T, data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->forks)
		return (error(ALLOC_F, data));
	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		return (error(ALLOC_P, data));
	return (0);
}

static int invalid_input(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac < 5 || ac > 6)
		return (error("ARG_COUNT", NULL));
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if (av[i][j] < 48 || av[i][j] > 57)
				return (error("INPUT_FORMAT", NULL));
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;/*Allocate for data struct?*/

	if (invalid_input(ac, av))
		return (1);
	if (init_data(ac, av, &data))
		return (1);
	if (allocate(&data))
		return (1);
	if (init_forks(&data))
		return (1);
	init_philos(&data);
	if (data.philo_nb == 1)
		return (one_philo(&data));
	if (launch_threads(&data))
		return (1);
	clean_exit(&data);
	return (0);
}
