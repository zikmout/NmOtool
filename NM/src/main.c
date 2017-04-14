/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 16:35:42 by ssicard           #+#    #+#             */
/*   Updated: 2017/04/14 15:32:50 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int							ft_check_arg(void *ptr, int ac_nb, char **av)
{
	struct stat				buf;
	int						fd;

	if (!ft_check_arg1(&fd, ac_nb, av))
		return (0);
	if (fstat(fd, &buf) == -1)
	{
		printf("Error with fstat. Exit\n");
		return (0);
	}
	if ((ptr = mmap(0, (size_t)buf.st_size, PROT_READ,\
					MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		printf("Error with mmap. Exit\n");
		return (0);
	}
	if (g_env.argc > 2)
		printf("\n%s:\n", av[ac_nb]);
	ft_nm(ptr);
	if (munmap(ptr, buf.st_size) == -1)
		return (0);
	close(fd);
	return (0);
}

int							main(int ac, char **av)
{
	void					*ptr;
	int						i;

	g_env.is_ppc = 0;
	ptr = NULL;
	if (ac < 2)
	{
		av[0] = ft_strdup("a.out");
		ac = 2;
	}
	g_env.argv = init_env(ac, av);
	if (g_env.argc > 2)
	{
		i = 1;
		while (i < g_env.argc)
		{
			ft_check_arg(ptr, i, g_env.argv);
			i++;
		}
		return (0);
	}
	else if (g_env.argc == 2)
		ft_check_arg(ptr, 1, g_env.argv);
	return (0);
}

char						**init_env(int ac, char **av)
{
	int						i;
	char					**argv;

	g_env.secs = NULL;
	g_env.nb_secs = 0;
	g_env.argc = ac;
	if (!(argv = (char **)(malloc(sizeof(char *) * ac + 1))))
		ft_putendl_fd("Malloc failed", 2);
	i = 0;
	while (av[i])
	{
		argv[i] = ft_strdup(av[i]);
		i++;
	}
	argv[i] = ft_strdup("\0");
	return (argv);
}

static void					ft_nm_env(unsigned int magic)
{
	g_env.type = 0;
	g_env.is_swap = 0;
	g_env.nb_secs = 0;
	g_env.is_fat = 0;
	if (magic == MH_MAGIC)
		g_env.type = 32;
	else if (magic == MH_CIGAM)
	{
		g_env.is_swap = 1;
		g_env.type = 32;
	}
	else if (magic == MH_MAGIC_64)
		g_env.type = 64;
	else if (magic == MH_CIGAM_64)
	{
		g_env.is_swap = 1;
		g_env.type = 64;
	}
	else if (magic == FAT_MAGIC)
		g_env.is_fat = 1;
	else if (magic == FAT_CIGAM)
	{
		g_env.is_swap = 1;
		g_env.is_fat = 1;
	}
}

void						ft_nm(void *ptr)
{
	unsigned int			magic;
	char					*secs;

	secs = NULL;
	magic = *(int *)ptr;
	ft_nm_env(magic);
	if (magic == MH_MAGIC || magic == MH_CIGAM || magic == MH_MAGIC_64 ||\
			magic == MH_CIGAM_64)
	{
		if (g_env.type == 32)
			get_header32_info(ptr);
		else
			get_header64_info(ptr);
		map_sections(ptr, -1);
		handle(ptr);
	}
	else if (magic == FAT_MAGIC)
		parse_fat(ptr);
	else if (magic == FAT_CIGAM)
		parse_fat(ptr);
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		parse_lib(ptr);
	else
		printf("Not handled yet. Exit\n");
}
