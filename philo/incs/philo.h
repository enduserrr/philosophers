/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:47:10 by asalo             #+#    #+#             */
/*   Updated: 2024/07/10 17:06:52 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

/* ******* */
/* Actions */
/********* */
# define EAT "is eating"
# define DIE "died"
# define THINK "is thinking"
# define SLEEP "is sleeping"

/* ******* */
/* Structs */
/* ******* */
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_data
{
	int		philo_nb;
	long long	start_time;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meal_goal;
	int		meal_goal_total;
	e_bool		is_processing;
	pthread_mutex_t	writing;
	pthread_mutex_t	meal_goal_total_mutex;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	timer_mutex;
}	t_data;

typedef struct s_forks
{
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
}	t_forks;

typedef struct s_philo
{
	pthread_t	t_id;
	t_forks		forks;
	t_data		*data;
	int		index;
	int		eating_nbr;
	long long	last_meal;
	void		*next;
	pthread_mutex_t	last_meal_mutex;
}	t_philo;

/* ********* */
/* Functions */
/* ********* */
void		write_error(char *s);
t_philo		*launcher(int ac, char **av);
long long	get_time(void);
/*void				philos_lister(t_philo *philo, t_philo *head);*/
void		join_and_clean(t_philo *philo);
int		ft_sleep(t_philo *philo, long long time, char *action);
/*int					sleeping(long long time, t_philo *philos);*/
int		print_act(t_philo *philos, char *action);
int		put_forks_down(pthread_mutex_t *right, pthread_mutex_t *left);
int		pickup_forks(t_philo *philo);
int		eat(t_philo *philo);
/*int					_sleep(t_philo *philo);*/
e_bool		ft_is_processing(t_philo *philos, char method, e_bool new_value);
long long	ft_last_meal(t_philo *philos, char method, long long new_value);
int		ft_total_meals(t_philo *philos, char method, int new_value);
/*int					better_sleep(t_philo *philo);*/

#endif
