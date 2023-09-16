/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_aeting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:32:08 by iganiev           #+#    #+#             */
/*   Updated: 2023/09/15 21:07:21 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_routine(t_data *info, int id, char *message)
{
	long long	current_time;
	int			is_dead;

	current_time = get_time();
	pthread_mutex_lock(&(info->lock));
	is_dead = info->dead;
	if (!is_dead)
	{
		printf("%lld ", (current_time - info->timestamp));
		printf("%d ", id + 1);
		printf("%s\n", message);
	}
	pthread_mutex_unlock(&(info->lock));
}

void	grab_forks(t_philo *philo)
{
	if (philo->info->count_philo % 2 != 0
		&& (philo->philo_id == philo->info->count_philo - 1))
	{
		pthread_mutex_lock(&(philo->info->forks[philo->right_fork]));
		pthread_mutex_lock(&(philo->info->forks[philo->left_fork]));
	}
	else
	{
		pthread_mutex_lock(&(philo->info->forks[philo->left_fork]));
		pthread_mutex_lock(&(philo->info->forks[philo->right_fork]));
	}
}

void	release_forks(t_philo *philo)
{
	if (philo->info->count_philo % 2 != 0
		&& (philo->philo_id == philo->info->count_philo - 1))
	{
		pthread_mutex_unlock(&(philo->info->forks[philo->right_fork]));
		pthread_mutex_unlock(&(philo->info->forks[philo->left_fork]));
	}
	else
	{
		pthread_mutex_unlock(&(philo->info->forks[philo->left_fork]));
		pthread_mutex_unlock(&(philo->info->forks[philo->right_fork]));
	}
	ft_usleep(philo->info->time_to_eat);
}

int	is_eating(t_philo *philo)
{
	if (philo->info->count_philo != 1)
	{
		grab_forks(philo);
		display_routine(philo->info, philo->philo_id, "has taken a fork");
		display_routine(philo->info, philo->philo_id, "has taken a fork");
		display_routine(philo->info, philo->philo_id, "is eating");
		pthread_mutex_lock(&(philo->ph_lock));
		philo->last_meal_time = get_time();
		philo->meal_count = philo->meal_count + 1;
		pthread_mutex_unlock(&(philo->ph_lock));
		ft_usleep(philo->info->time_to_eat);
		release_forks(philo);
	}
	return (0);
}
