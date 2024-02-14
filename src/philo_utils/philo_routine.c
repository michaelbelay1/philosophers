/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:34:27 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/14 22:43:05 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork[philo->id]);
	if (!philo_is_dead(philo))
		print_message("has taken a fork", philo);
	pthread_mutex_unlock(&philo->left_fork[philo->id]);
	ft_sleep(philo->time_to_die, philo);
	philo->data->philo_dead = 1;
}

void	print_message(char *str, t_philo *philo)
{
	if (!philo_is_dead(philo))
	{
		pthread_mutex_lock(&philo->data->mutex);
		printf("%ld %d %s\n", get_time()
			- philo->data->start_time, philo->id, str);
		pthread_mutex_unlock(&philo->data->mutex);
	}
}

void	*philo_routine(void *arguments)
{
	t_philo	*philo;

	philo = (t_philo *)arguments;
	if (philo->num_of_philo == 1)
		one_philo_case(philo);
	while (philo->data->philo_dead == 0)
	{
		if (philo_is_dead(philo))
			return (0);
		philo_takes_forks(philo);
		if (philo_is_dead(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		philo_is_eating(philo);
		if (philo_is_dead(philo))
			return (0);
		philo_is_sleeping(philo);
		if (philo_is_dead(philo))
			return (0);
		philo_is_thinking(philo);
	}
	return (0);
}

void	create_threads(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_of_philo)
	{
		pthread_create(&data->philo[i].thread_id,
			NULL, &philo_routine, (void *)&data->philo[i]);
		i++;
	}
	j = 0;
	while (j < data->num_of_philo)
	{
		pthread_join(data->philo[j].thread_id, NULL);
		j++;
	}
}
