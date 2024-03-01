/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:12:09 by mhaile            #+#    #+#             */
/*   Updated: 2024/03/01 20:46:09 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_of_philo)
	{
		pthread_create(&data->philo[i].thread_id,
			NULL, &philo_routine, (void *)&data->philo[i]);
		i++;
	}
}

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

int	main(int ac, char **av)
{
	t_data	data;
	int		philo_dead_id;

	if (arg_num(ac) || args_all_num(av))
		return (1);
	if (init_struct(&data, av))
	{
		ft_putstr_fd("Invalid argument\n", 2);
		return (1);
	}
	create_threads(&data);
	if (data.num_of_philo == 1)
	{
		pthread_mutex_lock(data.philo->left_fork);
		print_message("\033[1;36mhas taken a fork\033[0m", data.philo);
		usleep(data.time_to_die * 1000);
		printf("\033[0;31m%lu 1 died \033[0m\n", get_time()
			- data.philo->data->start_time);
		pthread_mutex_unlock(data.philo->left_fork);
	}
	else
	{
		philo_dead_id = begin_monitoring(&data);
		if (philo_dead_id)
		{
			pthread_mutex_lock(&data.mutex_dead);
			printf("\033[0;31m%lu %d died \033[0m\n", get_time()
				- data.philo->data->start_time, philo_dead_id);
			pthread_mutex_unlock(&data.mutex_dead);
		}
	}
	for (int i = 0; i < data.num_of_philo; i++)
	{
		if (pthread_mutex_lock(&data.forks[i]) == 0)
			pthread_mutex_unlock(&data.forks[i]);
		else
			pthread_mutex_unlock(&data.forks[i]);
	}
	join_threads(&data);
	for (int i = 0; i < data.num_of_philo; i++)
		pthread_mutex_destroy(&data.forks[i]);
	free(data.forks_taken);
	free(data.forks);
	free(data.philo);
}
