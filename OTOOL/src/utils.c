/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 13:59:00 by ssicard           #+#    #+#             */
/*   Updated: 2017/04/14 15:38:29 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

uint32_t				rev_32(uint32_t nb)
{
	return (((nb & 0xff000000) >> 24) |
			((nb & 0x00ff0000) >> 8) |
			((nb & 0x0000ff00) << 8) |
			(nb << 24));
}

int						get_len_lib(char *name)
{
	int					len;

	name = ft_strchr(name, '/') + 1;
	len = ft_atoi(name);
	return (len);
}

void					ft_nm_env(unsigned int magic)
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

void					print_res(long unsigned int addr,\
		unsigned int size, char *ptr)
{
	unsigned int		i;
	char				*str;

	i = 0;
	while (i < size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
			if (g_env.type == 64)
				ft_printf("%.16lx        ", addr);
			else
				ft_printf("%.8lx        ", addr);
		}
		str = ft_itoa_base(ptr[i], 16, 2);
		ft_printf("%s ", str);
		free(str);
		if ((i + 1) % 16 == 0)
			ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}
