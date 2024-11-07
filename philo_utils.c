/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 17:50:58 by skoene        #+#    #+#                 */
/*   Updated: 2024/10/31 15:39:55 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (check_simulation_end(philo))
			break ;
		usleep(500);
	}
}

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_status(t_philo *philo, char *status)
{
	size_t	timestamp;

	pthread_mutex_lock(philo->dead_lock);
	if (!*(philo->dead))
	{
		pthread_mutex_lock(philo->write_lock);
		timestamp = get_current_time() - philo->start_time;
		printf("%zu\t%d\t%s\n", timestamp, philo->id, status);
		pthread_mutex_unlock(philo->write_lock);
	}
	pthread_mutex_unlock(philo->dead_lock);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_positive_integer(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (ft_atoll(str) > 0);
}
