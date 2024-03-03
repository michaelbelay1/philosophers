/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:27:02 by mhaile            #+#    #+#             */
/*   Updated: 2024/03/03 10:08:20 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	pick_up_forks(t_philo *philo)
{
	if (philo->data->forks_taken[philo->id - 1]
		&& philo->data->forks_taken[philo->id - 1] != philo->id)
		philo->data->forks_taken[philo->id - 1] = 0;
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	if (philo->id == philo->num_of_philo && (philo->data->forks_taken[0]
			&& philo->data->forks_taken[0] != philo->id))
		philo->data->forks_taken[0] = 0;
	else if (philo->id != philo->num_of_philo
		&& philo->data->forks_taken[philo->id]
		&& (philo->data->forks_taken[philo->id] != philo->id))
		philo->data->forks_taken[philo->id] = 0;
	else
	{
		philo->data->forks_taken[philo->id - 1] = -1;
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_unlock(philo->right_fork);
	return (pthread_mutex_unlock(philo->left_fork), 0);
}

int	philo_takes_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	if (pick_up_forks(philo))
		return (1);
	print_message("\033[1;36mhas taken a fork\033[0m", philo);
	print_message("\033[1;36mhas taken a fork\033[0m", philo);
	return (0);
}

int	philo_is_eating(t_philo *philo)
{
	print_message("\033[1;32m\033[0m\033[1;32mis eating\033[0m", philo);
	pthread_mutex_lock(&philo->data->mutex_dead);
	philo->last_eat = get_time() - philo->data->start_time;
	philo->time_to_die = philo->last_eat + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->mutex_dead);
	if (is_philo_dead(philo->data))
		return (drop_forks(philo), 0);
	if (!ft_sleep(philo->data->time_to_eat, philo))
		return (drop_forks(philo), 0);
	pthread_mutex_lock(&philo->data->mutex_meals);
	if (philo->data->num_of_meals != -1)
		philo->data->num_of_meals++;
	pthread_mutex_unlock(&philo->data->mutex_meals);
	drop_forks(philo);
	return (1);
}

int	philo_is_sleeping(t_philo *philo)
{
	if (!is_philo_dead(philo->data))
	{
		print_message("\033[1;95mis sleeping\033[0m", philo);
		if (!ft_sleep(philo->data->time_to_sleep, philo))
			return (0);
		return (1);
	}
	else
		return (0);
}

int	philo_is_thinking(t_philo *philo)
{
	if (!is_philo_dead(philo->data))
	{
		print_message("\033[1;97mis thinking\033[0m", philo);
		usleep(50);
		return (1);
	}
	else
		return (0);
}
