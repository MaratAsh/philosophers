/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/23 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_long_long_(long long int num)
{
	int	digits;

	digits = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num = num / 10;
		digits++;
	}
	return (digits);
}

long long int	ft_power(int num, int power)
{
	long long int	result;
	int				i;

	result = 1;
	i = 0;
	while (i < power)
	{
		result *= num;
		i++;
	}
	return (result);
}

long long int	milliseconds_from(struct timeval *since, struct timeval *curr)
{
	if (since->tv_sec == curr->tv_sec)
		return ((curr->tv_usec - since->tv_usec) / 1000);
	return ((curr->tv_sec - since->tv_sec) * 1000
		+ (curr->tv_usec - since->tv_usec) / 1000);
}

int	set_long_long_in_string(char *str, long long int num)
{
	int	i;
	int	len;

	if (num < 0)
		return (0);
	len = get_long_long_(num);
	if (num == 0)
	{
		str[0] = '0';
		str[1] = 0;
		return (1);
	}
	i = 0;
	while (i < len)
	{
		str[i] = '0' + (num / ft_power(10, (len - i - 1))) % 10;
		i++;
	}
	str[i] = 0;
	return (len);
}
