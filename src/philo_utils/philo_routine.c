/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:34:27 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/09 22:33:43 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

// int	check_last_meal(t_philo *philo)
// {
// 	if (get_time() - philo->data->start_time > philo->time_to_die)
// 	{
// 		philo->data->philo_dead = 1;
// 		printf("%d %d died\n", get_time()
// 			- philo->data->start_time, philo->id);
// 		return (0);
// 	}
// 	else
// 		return (1);
// }

// void	*test(void *arg)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)arg;
// 	for (int i = 0; i < 1000000; i++) {
// 		pthread_mutex_lock(&philo->data->mutex);
// 		g++;
// 		pthread_mutex_unlock(&philo->data->mutex);
// 	}
// 	return NULL;
// }

void	create_threads(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	printf("TIME: %lu\n", data->start_time);
	while (++i < data->num_of_philo)
		pthread_create(&data->philo[i].thread_id, NULL,
			&philo_routine, (void *)&data->philo[i]);
	i = -1;
	while (++i < data->num_of_philo)
		pthread_join(data->philo[i].thread_id, NULL);
}
