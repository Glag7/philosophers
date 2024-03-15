/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:34:02 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/15 16:16:14 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread/philo.h"

static int32_t	ft_atoi(char *s, uint32_t *n, uint32_t mult, uint64_t max)
{
	const char	*start = s + (*s == '+');

	s += (*s == '+');
	if (*s == '-')
	{
		ft_perror("Error: number cannot be negative\n");
		return (1);
	}
	while (*s >= '0' && *s <= '9')
	{
		if ((uint64_t)(*n) * 10 + *s - '0' > max)
		{
			ft_perror("Error: number is too big\n");
			return (1);
		}
		*n = *n * 10 + *s - '0';
		s++;
	}
	if (*s)
		ft_perror("Error: character is not a number\n");
	if (!*s && s == start)
		ft_perror("Error: string is empty\n");
	*(uint64_t *)n *= mult;
	return (*s || s == start);
}

static void	trim_args(int argc, char **argv)
{
	int		i;
	char	minus;
	size_t	j;
	size_t	last;

	i = 0;
	while (i < argc)
	{
		while (argv[i][0] == ' ')
			argv[i]++;
		minus = argv[i][0] == '-';
		j = minus;
		last = minus + 1;
		while (argv[i][j])
		{
			minus &= (argv[i][j] == '0' || argv[i][j] == ' ');
			if (argv[i][j] != ' ')
				last = j + 1;
			j++;
		}
		argv[i][last] = 0;
		argv[i] += minus;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5)
	{
		ft_perror("Error: not enough args\n");
		return (ERR_ARG);
	}
	if (argc > 6)
	{
		ft_perror("Error: too many args\n");
		return (ERR_ARG);
	}
	trim_args(argc - 1, argv + 1);
	data = (t_data){0, 0, 0, 0, 0, 0, 0};
	if (ft_atoi(argv[1], (uint32_t *)&data.nphilo, 1, 65535)
		|| ft_atoi(argv[2], (uint32_t *)&data.tdie, 1000, 4294967295)
		|| ft_atoi(argv[3], (uint32_t *)&data.teat, 1000, 4294967295)
		|| ft_atoi(argv[4], (uint32_t *)&data.tsleep, 1000, 4294967295))
		return (ERR_NUM);
	if (argc == 6 && ft_atoi(argv[5], &data.neat, 1, 4294967295))
		return (ERR_NUM);
	data.eatstop = argc == 6;
	if (data.nphilo == 0)
		return (0);
	return (start_philo(&data));
}
