#include "../incs/philo.h"

void	write_error(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(2, "Error: ", 7);
	write(2, s, i);
	write(2, "\n", 1);
}

void	join_and_clean(t_philo *philo)
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
}
