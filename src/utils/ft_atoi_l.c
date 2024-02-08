/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:48:49 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/08 23:05:15 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static int	handle_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
		{
			sign = -1;
		}
		(*i)++;
	}
	return (sign);
}

long long int	ft_atoi_l(const char *str)
{
	int				i;
	int				sign;
	long long int	res;
	int				digit;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	sign = handle_sign(str, &i);
	while (ft_isdigit(str[i]))
	{
		digit = str[i] - '0';
		if ((res > (9223372036854775807 - digit) / 10) && sign == 1)
			return ((long long int)INT_MAX + 1);
		else if ((res > (9223372036854775807 - digit) / 10) && sign == -1)
			return ((long long int)INT_MAX + 1);
		res = (res * 10) + digit;
		i++;
	}
	return ((int) sign * res);
}

// int main()
// {
//     char *num = "-9223372036854775804";
//     printf("%lld\n", ft_atoi(num));
// 		// printf("%d\n", atoi(num));
//     return (0);
// }
