/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   launch_simulation.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 17:50:48 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/01 20:37:25 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_simulation(t_program *prog)
{
	if (prog->num_philos == 1)
		return (handle_single_philosopher(prog));
	if (initialize_philosophers(prog) != 0)
		return (1);
	pthread_mutex_lock(&prog->start_lock);
	prog->ready_flag = 1;
	pthread_mutex_unlock(&prog->start_lock);
	monitor_philosophers(prog);
	if (join_philosopher_threads(prog) != 1)
	{
		fprintf(stderr, "Error: Failed to join all philosopher threads.\n");
		return (1);
	}
	return (0);
}

int	handle_single_philosopher(t_program *prog)
{
	size_t	start_time;

	start_time = get_current_time();
	prog->philos[0].start_time = start_time;
	prog->philos[0].last_meal = start_time;
	if (pthread_create(&(prog->philos[0].thread), NULL, &philo_routine,
			&(prog->philos[0])) != 0)
	{
		fprintf(stderr, "Error: Failed to create thread for philosopher %d\n",
			1);
		return (1);
	}
	monitor_philosophers(prog);
	if (pthread_join(prog->philos[0].thread, NULL) != 0)
	{
		fprintf(stderr, "Error: Failed to join thread for philosopher %d\n", 1);
		return (1);
	}
	return (0);
}

int	initialize_philosophers(t_program *prog)
{
	int		i;
	size_t	start_time;

	i = 0;
	start_time = get_current_time();
	while (i < prog->num_philos)
	{
		prog->philos[i].start_time = start_time;
		prog->philos[i].last_meal = start_time;
		if (pthread_create(&(prog->philos[i].thread), NULL, &philo_routine,
				&(prog->philos[i])) != 0)
		{
			printf("Error: Failed to create thread for philosopher %d\n", i
				+ 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	monitor_philosophers(t_program *prog)
{
	int	all_done;

	while (1)
	{
		all_done = 1;
		if (check_philosopher_status(prog, &all_done))
			break ;
		if (prog->num_times_to_eat != -1 && all_done)
		{
			pthread_mutex_lock(&prog->dead_lock);
			prog->dead_flag = 1;
			pthread_mutex_unlock(&prog->dead_lock);
			break ;
		}
		usleep(1000);
	}
}

int	check_philosopher_status(t_program *prog, int *all_done)
{
	int		i;
	size_t	timestamp;

	i = -1;
	while (++i < prog->num_philos)
	{
		if (has_died(&prog->philos[i]))
		{
			pthread_mutex_lock(&prog->dead_lock);
			prog->dead_flag = 1;
			pthread_mutex_unlock(&prog->dead_lock);
			pthread_mutex_lock(&prog->write_lock);
			timestamp = get_current_time() - prog->philos[i].start_time;
			printf("%zu\t", timestamp);
			printf("%d\tdied\n", prog->philos[i].id);
			return (pthread_mutex_unlock(&prog->write_lock), 1);
		}
		pthread_mutex_lock(&prog->philos[i].meal_lock);
		if (prog->num_times_to_eat != -1
			&& prog->philos[i].meals_eaten < prog->num_times_to_eat)
			*all_done = 0;
		pthread_mutex_unlock(&prog->philos[i].meal_lock);
	}
	return (0);
}
