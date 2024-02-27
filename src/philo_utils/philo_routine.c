/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:34:27 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/27 22:40:13 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	make_philo_think(t_philo *philo)
{
	(void)philo;
	// print_message("\033[1;97mis thinking\033[0m", philo);
	usleep(1000);
	return (1);
}

void	one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (!philo_is_dead(philo))
		print_message("\033[1;36mhas taken a fork\033[0m", philo);
	pthread_mutex_unlock(philo->left_fork);
	ft_sleep(philo->time_to_die, philo);
	pthread_mutex_lock(&philo->data->mutex);
	philo->data->philo_dead = 1;
	pthread_mutex_unlock(&philo->data->mutex);
}

void	print_message(char *str, t_philo *philo)
{
	if (!philo_is_dead(philo))
	{
		pthread_mutex_lock(&philo->data->mutex_dead);
		printf("%ld %d %s\n", get_time()
			- philo->data->start_time, philo->id, str);
		pthread_mutex_unlock(&philo->data->mutex_dead);
	}
}

int	take_fork_eat(t_philo *philo)
{
	if (philo_is_dead(philo))
		return (0);
	while (philo_takes_forks(philo) == 1)
	{
		usleep(100);
		if (philo_is_dead(philo))
			return (0);
	}
	if (philo_is_dead(philo))
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		return (0);
	}
	philo_is_eating(philo);
	return (1);
}

void	*philo_routine(void *arguments)
{
	t_philo	*philo;

	philo = (t_philo *)arguments;
	if (philo->num_of_philo == 1)
		one_philo_case(philo);
	else
	{
		if (philo->id % 2 == 0)
			make_philo_think(philo);
		while (1)
		{
			if (!take_fork_eat(philo))
				return (0);
			is_max_eat(philo);
			if (philo_is_dead(philo))
				return (0);
			philo_is_sleeping(philo);
			if (philo_is_dead(philo))
				return (0);
			philo_is_thinking(philo);
		}
	}
	return (0);
}
