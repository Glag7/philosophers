/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:31:53 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/15 18:15:29 by glaguyon         ###   ########.fr       */
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

static void	cpy_state(char *restrict dst, const char *restrict src, int len)
{
	uint64_t	*dstlong;
	uint64_t	*srclong;
	int			i;

	dstlong = (uint64_t *)dst;
	srclong = (uint64_t *)src;
	dstlong[0] = srclong[0];
	dstlong[1] = srclong[1];
	dstlong[2] = srclong[2];
	dstlong[3] = srclong[3];
	i = 16;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

void	printp(uint64_t us, int num, int output)
{
	static const char	*messages[5] = {"\033[90m has taken a fork\033[0m\n",
		"\033[93m is eating\033[0m\n", "\033[94m is sleeping\033[0m\n",
		"\033[92m is thinking\033[0m\n", "\033[31m died\033[0m\n"};
	const int			lens[5] = {27, 20, 22, 22, 15};
	int					len;
	char				toprint[52];

	len = itoa_cpy(us / 1000, toprint);
	toprint[len] = ' ';
	len++;
	len += itoa_cpy(num, toprint + len);
	cpy_state(toprint + len, messages[output], lens[output]);
	len += lens[output];
	write(1, toprint, len);
}
