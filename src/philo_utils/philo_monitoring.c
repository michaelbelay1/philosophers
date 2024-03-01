/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:35:14 by mhaile            #+#    #+#             */
/*   Updated: 2024/03/01 16:13:51 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	if (philo->data->philo_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_dead);
		return (1);
	}
	if (!check_last_meal(philo))
	{
		philo->data->philo_dead = 1;
		pthread_mutex_unlock(&philo->data->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_dead);
	return (0);
}

int	check_last_meal(t_philo *philo)
{
	if (get_time() - philo->data->start_time >= philo->time_to_die)
	{
		philo->data->philo_dead = 1;
		return (0);
	}
	else
	{
		return (1);
	}
}

void	is_max_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	pthread_mutex_lock(&philo->data->mutex_meals);
	if (philo->data->must_eat_count != -1
		&& philo->data->num_of_meals >= philo->data->num_of_philo
		* philo->data->must_eat_count)
		philo->data->philo_dead = 1;
	pthread_mutex_unlock(&philo->data->mutex_meals);
	pthread_mutex_unlock(&philo->data->mutex_dead);
}

int	check_if_one_is_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (check_last_meal(&data->philo[i]) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}

int	begin_monitoring(void *arg)
{
	t_data	*data;
	int		dead_philo;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->mutex_dead);
		if (data->philo_dead == 1)
		{
			pthread_mutex_unlock(&data->mutex_dead);
			return (0);
		}
		dead_philo = check_if_one_is_dead(data);
		if (dead_philo)
		{
			pthread_mutex_unlock(&data->mutex_dead);
			return (dead_philo);
		}
		pthread_mutex_unlock(&data->mutex_dead);
		usleep(200);
	}
}
