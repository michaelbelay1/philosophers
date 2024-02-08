/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 23:15:10 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/08 23:19:26 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	init_philos(t_data *data, char **av)
{
	data->num_of_philo = ft_atoi_l(av[1]);
	data->time_to_die = ft_atoi_l(av[2]);
	data->time_to_eat = ft_atoi_l(av[3]);
	data->time_to_sleep = ft_atoi_l(av[4]);
	if (av[5])
		data->must_eat_count = ft_atoi_l(av[5]);
	else
		data->must_eat_count = -1;
	data->philo_dead = 0;
}
