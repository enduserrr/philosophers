/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:14:52 by asalo             #+#    #+#             */
/*   Updated: 2024/07/10 14:04:58 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	write_error(char *s)
{
	int i;

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
		pthread_join(tmp->t_id, NULL);
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

