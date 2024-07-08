/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:14:52 by asalo             #+#    #+#             */
/*   Updated: 2024/07/08 17:50:53 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static void	write_error(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	write(2, "Error: ", 7);
	write(2, s, i);
	write(2, "\n", 1);
}

void	clean_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	clear_data(data);
}

void	clear_data(t_data *data)
{
	if (data->t_id)
		free(data->t_id);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

int	error(char *s, t_data *data)
{
	write_error(s);
	if (data)
		clean_exit(data);
	return (1);
}