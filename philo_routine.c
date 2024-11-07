/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 17:50:00 by skoene        #+#    #+#                 */
/*   Updated: 2024/10/31 16:21:16 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num_of_philos == 1)
		return (NULL);
	wait_for_ready_flag(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 2, philo);
	while (1)
	{
		if (check_simulation_end(philo))
			break ;
		philo_eat(philo);
		if (check_simulation_end(philo))
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	check_simulation_end(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(philo->dead_lock);
	is_dead = *(philo->dead);
	pthread_mutex_unlock(philo->dead_lock);
	return (is_dead);
}

int	has_eaten_enough(t_philo *philo)
{
	int	result;

	result = 0;
	if (philo->num_times_to_eat != -1)
	{
		pthread_mutex_lock(&philo->meal_lock);
		if (philo->meals_eaten >= philo->num_times_to_eat)
			result = 1;
		pthread_mutex_unlock(&philo->meal_lock);
	}
	return (result);
}

void	philo_eat(t_philo *philo)
{
	pick_up_forks(philo);
	update_last_meal_time(philo);
	print_status(philo, "is eating");
	ft_usleep(philo->time_to_eat, philo);
	increment_meals_eaten(philo);
	put_down_forks(philo);
}

void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_left);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		print_status(philo, "has taken a fork");
	}
}
