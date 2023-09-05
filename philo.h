/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:30:58 by iganiev           #+#    #+#             */
/*   Updated: 2023/08/30 15:19:57 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	long long		timestamp;
	int				count_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_meals;
	int				dead;

	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philo
{
	int				philo_id;
	t_data			*info;
	int				left_fork;
	int				meal_count;
	long long		last_meal_time;
	int				right_fork;
	int				holding_fork;

	pthread_mutex_t	ph_lock;
	pthread_t		thread;
}					t_philo;

long long			philo_atoi(const char *str);
long long			get_time(void);
void				ft_usleep(int ms);
void				ft_free(t_philo *philo, t_data *info);

int					parse_args(int ac, char *av[]);
void				get_data(t_data *info, int ac, char *av[]);
void				ft_error(t_data *info, char *message);
void				initialize_forks(t_data *info);
void				initialize_philosophers(t_philo **philo, t_data *info);

void				display_routine(t_data *info, int id, char *message);
void				grab_forks(t_philo *philo);
void				release_forks(t_philo *philo);
int					is_eating(t_philo *philo);

int					is_sleeping(t_philo *philo);
int					is_thinking(t_philo *philo);
int					finished_meals(t_data *info, t_philo *philo);
int					is_dead(t_data *info, t_philo *philo);
int					simulation_finished(t_philo *philo, t_data *info);

void				*philosopher(void *arg);
void				run_simulation(t_philo *philo, t_data *info);

#endif