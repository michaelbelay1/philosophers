/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:27:02 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/14 22:39:44 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	philo_takes_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork[philo->id]);
	if (!philo_is_dead(philo))
		print_message("has taken a fork", philo);
	pthread_mutex_lock(&philo->right_fork[philo->id + 1]);
	if (!philo_is_dead(philo))
		print_message("has taken a fork", philo);
	if (pthread_mutex_lock(&philo->right_fork[philo->id + 1]) != 0)
		return (pthread_mutex_unlock(&philo->left_fork[philo->id]), 1);
	if (pthread_mutex_lock(&philo->left_fork[philo->id]) != 0)
		return (pthread_mutex_unlock(&philo->right_fork[philo->id + 1]), 1);
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
	if (philo->num_of_meals != -1)
		philo->num_of_meals++;
	pthread_mutex_unlock(&philo->data->mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_is_sleeping(t_philo *philo)
{
	print_message("is sleeping", philo);
	ft_sleep(philo->data->time_to_sleep, philo);
}

void	philo_is_thinking(t_philo *philo)
{
	print_message("is thinking", philo);
}

int	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->philo_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex);
	return (0);
}
