/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 10:42:14 by ssicard           #+#    #+#             */
/*   Updated: 2017/04/14 10:43:04 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

uint32_t	rev_32(uint32_t nb)
{
	return (((nb & 0xff000000) >> 24) |
			((nb & 0x00ff0000) >> 8) |
			((nb & 0x0000ff00) << 8) |
			(nb << 24));
}

char		get_sector_type(uint8_t sect, char *secs)
{
	return (secs[sect - 1]);
}

char		get_symbol_type(uint8_t type,\
		uint8_t sect, char *secs, uint32_t soffset)
{
	char	c;

	c = '?';
	if ((type & N_TYPE) == N_UNDF)
	{
		if (soffset)
			c = 'C';
		else
			c = 'U';
	}
	else if ((type & N_TYPE) == N_ABS)
		c = 'A';
	else if ((type & N_TYPE) == N_SECT)
		c = get_sector_type(sect, secs);
	else if ((type & N_TYPE) == N_PBUD)
		c = 'U';
	else if ((type & N_TYPE) == N_INDR)
		c = 'I';
	if ((type & N_STAB) != 0)
		c = 'Z';
	if ((type & N_EXT) == 0 && c != '?')
		c += 32;
	return (c);
}

int			get_len_lib(char *name)
{
	int		len;

	name = ft_strchr(name, '/') + 1;
	len = ft_atoi(name);
	return (len);
}

int			ft_check_arg1(int *fd, int ac_nb, char **av)
{
	if ((*fd = open(av[ac_nb], O_RDONLY)) < 0)
	{
		printf("%s:%s: No such file or directory.\n", av[0], av[ac_nb]);
		return (0);
	}
	return (1);
}
