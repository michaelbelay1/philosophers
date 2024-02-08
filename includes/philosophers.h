/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:07:40 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/08 23:16:45 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	long			last_eat;
	struct s_data	*data;
	pthread_t		thread;
}				t_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				philo_dead;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_philo			*philo;
}				t_data;

long long int	ft_atoi_l(const char *str);
void			ft_putstr_fd(char *s, int fd);
void			*ft_calloc(size_t count, size_t size);
void			ft_bzero(void *s, size_t n);
int				ft_isdigit(int c);
void			init_philos(t_data *data, char **av);

#endif
