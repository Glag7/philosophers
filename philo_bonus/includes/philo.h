/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:05:00 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/28 15:48:29 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>

//errors
# define ERR_ARG 1
# define ERR_NUM 2
# define ERR_AINTNOWAY 3
# define ERR_FORK 4
# define ERR_SEM 5

//sems
# define FORKS "/forks_philo_bonus"
# define PFORK "/fork_prot_philo_bonus"
# define RUN "/run_philo_bonus"
# define EATING "/eating_philo_bonus"
# define END "/end_philo_bonus"
# define S_MOD 444

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

typedef struct s_pdata
{
	sem_t			*run;
	sem_t			*end;
	sem_t			*forks;
	sem_t			*pfork;
	sem_t			*eating;
	sem_t			**run_n;
	pid_t			*proc;
	t_data			data;
	t_meal			meal;
	pthread_t		thread[2];
	struct timeval	start;
	int				n;
}	t_pdata;

//start
int		start_philo(t_data *data);
void	free_philo(t_pdata *pdata);

//utils
size_t	ft_strlen(char *s);
void	ft_perror(char *s);
void	gettimeofday_adjust(struct timeval *tim, int nphilo);
void	free_philo(t_pdata *pdata);

//err
void	dec_sems(t_pdata *pdata, int n);
void	dec_sems_except(t_pdata *pdata, int n);
void	clean_exit(t_pdata *pdata, int n);

//output
void	printp(uint64_t us, int num, int output);

//routine
void	start_routine(t_pdata *pdata);
void	routine(t_pdata *pdata, int n, sem_t *run_n, sem_t *run);

//sem
void	sem_close_all(t_pdata *pdata, int n);
int		init_sem(t_pdata *pdata);

#endif
