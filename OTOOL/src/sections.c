/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 14:55:08 by ssicard           #+#    #+#             */
/*   Updated: 2017/04/14 15:18:37 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

char							read_tab(int i)
{
	char						*tab;

	tab = "0123456789abcdefghijklmnopqrstuvwxyz";
	return (tab[i]);
}

char							*ft_itoa_base(int val, int base,\
		int output_size)
{
	char						buffer[output_size + 1];
	char						*p;
	unsigned int				unsigned_val;

	unsigned_val = (unsigned int)val;
	if (base > 36 || base < 2)
		return (NULL);
	buffer[output_size] = 0;
	p = buffer + output_size - 1;
	*p = '0';
	if (unsigned_val > 0)
	{
		while (unsigned_val > 0)
		{
			*p-- = read_tab(unsigned_val % base);
			unsigned_val = unsigned_val / base;
			if (p < buffer)
				break ;
		}
		p++;
	}
	while (p > buffer)
		*--p = '0';
	return (ft_strdup(p));
}

void							cast_section_32_64_map(struct\
		segment_command_64 **sg_64, struct segment_command **sg_32,\
		struct section_64 **sc_64, struct section **sc_32)
{
	if (g_env.type == 64)
	{
		*sg_64 = (struct segment_command_64 *)(g_env.lc);
		*sc_64 = (struct section_64 *)(*sg_64 +\
				sizeof(*sg_64) / sizeof(void *));
		g_env.nsects = (g_env.is_swap) ? (rev_32(\
					(*sg_64)->nsects)) : ((*sg_64)->nsects);
		g_env.segname = ft_strdup((*sc_64)->segname);
	}
	else
	{
		*sg_32 = (struct segment_command *)(g_env.lc);
		*sc_32 = (struct section *)((*sg_32) +\
				sizeof(*sg_32) / sizeof(void *));
		g_env.nsects = (g_env.is_swap) ? (rev_32(\
					(*sg_32)->nsects)) : ((*sg_32)->nsects);
		g_env.segname = ft_strdup((*sc_32)->segname);
	}
}

void							print_tool(void *ptr,\
		struct section_64 *sc_64, struct section *sc_32)
{
	struct mach_header_64		*header_64;
	struct mach_header			*header_32;

	header_32 = (struct mach_header *)ptr;
	header_64 = (struct mach_header_64 *)ptr;
	if (g_env.type == 64)
		print_res(sc_64->addr, sc_64->size, (char *)header_64 + sc_64->offset);
	else
		print_res(sc_32->addr, sc_32->size, (char *)header_32 + sc_32->offset);
}

void							go_tool(void *ptr)
{
	struct section_64			*sc_64;
	struct section				*sc_32;
	struct segment_command_64	*sg_64;
	struct segment_command		*sg_32;
	uint32_t					i;

	i = -1;
	while (++i < g_env.ncmds)
	{
		g_env.lcmd = (g_env.is_swap) ? (rev_32(\
					g_env.lc->cmd)) : (g_env.lc->cmd);
		if (g_env.lcmd == LCS(g_env.type))
		{
			cast_section_32_64_map(&sg_64, &sg_32, &sc_64, &sc_32);
			if (ft_strcmp(g_env.segname, "__TEXT") == 0)
			{
				print_tool(ptr, sc_64, sc_32);
				break ;
			}
		}
		(g_env.is_swap) ? (g_env.lc = g_env.lc +\
				rev_32(g_env.lc->cmdsize) / sizeof(void *)) : (g_env.lc =\
				g_env.lc + g_env.lc->cmdsize / sizeof(void *));
	}
}
