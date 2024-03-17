/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:31:53 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/17 18:17:11 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread/philo.h"

static inline int	itoa_cpy(uint64_t n, char *dest)
{
	int		len;
	int		i;
	char	rev[19];

	*rev = n % 10 + '0';
	n /= 10;
	len = 1;
	while (n)
	{
		rev[len] = n % 10 + '0';
		n /= 10;
		len++;
	}
	i = 0;
	while (i < len)
	{
		dest[i] = rev[len - 1 - i];
		i++;
	}
	return (len);
}

static void	cpy_state(char *restrict dst, const char *restrict src)
{
	uint64_t	*dstlong;
	uint64_t	*srclong;

	dstlong = (uint64_t *)dst;
	srclong = (uint64_t *)src;
	dstlong[0] = srclong[0];
	dstlong[1] = srclong[1];
	dstlong[2] = srclong[2];
}

void	printp(uint64_t us, int num, int output)
{
	static const char	*colors[5] = {"\033[90m\0\0", "\033[93m\0\0",
		"\033[94m\0\0", "\033[92m\0\0", "\033[31m\0\0"};
	static const char	*messages[5] = {" has taken a fork\033[0m\n\0",
		" is eating\033[0m\n\0\0\0\0\0\0\0\0",
		" is sleeping\033[0m\n\0\0\0\0\0\0",
		" is thinking\033[0m\n\0\0\0\0\0\0",
		" died\033[0m\n\0\0\0\0\0\0\0\0\0\0\0\0\0"};
	const int			lens[5] = {22, 15, 17, 17, 10};
	int					len;
	char				toprint[52];

	((uint64_t *)toprint)[0] = ((uint64_t *)colors[output])[0];
	len = 5 + itoa_cpy(us / 1000, toprint + 5);
	toprint[len] = ' ';
	len++;
	len += itoa_cpy(num, toprint + len);
	cpy_state(toprint + len, messages[output]);
	len += lens[output];
	write(1, toprint, len);
}
