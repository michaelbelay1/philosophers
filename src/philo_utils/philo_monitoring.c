/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:35:14 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/21 15:17:03 by mhaile           ###   ########.fr       */
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
		philo->data->philo_dead = 1;
		// printf("%lu %d died\n", get_time()
		// 	- philo->data->start_time, philo->id);
		return (0);
	}
	else
		return (1);
}

int	check_if_one_is_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (check_last_meal(&data->philo[i]) == 1)
			return (1);
		i++;
	}
	return (1);
}

void	*begin_monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->mutex);
		if (check_if_one_is_dead(data) == 1)
		{
			// usleep(100);
			return (pthread_mutex_unlock(&data->mutex), NULL);
		}
		pthread_mutex_unlock(&data->mutex);
		// usleep(200);
	}
}
