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

int	convert_parameter(int *ptr_num, char *name, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			printf("Error: Arguments: %s should be a positive number\n", name);
			return (1);
		}
		i++;
	}
	*ptr_num = ft_atoi(arg);
	if (*ptr_num <= 0)
	{
		printf("Error: Arguments: %s is cannot be negative\n", name);
		return (1);
	}
	return (0);
}

int	parse(t_main *params, int count, char **argv)
{
	if (convert_parameter(&(params->count), "count", argv[1]))
		return (1);
	if (convert_parameter(&(params->time_to_die), "time_to_die", argv[2]))
		return (1);
	if (convert_parameter(&(params->time_to_eat), "time_to_eat", argv[3]))
		return (1);
	if (convert_parameter(&(params->time_to_sleep), "time_to_sleep", argv[4]))
		return (1);
	if (count == 5)
	{
		if (convert_parameter(&(params->philo_must_eat),
				"philo_must_eat", argv[5]))
			return (1);
	}
	else
		params->philo_must_eat = -1;
	return (0);
}
