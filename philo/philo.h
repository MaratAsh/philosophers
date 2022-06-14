/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/14 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo_fork
{
	pthread_mutex_t	mutex;
	unsigned int	id;
}				t_philo_fork;

typedef struct s_philo
{
	unsigned int	id;
	int				eaten;
	t_philo_fork	*left;
	t_philo_fork	*right;
}				t_philo;

typedef struct s_main
{
	int				count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_must_eat;
	t_philo			*philosophers;
	pthread_t		*threads;
	pthread_mutex_t	out_mutex;
}				t_main;

void	*philo_func(void *params);
int		ft_atoi(const char *str);

#endif
