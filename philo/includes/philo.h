/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:05:00 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/21 18:32:50 by glaguyon         ###   ########.fr       */
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
	uint32_t	neat;
	uint64_t	lasteat;
}	t_meal;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	char			clean;
}	t_fork;

typedef struct s_pdata
{
	t_data			data;
	t_fork			*forks;
	t_meal			*meals;
	pthread_t		*threads;
	pthread_mutex_t	run;
	struct timeval	start;
	uint16_t		eating;
}	t_pdata;

typedef struct s_philo
{
	t_pdata		*pdata;
	uint16_t	num;
	t_fork		*fork;
	t_fork		*nfork;
	t_meal		*meal;
}	t_philo;

//start
int		start_philo(t_data *data);

//utils
size_t	ft_strlen(char *s);
void	ft_perror(char *s);

//routine
void	*routine(void *philo_);
void	routine_loop(t_philo *philo, t_pdata *pdata,
			uint16_t n, struct timeval start);

//output
void	printp(uint64_t us, int num, int output);

#endif
