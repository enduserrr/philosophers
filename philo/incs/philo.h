/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:47:10 by asalo             #+#    #+#             */
/*   Updated: 2024/07/08 17:46:55 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

/* ************** */
/* Error messages */
/* ************** */
# define ALLOC_T "Failed allocating memory for threads"
# define ALLOC_P "Failed allocating memory for philosophers"
# define ALLOC_F "Failed allocating memory for forks"
# define ARG_COUNT "Incorrect argument count."
# define INPUT_FORMAT "Incorrect inut(s)."
# define CREATE_TH "Failed creating thread(s)."
# define JOIN_TH "Failed joining thread(s)."
# define INIT_FORKS "Failed initializing forks."
# define GET_TIME "UNABLE TO RETRIEVE TIME"


typedef	enum {
	FALSE,
	TRUE
} e_bool;

struct	s_data;

typedef struct		s_philo
{
	struct s_data	*data;/*should this be freed?*/
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	int				status;
	e_bool			eating;/*leaking??*/
	long long		time_to_die;
	pthread_mutex_t	lock;/*destroy*/
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}					t_philo;

typedef struct		s_data
{
	pthread_t		*t_id;/*free*/
	int				philo_nb;
	int				meal_goal;
	int				dead;
	int				done_eating;
	t_philo			*philos;/*free*/
	long long		death_time;
	long long		eat_time;
	long long		sleep_time;
	long long		start_time;
	pthread_mutex_t	*forks;/*destroy & free*/
	pthread_mutex_t	lock;/*destroy*/
	pthread_mutex_t	write;/*destroy*/
}					t_data;


/* ********* */
/* Functions */
/* ********* */
void		clean_exit(t_data *data);
void		clear_data(t_data *data);
int			error(char *s, t_data *data);

long long	get_time(void);
int			better_sleep(unsigned int time);

int			init_forks(t_data *data);
void		init_philos(t_data *data);
int			init_data(int ac, char **av, t_data *data);

void		print_status(char *s, t_philo *philo);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		eat(t_philo *philo);

void		*monitor(void *data_ptr);
void		*mortality(void *philo_ptr);
void		*philo_process(void *philo_ptr);
int			launch_threads(t_data *data);

#endif
