/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/25 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philosophers_init_semaphore(t_main *m, sem_t **ptr, char *name, unsigned int start)
{
	sem_unlink(name);
	*ptr = sem_open(name, IPC_CREAT, 0777, start);
	if (*ptr == SEM_FAILED)
	{
		printf("Error: sem_open: failed to open \"%s\"\n", name);
		philosophers_destroy_semaphores(m);
		exit(0);
	}
}

void	philosophers_init_semaphores(t_main *m)
{
	philosophers_init_semaphore(m, &(m->sem_need_stop), SEMAPHORE_NEED_STOP, 0);
	philosophers_init_semaphore(m, &(m->sem_out), SEMAPHORE_OUT, 1);
	philosophers_init_semaphore(m, &(m->sem_forks), SEMAPHORE_FORKS, m->count);
	philosophers_init_semaphore(m, &(m->sem_edit), SEMAPHORE_EDIT, 1);
	philosophers_init_semaphore(m, &(m->sem_get_forks), SEMAPHORE_GET_FORKS, m->count / 2 + 1);
	philosophers_init_semaphore(m, &(m->sem_enough_eaten), SEMAPHORE_ENOUGH_EATEN, 0);
}

void	philosophers_init(t_main *m)
{
	int		i;
	t_philo	*p;
	size_t	len;

	m->stopped = 0;
	philosophers_init_semaphores(m);
	i = 0;
	while (i < m->count)
	{
		p = m->philosophers + i;
		p->parent = m;
		p->id = i + 1;
		len = ft_strlcpy(p->name_sem_main, "philo_main_p", 13);
		len += set_long_long_in_string(p->name_sem_main + len,
			(long long int) p->id);
		p->name_sem_main[len] = 0;
		philosophers_init_semaphore(m, &(p->sem_main), p->name_sem_main, 1);
		i++;
	}
}
