/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/26 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philosophers_destroy_free_memory(t_main *m)
{
	if (m->philosophers)
		free(m->philosophers);
	if (m->p_forks)
		free(m->p_forks);
	if (m->threads)
		free(m->threads);
	if (m->threads_monitor)
		free(m->threads_monitor);
	return (0);
}

int	philosophers_destroy(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->count)
	{
		pthread_mutex_destroy(&(m->philosophers[i].mutex));
		pthread_mutex_destroy(&(m->p_forks[i].mutex));
		i++;
	}
	philosophers_destroy_free_memory(m);
	pthread_mutex_destroy(&(m->out_mutex));
	pthread_mutex_destroy(&(m->main_mutex));
	return (0);
}
