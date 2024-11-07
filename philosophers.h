/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/26 15:58:38 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/01 20:49:09 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <ctype.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// Structure for philosopher data
typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	size_t				last_meal;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				time_to_think;
	size_t				start_time;
	int					num_of_philos;
	int					num_times_to_eat;
	int					*dead;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		*start_lock;
	int					*ready_flag;
	struct s_program	*prog;
	pthread_t			thread;
}						t_philo;

// Structure for program-wide data
typedef struct s_program
{
	int					num_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					num_times_to_eat;
	int					dead_flag;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		start_lock;
	int					ready_flag;
	t_philo				*philos;
}						t_program;

// Function declarations
int						init_program(t_program *prog, int argc, char **argv);
int						init_philosophers(t_program *prog);
int						start_simulation(t_program *prog);
void					*philo_routine(void *arg);
void					philo_eat(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					philo_think(t_philo *philo);
void					print_status(t_philo *philo, char *status);
void					ft_usleep(size_t milliseconds, t_philo *philo);
size_t					get_current_time(void);
int						has_died(t_philo *philo);
int						validate_input(int argc, char **argv);
int						is_positive_integer(char *str);
void					cleanup(t_program *prog);
int						start_simulation(t_program *prog);
int						handle_single_philosopher(t_program *prog);
int						initialize_philosophers(t_program *prog);
void					monitor_philosophers(t_program *prog);
int						check_philosopher_status(t_program *prog,
							int *all_done);
int						join_philosopher_threads(t_program *prog);
void					ft_bzero(void *s, size_t n);
int						has_died(t_philo *philo);
void					put_down_forks(t_philo *philo);
void					increment_meals_eaten(t_philo *philo);
void					update_last_meal_time(t_philo *philo);
void					pick_up_forks(t_philo *philo);
int						has_eaten_enough(t_philo *philo);
int						check_simulation_end(t_philo *philo);
int						ft_isdigit(int c);
int						initialize_philosopher(t_philo *philo, t_program *prog,
							int index);
int						init_philosophers(t_program *prog);
int						allocate_resources(t_program *prog);
int						parse_arguments(t_program *prog, int argc, char **argv);
long long				ft_atoll(const char *str);
void					wait_for_ready_flag(t_philo *philo);

#endif
