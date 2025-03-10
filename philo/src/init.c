#include "../incs/philo.h"

/**
 * @brief	Given string to an int with error handling for invalid
 *			or out-of-range inputs.
*/
static int	ft_atoi(const char *s)
{
	unsigned long long	res;

	res = 0;
	if (!*s)
		return (-1);
	if (*s < '0' || *s > '9')
		return (-1);
	if (*s == '0')
		return (-1);
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			res = res * 10 + *s - '0';
		if (*s < '0' || *s > '9')
			return (-1);
		s++;
	}
	if (res > 1000)
		return (-1);
	return (res);
}

/**
 * @brief	Initializes a philo, allocating memory, setting initial values,
 *			and initializing mutexes.
*/
static t_philo	*init_philo(t_data *data, int i)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (write_error(ALLOC), NULL);
	philo->data = data;
	philo->last_meal = get_time();
	philo->index = i + 1;
	philo->eat_count = 0;
	philo->forks.right = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo->forks.right)
		return (write_error(ALLOC), free(philo), NULL);
	if (pthread_mutex_init(&philo->last_meal_mutex, NULL))
		return (write_error(MTX), free(philo), free(philo->forks.right), NULL);
	if (pthread_mutex_init(philo->forks.right, NULL))
		return (write_error(MTX), free(philo), free(philo->forks.right), NULL);
	return (philo);
}

/**
 * @brief	Creates a circular linked list of philos,
 *			initializing each one and linking their forks.
*/
static t_philo	*create_philos(t_data *data)
{
	t_philo	*philo;
	t_philo	*first;
	t_philo	*prev;
	int		i;

	prev = NULL;
	first = NULL;
	i = 0;
	while (i < data->philo_nb)
	{
		philo = init_philo(data, i);
		if (philo == NULL)
			return (NULL);
		if (i == 0)
			first = philo;
		else
		{
			prev->next = philo;
			philo->forks.left = prev->forks.right;
		}
		prev = philo;
		i++;
	}
	first->forks.left = prev->forks.right;
	return (prev->next = NULL, first);
}

/**
 * @brief	Parse given arguments into a t_data structure,
 *			validate input values and set initial parameters.
*/
static t_data	*get_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (write_error(ALLOC), NULL);
	data->philo_nb = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->meal_goal = ft_atoi(av[5]);
		if (data->meal_goal < 0)
			return (write_error(INPUT), NULL);
	}
	else
		data->meal_goal = -1;
	if (data->philo_nb > 200 || data->philo_nb < 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (write_error(INPUT), free(data), NULL);
	return (data);
}

/**
 * @brief	Orchestrate the init process and
 *			(calling 'get_data()' and 'create_philos()')
 *			set up initial conditions and mutexes.
*/
t_philo	*launcher(int ac, char **av)
{
	t_philo	*philo;
	t_data	*data;

	data = get_data(ac, av);
	if (data == NULL || data->meal_goal == 0)
		return (NULL);
	data->is_processing = TRUE;
	data->meal_goal_total = data->meal_goal * data->philo_nb;
	if ((pthread_mutex_init(&data->process_state, NULL)))
		return (write_error(MTX), NULL);
	if ((pthread_mutex_init(&data->writing, NULL)))
		return (NULL);
	if ((pthread_mutex_init(&data->meal_goal_total_mutex, NULL)))
		return (write_error(MTX), NULL);
	data->start_time = get_time();
	philo = create_philos(data);
	if (philo == NULL)
		return (free(data), NULL);
	return (philo);
}
