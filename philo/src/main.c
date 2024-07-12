/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:51:21 by asalo             #+#    #+#             */
/*   Updated: 2024/07/12 09:55:32 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

/**
 * @brief	Puts a philosopher to sleep for the specified time.
*/
static int	sleep_frame(t_philo *philo)
{
	return (ft_sleep(philo, philo->data->time_to_sleep, SLEEP));
}

/**
 * @brief	Monitors each philo to check if they are alive by comparing
 *			the time from their last meal to the time_to_die. 
 *			Sleeps for 4 ms initially to ensure processes are ready.
 *			Prints a message if a philo dies.
*/
static void	monitoring(t_philo *philo, t_philo *first)
{
	t_bool	is_processing;

	is_processing = TRUE;
	usleep(4000);
	while (is_processing)
	{
		if (get_time() - ft_last_meal(philo, 'g', 0) > philo->data->time_to_die)
		{
			ft_process_status(philo, 'u', FALSE);
			pthread_mutex_lock(&philo->data->writing);
			printf("%lld %d %s\n", get_time() - philo->data->start_time,
				philo->index, DIE);
			pthread_mutex_unlock(&philo->data->writing);
		}
		philo = philo->next;
		if (philo == NULL)
			philo = first;
		is_processing = ft_process_status(philo, 'g', FALSE);
	}
}

/**
 * @brief	The routine for each philo thread. Even-indexed philos sleep first.
 *			The loop continues with the philo thinking, picking up forks,
 *			eating, and sleeping, breaking if any action fails.
*/
static void	*philo_routine(void *philo)
{
	if (((t_philo *)philo)->index % 2 == 0)
		sleep_frame((t_philo *)philo);
	while (1)
	{
		if (put_action((t_philo *)philo, THINK) == 1)
			break ;
		if (forks_up((t_philo *)philo) == 1)
			break ;
		if (eat((t_philo *)philo) == 1)
			break ;
		if (sleep_frame((t_philo *)philo) == 1)
			break ;
	}
	return (NULL);
}

/**
 * @brief	Handles cleanup and error reporting if thread creation fails.
 *			Joins all threads and frees allocated memory.
*/
static void	create_fail_exit(t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*prev;

	tmp = philo;
	while (tmp)
	{
		if (pthread_join(tmp->t_id, NULL) != 0)
			write_error(TH_JOIN);
		tmp = tmp->next;
	}
	free(philo->data);
	tmp = philo;
	while (tmp)
	{
		prev = tmp;
		free(prev->forks.right);
		tmp = tmp->next;
		free(prev);
	}
	return (write_error(TH_CREATE));
}

/**
 * @brief	Entry point of the program. Check arg count,
 *			call for launcher() to initiate structs, threads
 *			and mutexes. Cleans up before exitting.
*/
int	main(int ac, char **av)
{
	t_philo			*philo;
	t_philo			*tmp;

	if (ac != 5 && ac != 6)
		return (write_error(ARGC), 1);
	philo = launcher(ac, av);
	if (philo == NULL)
		return (1);
	tmp = philo;
	tmp->data->start_time = get_time();
	while (tmp)
	{
		if ((pthread_create(&tmp->t_id, NULL, &philo_routine, tmp)))
			return (create_fail_exit(philo), 1);
		tmp = tmp->next;
	}
	tmp = philo;
	monitoring(tmp, philo);
	join_and_clean(philo);
	return (0);
}
