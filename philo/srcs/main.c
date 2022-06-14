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

void	create_philosophers_and_check(t_main *params)
{
	unsigned int	i;

	i = 0;
	params->philosophers = (t_philo *) malloc(sizeof(t_philo) * params->count);
	params->threads = (pthread_t *) malloc(sizeof(pthread_t) * params->count);
	if (!params->philosophers || !params->threads)
	{
		printf("Error: Malloc: cannot allocate memory\n");
		exit(0);
	}
	memset((void *) params->philosophers, 0, sizeof(t_philo) * params->count);
	while (i < params->count)
	{
		pthread_create(params->threads +i, NULL,
					   philo_func, (void *) params->philosophers + i);
		i++;
	}
}

void convert_parameter(int *ptr_num, char *name, char *arg)
{
	*ptr_num = ft_atoi(arg);
	if (*ptr_num <= 0)
	{
		printf("Error: Arguments: %s is cannot be negative\n", name);
		exit(0);
	}
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
	pthread_mutex_init(&(params.out_mutex), NULL);
	convert_parameter(&(params.count), "count", argv[1]);
	convert_parameter(&(params.time_to_die), "time_to_die", argv[2]);
	convert_parameter(&(params.time_to_eat), "time_to_eat", argv[3]);
	convert_parameter(&(params.time_to_sleep), "time_to_sleep", argv[4]);
	if (argc == 6)
		convert_parameter(&(params.philo_must_eat), "philo_must_eat", argv[5]);
	else
		params.philo_must_eat = -1;
	create_philosophers_and_check(&params);
	pthread_mutex_destroy(&(params.out_mutex));
	return (0);
}
