/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:27:02 by mhaile            #+#    #+#             */
/*   Updated: 2024/03/05 14:04:33 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_fork_available(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (*philo->l_fork && *philo->l_fork != philo->id)
		pthread_mutex_unlock(philo->left_fork);
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	if (*philo->r_fork && *philo->r_fork != philo->id)
	{
		*philo->r_fork = philo->id;
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	return (1);
}

int	philo_takes_forks(t_philo *philo)
{
	if (is_fork_available(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		*philo->l_fork = 0;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		*philo->r_fork = 0;
		pthread_mutex_unlock(philo->right_fork);
	}
	else
		return (1);
	print_message("\033[1;36mhas taken a fork\033[0m", philo);
	print_message("\033[1;36mhas taken a fork\033[0m", philo);
	return (0);
}

int	philo_is_eating(t_philo *philo)
{
	print_message("\033[1;32m\033[0m\033[1;32mis eating\033[0m", philo);
	pthread_mutex_lock(&philo->data->mutex_dead);
	philo->time_to_die = (get_time() - philo->data->start_time)
		+ philo->data->time_to_die;
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
		return (1);
	}
	else
		return (0);
}
