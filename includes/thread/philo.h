/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:05:00 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/15 18:07:53 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERR_ARG 1
# define ERR_NUM 2
# define ERR_AINTNOWAY 3
# define ERR_THREAD 4

enum e_output
{
	FORK = 0,
	EAT,
	SLEEP,
	THINK,
	DIE
};

typedef struct s_data
{
	uint64_t	tdie;
	uint64_t	teat;
	uint64_t	tsleep;
	uint32_t	neat;
	uint16_t	nphilo;
	uint8_t		eatstop;
	uint8_t		end;
}	t_data;

typedef struct s_meal
{
	uint32_t		neat;
	struct timeval	lasteat;
}	t_meal;

typedef struct s_pdata
{
	t_data		data;
	char		*forks;
	t_meal		*meals;
	pthread_t	*threads;
}	t_pdata;

typedef struct s_philo
{
	t_pdata		*pdata;
	uint16_t	num;
}	t_philo;

//start
int		start_philo(t_data *data);

//utils
size_t	ft_strlen(char *s);
void	ft_perror(char *s);

//routine
void	*routine(void *philo_);

//output
void	printp(uint64_t us, int num, int output);

#endif
