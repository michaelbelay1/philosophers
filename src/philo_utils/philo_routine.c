/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:34:27 by mhaile            #+#    #+#             */
/*   Updated: 2024/03/02 13:11:06 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	make_philo_think(t_philo *philo)
{
	(void)philo;
	usleep(1000);
	return (1);
}

void	clean_up(t_data *data)
{
	int	idx;

	idx = -1;
	while (++idx < data->num_of_philo)
	{
		if (pthread_mutex_lock(&data->forks[idx]) == 0)
			pthread_mutex_unlock(&data->forks[idx]);
		else
			pthread_mutex_unlock(&data->forks[idx]);
	}
	join_threads(data);
	idx = -1;
	while (++idx < data->num_of_philo)
		pthread_mutex_destroy(&data->forks[idx]);
	free(data->forks_taken);
	free(data->forks);
	free(data->philo);
}

void	one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message("\033[1;36mhas taken a fork\033[0m", philo);
	ft_sleep(philo->time_to_die, philo);
	pthread_mutex_lock(&philo->data->mutex_dead);
	philo->data->philo_dead = 1;
	printf("\033[0;31m%lu %d died \033[0m\n", get_time()
		- philo->data->start_time, 1);
	pthread_mutex_unlock(&philo->data->mutex_dead);
	pthread_mutex_unlock(philo->left_fork);
}

void	print_message(char *str, t_philo *philo)
{
	if (!philo_is_dead(philo))
	{
		pthread_mutex_lock(&philo->data->mutex_print);
		pthread_mutex_lock(&philo->data->mutex_dead);
		printf("%ld %d %s\n", get_time()
			- philo->data->start_time, philo->id, str);
		pthread_mutex_unlock(&philo->data->mutex_dead);
		pthread_mutex_unlock(&philo->data->mutex_print);
	}
}

void	*philo_routine(void *arguments)
{
	t_philo	*philo;

	philo = (t_philo *)arguments;
	if (philo->num_of_philo == 1)
		return (0);
	else
	{
		if (philo->id % 2 == 0)
			make_philo_think(philo);
		pthread_mutex_lock(&philo->data->mutex_dead);
		while (philo->data->philo_dead == 0)
		{
			pthread_mutex_unlock(&philo->data->mutex_dead);
			while (philo_takes_forks(philo) == 1)
				usleep(100);
			philo_is_eating(philo);
			is_max_eat(philo);
			philo_is_sleeping(philo);
			philo_is_thinking(philo);
			pthread_mutex_lock(&philo->data->mutex_dead);
		}
		pthread_mutex_unlock(&philo->data->mutex_dead);
	}
	return (0);
}
