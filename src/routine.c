/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:34:27 by mhaile            #+#    #+#             */
/*   Updated: 2024/03/05 14:39:17 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_philo_dead(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->mutex_dead);
	res = data->philo_dead;
	pthread_mutex_unlock(&data->mutex_dead);
	return (res);
}

void	one_philo_case(t_philo *philo)
{
	print_message("\033[1;36mhas taken a fork\033[0m", philo);
	ft_sleep(philo->time_to_die, philo);
	pthread_mutex_lock(&philo->data->mutex_dead);
	philo->data->philo_dead = 1;
	pthread_mutex_unlock(&philo->data->mutex_dead);
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("\033[0;31m%lu %d died \033[0m\n", get_time()
		- philo->data->start_time, 1);
	pthread_mutex_unlock(&philo->data->mutex_print);
	join_threads(philo->data);
}

void	print_message(char *str, t_philo *philo)
{
	if (!is_philo_dead(philo->data))
	{
		pthread_mutex_lock(&philo->data->mutex_dead);
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%ld %d %s\n", get_time()
			- philo->data->start_time, philo->id, str);
		pthread_mutex_unlock(&philo->data->mutex_print);
		pthread_mutex_unlock(&philo->data->mutex_dead);
	}
}

int	take_fork_eat(t_philo *philo)
{
	if (is_philo_dead(philo->data))
		return (0);
	while (philo_takes_forks(philo) == 1)
	{
		usleep(100);
		if (is_philo_dead(philo->data))
			return (0);
	}
	if (!philo_is_eating(philo))
		return (0);
	return (1);
}

void	*philo_routine(void *arguments)
{
	t_philo	*philo;

	philo = (t_philo *)arguments;
	if (philo->data->num_of_philo == 1)
		return (0);
	else
	{
		if (philo->id % 2 == 0)
		{
			print_message("\033[1;97mis thinking\033[0m", philo);
			usleep(800);
		}
		while (!is_philo_dead(philo->data))
		{
			if (!take_fork_eat(philo))
				break ;
			is_max_eat(philo);
			if (!philo_is_sleeping(philo))
				break ;
			if (!philo_is_thinking(philo))
				break ;
		}
	}
	return (0);
}
