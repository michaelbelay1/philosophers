/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:34:27 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/22 21:35:00 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	make_philo_think(t_philo *philo)
{
	print_message("is thinking", philo);
	usleep(1000);
	return (1);
}

void	one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (!philo_is_dead(philo))
		print_message("has taken a fork", philo);
	pthread_mutex_unlock(philo->left_fork);
	ft_sleep(philo->time_to_die, philo);
	philo->data->philo_dead = 1;
	printf("%lu %d died\n", get_time()
			- philo->data->start_time, philo->id);
		// pthread_mutex_unlock(&philo->data->mutex);
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
void	is_max_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->num_of_meals != -1
		&& philo->data->num_of_meals == philo->data->num_of_philo * philo->data->must_eat_count)
	{
		philo->data->philo_dead = 1;
		// pthread_mutex_unlock(philo->right_fork);
		// pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->data->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->mutex);
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

			if (philo_is_dead(philo))
				break ;
			// philo_takes_forks(philo)
			while (philo_takes_forks(philo) == 1) {
				// printf("philo %d is thinking\n", philo->id);
			}
			if (philo_is_dead(philo))
				break ;
			// printf("philo %d is eating\n", philo->id);
			philo_is_eating(philo);
			is_max_eat(philo);
			// if (philo->data->num_of_meals != -1
			// 	&& philo->data->num_of_meals == philo->data->num_of_philo * philo->data->must_eat_count)
			// {
			// 	philo->data->philo_dead = 1;
			// 	// break ;
			// }
			if (philo_is_dead(philo))
				break ;
			philo_is_sleeping(philo);
			if (philo_is_dead(philo))
				break ;
			philo_is_thinking(philo);
		}
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
