cmake_minimum_required(VERSION 3.21)
project(philosophers C)

set(CMAKE_C_STANDARD 99)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=thread -O2")

add_executable(philosophers philo/philo.h
        philo/srcs/main.c
        philo/srcs/philo_func.c philo/srcs/ft_atoi.c philo/srcs/ft_strlcpy.c philo/srcs/ft_strlen.c philo/srcs/ft_usleep.c philo/srcs/philo_watcher_func.c philo/srcs/print_philosopher.c philo/srcs/utils.c philo/srcs/philo_get_time.c philo/srcs/philo_action.c philo/srcs/philo_conditions.c philo/srcs/parse.c philo/srcs/utils_2.c)

add_executable(philo_bonus philo_bonus/philo.h
        philo_bonus/srcs/main.c
        philo_bonus/srcs/ft_atoi.c philo_bonus/srcs/ft_strlcpy.c philo_bonus/srcs/ft_strlen.c philo_bonus/srcs/ft_usleep.c
        philo_bonus/srcs/parse.c philo_bonus/srcs/print_philosopher.c philo_bonus/srcs/utils.c
        philo_bonus/srcs/philo_start.c philo_bonus/srcs/philo_func.c philo_bonus/srcs/philo_monitor.c)
