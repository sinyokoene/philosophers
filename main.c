/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 17:50:27 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/01 20:41:02 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isspace23(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (ft_isspace23(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result < 0 && sign == 1)
			return (LLONG_MAX);
		else if (result < 0 && sign == -1)
			return (LLONG_MIN);
		str++;
	}
	return (sign * result);
}

int	validate_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("\033[1;31mError: invalid number of arguments\033[0m\n");
		return (0);
	}
	while (i < argc)
	{
		if (!is_positive_integer(argv[i]))
		{
			printf("\033[1;31mError: All arguments must be positive integers. \
			\033[0m\n");
			return (0);
		}
		if (ft_atoll(argv[i]) > INT_MAX)
			return (printf("\033[1;31mError: Integer overflow.\033[0m\n"), 0);
		i++;
	}
	return (1);
}

void	cleanup(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_philos)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		pthread_mutex_destroy(&prog->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&prog->write_lock);
	pthread_mutex_destroy(&prog->dead_lock);
	pthread_mutex_destroy(&prog->meal_lock);
	pthread_mutex_destroy(&prog->start_lock);
	if (prog->philos)
		free(prog->philos);
	if (prog->forks)
		free(prog->forks);
}

int	main(int argc, char **argv)
{
	t_program	prog;

	if (!validate_input(argc, argv))
		return (1);
	if (init_program(&prog, argc, argv) != 0)
		return (cleanup(&prog), 1);
	if (start_simulation(&prog) != 0)
		return (cleanup(&prog), 1);
	cleanup(&prog);
	return (0);
}
