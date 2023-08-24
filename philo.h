/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:30:58 by iganiev           #+#    #+#             */
/*   Updated: 2023/08/11 15:30:58 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data
{
    long long       timestamp;
    int             count_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             count_meals;
    int				dead;

    pthread_mutex_t lock;
	pthread_mutex_t *forks;
}                           t_data;

typedef struct s_philo
{
    int				philo_id;
    t_data			*info;
    int				left_fork;
    int				meal_count;
    long long		last_meal_time;
    int				right_fork;
	bool			holding_fork;
	pthread_mutex_t ph_lock;

	pthread_t	thread;
}                           t_philo;


long long	philo_atoi(const char *str);
long long   get_time();
void        ft_usleep(int ms);

#endif