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

int main(int argc, char **argv)
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
	printf("philo start\n");
	philo_start(&params);
	/*
	philosophers_start(&params);
	philosophers_join(&params);
	philosophers_destroy(&params);
	 */
}
