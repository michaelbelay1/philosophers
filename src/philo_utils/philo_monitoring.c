/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:35:14 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/26 21:55:24 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
}

int	check_last_meal(t_philo *philo)
{
	if (get_time() - philo->data->start_time >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->data->mutex_dead);
		philo->data->philo_dead = 1;
		// printf("%lu %d died\n", get_time()
		// 	- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_dead);
		return (0);
	}
	else
		return (1);
}

void	is_max_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_meals);
	if (philo->data->num_of_meals != -1
		&& philo->data->num_of_meals == philo->data->num_of_philo * philo->data->must_eat_count)
		philo->data->philo_dead = 1;
	pthread_mutex_unlock(&philo->data->mutex_meals);
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
	int 	i;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->mutex);
		pthread_mutex_lock(&data->mutex_meals);
		if (data->philo_dead == 1)
		{
			pthread_mutex_unlock(&data->mutex_meals);
			pthread_mutex_unlock(&data->mutex);
			return (0);
		}
		i = check_if_one_is_dead(data);
		if (i)
		{
			usleep(100);
			pthread_mutex_unlock(&data->mutex_meals);
			pthread_mutex_unlock(&data->mutex);
			return (i);
		}
		pthread_mutex_unlock(&data->mutex_meals);
		pthread_mutex_unlock(&data->mutex);
		usleep(200);
	}
}
