/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 17:50:34 by skoene        #+#    #+#                 */
/*   Updated: 2024/10/31 15:53:18 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->meal_lock);
}

void	increment_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
	usleep(500);
}
