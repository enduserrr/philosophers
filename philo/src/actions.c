#include "../incs/philo.h"

/**
 * @brief	Unlocks the right and left forks (mutexes)
 *			to signal that the philo has put down the forks.
*/
int	forks_down(pthread_mutex_t *right, pthread_mutex_t *left)
{
	if (right != NULL)
		pthread_mutex_unlock(left);
	if (right != NULL)
		pthread_mutex_unlock(right);
	return (0);
}

/**
 * @brief	Locks the right fork, checks action status,
 *			handles single philosopher scenario,
 *			locks the left fork, and checks action status again.
*/
int	forks_up(t_philo *philo)
{
	pthread_mutex_lock(philo->forks.right);
	if (put_action(philo, FORK) == 1)
	{
		pthread_mutex_unlock(philo->forks.right);
		return (1);
	}
	if (philo->data->philo_nb == 1)
	{
		ft_sleep(philo, philo->data->time_to_die, SLEEP);
		pthread_mutex_unlock(philo->forks.right);
		return (1);
	}
	pthread_mutex_lock(philo->forks.left);
	if (put_action(philo, FORK) == 1)
	{
		forks_down(philo->forks.right, philo->forks.left);
		return (1);
	}
	return (0);
}

/**
 * @brief	Updates the last meal time, performs eating act,
 *			sleeps for eating duration,
 *			and updates meal goal counters if applicable.
*/
int	eat(t_philo *philo)
{
	ft_last_meal(philo, 'u', get_time());
	if (put_action(philo, EAT) == 1)
	{
		forks_down(philo->forks.right, philo->forks.left);
		return (1);
	}
	if (ft_sleep(philo, philo->data->time_to_eat, SLEEP) == 1)
	{
		forks_down(philo->forks.right, philo->forks.left);
		return (1);
	}
	forks_down(philo->forks.right, philo->forks.left);
	if (philo->data->meal_goal != -1)
	{
		if (philo->eat_count != philo->data->meal_goal)
		{
			philo->eat_count++;
			pthread_mutex_lock(&philo->data->meal_goal_total_mutex);
			philo->data->meal_goal_total--;
			pthread_mutex_unlock(&philo->data->meal_goal_total_mutex);
		}
	}
	if (ft_total_meals(philo, 'g', 0) == 0)
		ft_process_status(philo, 'u', FALSE);
	return (0);
}
