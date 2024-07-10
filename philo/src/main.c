/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:51:21 by asalo             #+#    #+#             */
/*   Updated: 2024/07/10 18:08:11 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static int	sleep_check(t_philo *philo)
{
	return (ft_sleep(philo, philo->data->time_to_sleep, SLEEP));
}

static void	philo_checker(t_philo *philo, t_philo *first)
{
	t_bool	is_processing;

	is_processing = TRUE;
	usleep(4000);
	while (is_processing)
	{
		if (get_time() - ft_last_meal(philo, 'g', 0) > philo->data->time_to_die)
		{
			ft_is_processing(philo, 's', FALSE);
			pthread_mutex_lock(&philo->data->writing);
			printf("%lld %d %s\n", get_time() - philo->data->start_time,
				philo->index, DIE);
			pthread_mutex_unlock(&philo->data->writing);
		}
		philo = philo->next;
		if (philo == NULL)
			philo = first;
		is_processing = ft_is_processing(philo, 'g', FALSE);
	}
}

static void	*routine(void *philo)
{
	if (((t_philo *)philo)->index % 2 == 0)
		sleep_check((t_philo *)philo);
	while (1)
	{
		if (print_act((t_philo *)philo, THINK) == 1)
			break ;
		if (forks_up((t_philo *)philo) == 1)
			break ;
		if (eat((t_philo *)philo) == 1)
			break ;
		if (sleep_check((t_philo *)philo) == 1)
			break ;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_philo	*tmp;

	if (ac != 5 && ac != 6)
		return (write_error(ARGC), 1);
	philo = launcher(ac, av);
	if (philo == NULL)
		return (1);
	tmp = philo;
	tmp->data->start_time = get_time();
	while (tmp)
	{
		if ((pthread_create(&tmp->t_id, NULL, &routine, tmp)))
			break ;
		tmp = tmp->next;
	}
	tmp = philo;
	philo_checker(tmp, philo);
	join_and_clean(philo);
	return (0);
}
