/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:43:55 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/08 23:05:06 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size && (count > 4294967295 / size))
		return (0);
	p = malloc (count * size);
	if (!p)
		return (0);
	ft_bzero(p, (count * size));
	return (p);
}

// int main()
// {
// 	int c = 0;
// 	int s = -5;
// 	printf("%s\n", ft_calloc(c, s));
//     printf("%s\n", calloc(c, s));
// 	printf("%d\n", 4294967295 / -5);
// 	return (0);
// }
