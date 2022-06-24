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
	void	(*func)(t_main *, t_philo *);

	if (i + 1 == m->count)
		func = philo_last_func;
	else
		func = philo_func;
	pid = fork();
	if (pid < 0)
	{
		printf("Error: fork\n");
		exit(0);
	}
	if (i == 0)
	{
		func(m, m->philosophers + i);
		exit(0);
	}
	m->philosophers[i].id = pid;
}

void	philo_print_all_think(t_main *m)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < m->count)
	{
		p = m->philosophers + i;
		print_philosopher(0, p->id, PHILOSOPHER_THINK, &(p->parent->out));
		i++;
	}
}

int	philo_start(t_main *m)
{
	int				i;
	struct timeval	curr_time;
	long long int	l;

	i = 0;
	gettimeofday(&(m->start), NULL);
	philo_print_all_think(m);
	while (i < m->count)
	{
		//philosophers_start_philo(params, i);
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
