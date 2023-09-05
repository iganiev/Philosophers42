/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:38:48 by iganiev           #+#    #+#             */
/*   Updated: 2023/08/30 18:55:59 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		pthread_mutex_lock(&(philo->info->lock));
		if (philo->info->dead)
		{
			pthread_mutex_unlock(&(philo->info->lock));
			break ;
		}
		pthread_mutex_unlock(&(philo->info->lock));
		if (((philo->info->count_meals > 0 \
			&& philo->meal_count >= philo->info->count_meals))
			|| philo->info->count_philo == 1)
			return (NULL);
		is_eating(philo);
		if (philo->info->count_meals > 0
			&& philo->meal_count >= philo->info->count_meals)
			return (NULL);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}

void	run_simulation(t_philo *philo, t_data *info)
{
	int	i;

	i = 0;
	while (i < info->count_philo)
	{
		pthread_create(&(philo[i].thread), NULL, philosopher, &philo[i]);
		i++;
	}
	simulation_finished(philo, info);
	i = 0;
	while (i < info->count_philo)
	{
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&(philo[i].ph_lock));
		i++;
	}
	pthread_mutex_destroy(&(info->lock));
	i = 0;
	while (i < info->count_philo)
	{
		pthread_mutex_destroy(&(info->forks[i]));
		i++;
	}
	ft_free(philo, info);
}