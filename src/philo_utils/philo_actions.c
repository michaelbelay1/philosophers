/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:27:02 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/23 16:03:56 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"
/* 2 cases check:
	1. availability of the fork.
	2. ydegm keyhlu iti specific philo	
*/

int	philo_takes_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	if (philo->data->forks_taken[philo->id - 1] == 0)
		philo->data->forks_taken[philo->id - 1] = 1;
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	if (philo->id == philo->num_of_philo && philo->data->forks_taken[0] == 0)
	{
		philo->data->forks_taken[0] = 1;
	}
	else if (philo->data->forks_taken[philo->id] == 0)
	{
		philo->data->forks_taken[philo->id] = 1;
	}
	else
	{
		philo->data->forks_taken[philo->id - 1] = 0;
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_message("has taken a fork", philo);
	print_message("has taken a fork", philo);
	return (0);
}

void	philo_is_eating(t_philo *philo)
{
	print_message("is eating", philo);
	pthread_mutex_lock(&philo->data->mutex);
	philo->last_eat = get_time() - philo->data->start_time;
	philo->time_to_die = philo->last_eat + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->mutex);
	ft_sleep(philo->data->time_to_eat, philo);
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->num_of_meals != -1)
		philo->data->num_of_meals++;
	pthread_mutex_unlock(&philo->data->mutex);

	philo->data->forks_taken[philo->id - 1] = 0;
	if (philo->id == philo->num_of_philo)
		philo->data->forks_taken[0] = 0;
	else
		philo->data->forks_taken[philo->id] = 0;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_is_sleeping(t_philo *philo)
{
	print_message("is sleeping", philo);
	ft_sleep(philo->data->time_to_sleep, philo);
}

void	philo_is_thinking(t_philo *philo)
{
	print_message("is thinking", philo);
	usleep(50);
}

int	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->philo_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return (1);
	}
	if (!check_last_meal(philo))
	{
		pthread_mutex_lock(&philo->data->mutex_dead);
		printf("%lu %d died\n", get_time()
			- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_dead);
		pthread_mutex_unlock(&philo->data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex);
	return (0);
}
