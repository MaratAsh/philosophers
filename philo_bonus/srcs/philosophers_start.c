/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/24 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philosophers_start_philo(t_main *m, int i)
{
	pid_t	pid;
	pid = fork();
	if (pid < 0)
	{
		printf("Error: fork\n");
		exit(0);
	}
	if (pid == 0)
	{
		philo_func(m, m->philosophers + i);
		exit(0);
	}
	m->pid_forks[i] = pid;
}

void	philo_print_all_think(t_main *m)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < m->count)
	{
		p = m->philosophers + i;
		print_philosopher(0, p->id, PHILOSOPHER_THINK, m->sem_out);
		i++;
	}
}

int	philosophers_start(t_main *m)
{
	int				i;
	struct timeval	curr_time;
	long long int	l;

	i = 0;
	gettimeofday(&(m->start), NULL);
	philo_print_all_think(m);
	while (i < m->count)
	{
		philosophers_start_philo(m, i);
		i += 2;
	}
	i = 1;
	gettimeofday(&curr_time, NULL);
	l = (curr_time.tv_sec - m->start.tv_sec) * 1000
		+ (curr_time.tv_usec - m->start.tv_usec) / 1000;
	ft_usleep((long long int) m->time_to_eat - l);
	while (i < m->count)
	{
		philosophers_start_philo(m, i);
		i += 2;
	}
	return (0);
}
