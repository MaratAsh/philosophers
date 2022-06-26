/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/24 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	allocate_memory(t_main *m)
{
	m->philosophers = (t_philo *) malloc(sizeof(t_philo) * m->count);
	m->pid_forks = (pid_t *) malloc(sizeof(pid_t) * m->count);
}

int	main(int argc, char **argv)
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
	allocate_memory(&params);
	philosophers_init(&params);
	philosophers_start(&params);
	philo_monitor(&params);
	philosophers_destroy(&params);
}
