/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/25 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philosophers_destroy_semaphores(t_main *m)
{
	int	i;

	sem_close(m->sem_need_stop);
	sem_close(m->sem_out);
	sem_close(m->sem_forks);
	sem_close(m->sem_get_forks);
	sem_close(m->sem_edit);
	sem_close(m->sem_enough_eaten);
	sem_unlink(SEMAPHORE_NEED_STOP);
	sem_unlink(SEMAPHORE_OUT);
	sem_unlink(SEMAPHORE_FORKS);
	sem_unlink(SEMAPHORE_GET_FORKS);
	sem_unlink(SEMAPHORE_EDIT);
	sem_unlink(SEMAPHORE_ENOUGH_EATEN);
	i = 0;
	while (i < m->count)
	{
		sem_close(m->philosophers[i].sem_main);
		sem_unlink(m->philosophers[i].name_sem_main);
		i++;
	}
}

void	philosophers_destroy(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->count)
	{
		kill(m->pid_forks[i], SIGINT);
		i++;
	}
	philosophers_destroy_semaphores(m);
	free(m->philosophers);
	free(m->pid_forks);
}
