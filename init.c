/* ************************************************************************** */
/*                                                                            */
/*                            :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: YourName <your.email@example.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: YYYY/MM/DD HH:MM:SS by YourName         #+#    #+#             */
/*   Updated: YYYY/MM/DD HH:MM:SS by YourName        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_program(t_program *prog, int argc, char **argv)
{
	prog->ready_flag = 0;
	if (parse_arguments(prog, argc, argv))
		return (1);
	if (allocate_resources(prog))
		return (1);
	if (pthread_mutex_init(&prog->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&prog->dead_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&prog->meal_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&prog->start_lock, NULL) != 0)
		return (1);
	if (init_philosophers(prog))
		return (1);
	return (0);
}

int	parse_arguments(t_program *prog, int argc, char **argv)
{
	prog->num_philos = (int)ft_atoll(argv[1]);
	prog->time_to_die = (size_t)ft_atoll(argv[2]);
	prog->time_to_eat = (size_t)ft_atoll(argv[3]);
	prog->time_to_sleep = (size_t)ft_atoll(argv[4]);
	if (argc == 6)
		prog->num_times_to_eat = (int)ft_atoll(argv[5]);
	else
		prog->num_times_to_eat = -1;
	prog->dead_flag = 0;
	return (0);
}

int	allocate_resources(t_program *prog)
{
	int	i;

	i = 0;
	prog->philos = malloc(sizeof(t_philo) * prog->num_philos);
	if (!prog->philos)
		return (1);
	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->num_philos);
	if (!prog->forks)
		return (1);
	while (i < prog->num_philos)
	{
		if (pthread_mutex_init(&prog->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_philosophers(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_philos)
	{
		if (initialize_philosopher(&prog->philos[i], prog, i) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	initialize_philosopher(t_philo *philo, t_program *prog, int index)
{
	ft_bzero(philo, sizeof(t_philo));
	philo->id = index + 1;
	philo->time_to_die = prog->time_to_die;
	philo->time_to_eat = prog->time_to_eat;
	philo->time_to_sleep = prog->time_to_sleep;
	philo->num_of_philos = prog->num_philos;
	philo->num_times_to_eat = prog->num_times_to_eat;
	philo->dead = &prog->dead_flag;
	philo->write_lock = &prog->write_lock;
	philo->dead_lock = &prog->dead_lock;
	philo->prog = prog;
	philo->fork_left = &prog->forks[index];
	philo->fork_right = &prog->forks[(index + 1) % prog->num_philos];
	philo->ready_flag = &prog->ready_flag;
	philo->start_lock = &prog->start_lock;
	if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
		return (1);
	return (0);
}
