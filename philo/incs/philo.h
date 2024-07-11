/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:47:10 by asalo             #+#    #+#             */
/*   Updated: 2024/07/11 11:10:37 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* Errors msg */
# define ARGC "Incorrect argument count."
# define INPUT "Invalid input."
# define MTX "Mutex init fail."
# define TH_CREATE
# define TH_JOIN
# define ALLOC "Memory allocation fail."

/* Action msg */
# define FORK "has taken a fork"
# define EAT "is eating"
# define DIE "died"
# define THINK "is thinking"
# define SLEEP "is sleeping"

/* Structs */
typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef struct s_data
{
	int				philo_nb;
	long long		start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_goal;
	int				meal_goal_total;
	t_bool			is_processing;
	pthread_mutex_t	writing;
	pthread_mutex_t	meal_goal_total_mutex;
	pthread_mutex_t	process_state;
}					t_data;

typedef struct s_forks
{
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
}					t_forks;

typedef struct s_philo
{
	pthread_t		t_id;
	t_forks			forks;
	t_data			*data;
	int				index;
	int				eat_count;
	long long		last_meal;
	void			*next;
	pthread_mutex_t	last_meal_mutex;
}					t_philo;

/* Utils */
long long			get_time(void);
int					put_action(t_philo *philos, char *action);
int					ft_sleep(t_philo *philo, long long time, char *action);

/*Exit and cleaning*/
void				write_error(char *s);
void				join_and_clean(t_philo *philo);

/* Actions */
int					forks_down(pthread_mutex_t *right, pthread_mutex_t *left);
int					forks_up(t_philo *philo);
int					eat(t_philo *philo);
t_philo				*launcher(int ac, char **av);

/* Management */
t_bool				ft_process_status(t_philo *philos, char cmd, t_bool n_w);
long long			ft_last_meal(t_philo *philos, char cmd, long long n_w);
int					ft_total_meals(t_philo *philos, char cmd, int n_w);

#endif
