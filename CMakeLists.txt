cmake_minimum_required(VERSION 3.21)
project(philosophers C)

set(CMAKE_C_STANDARD 99)

add_executable(philosophers philo/philo.h
        philo/srcs/main.c
        philo/srcs/philo_func.c philo/srcs/ft_atoi.c philo/srcs/ft_strlcpy.c philo/srcs/ft_strlen.c philo/srcs/ft_usleep.c philo/srcs/philo_watcher_func.c)

add_executable(philo_bonus philo_bonus/philo.h
        philo_bonus/srcs/main.c
        )
