/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 17:50:41 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/01 20:41:27 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (n--)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

void	wait_for_ready_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->start_lock);
	while (!*(philo->ready_flag))
	{
		pthread_mutex_unlock(philo->start_lock);
		usleep(10);
		pthread_mutex_lock(philo->start_lock);
	}
	pthread_mutex_unlock(philo->start_lock);
}

int	join_philosopher_threads(t_program *prog)
{
	int	i;
	int	ret;
	int	success;

	success = 1;
	i = 0;
	while (i < prog->num_philos)
	{
		ret = pthread_join(prog->philos[i].thread, NULL);
		if (ret != 0)
		{
			fprintf(stderr, "Error: Failed to join thread for philosopher %d: ",
				i + 1);
			fprintf(stderr, "%s\n", strerror(ret));
			success = 0;
		}
		i++;
	}
	return (success);
}

int	has_died(t_philo *philo)
{
	size_t	last_meal_time;
	int		died;

	died = 0;
	pthread_mutex_lock(&philo->meal_lock);
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	if ((get_current_time() - last_meal_time) > philo->time_to_die)
		died = 1;
	return (died);
}
