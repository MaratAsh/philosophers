/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/14 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	allocate_memory(t_main *m)
{
	m->philosophers = (t_philo *) malloc(sizeof(t_philo) * m->count);
	if (!(m->philosophers))
		return (1);
	m->p_forks = (t_philo_fork *) malloc(sizeof(t_philo_fork) * m->count);
	if (!(m->p_forks))
		return (1);
	m->threads = (pthread_t *) malloc(sizeof(pthread_t) * m->count);
	if (!(m->threads))
		return (1);
	m->threads_monitor = (pthread_t *) malloc(sizeof(pthread_t) * m->count);
	if (!(m->threads_monitor))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_main	params;

	if (argc != 5 && argc != 6)
	{
		printf("Usage:\n%s number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (0);
	}
	memset((void *) &params, 0, sizeof(t_main));
	if (parse(&params, argc - 1, argv))
		return (0);
	if (allocate_memory(&params))
	{
		philosophers_destroy_free_memory(&params);
		write(2, "Error: Malloc: cannot allocate memory\n", 39);
		return (0);
	}
	philosophers_init(&params);
	philosophers_start(&params);
	philosophers_join(&params);
	philosophers_destroy(&params);
	return (0);
}
