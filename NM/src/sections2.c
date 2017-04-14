/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 10:35:11 by ssicard           #+#    #+#             */
/*   Updated: 2017/04/14 11:15:12 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void							init_seg(struct section_64 **sc_64,\
		struct section **sc_32, struct segment_command_64 **sg_64,\
		struct segment_command **sg_32)
{
	sc_64 = NULL;
	sg_64 = NULL;
	sc_32 = NULL;
	sg_32 = NULL;
}

void							section_len(void *ptr, uint32_t i)
{
	struct section_64			*sc_64;
	struct section				*sc_32;
	struct segment_command_64	*sg_64;
	struct segment_command		*sg_32;
	uint32_t					j;

	init_seg(&sc_64, &sc_32, &sg_64, &sg_32);
	while (++i < g_env.ncmds)
	{
		g_env.lcmd = (g_env.is_swap) ? (\
				rev_32(g_env.lc->cmd)) : (g_env.lc->cmd);
		if (g_env.lcmd == LCS(g_env.type))
		{
			cast_section_32_64_len(sg_64, sg_32, sc_64, sc_32);
			j = -1;
			while (++j < g_env.nsects)
				g_env.nb_secs++;
		}
		g_env.lc = (g_env.is_swap) ? (g_env.lc +\
				rev_32(g_env.lc->cmdsize) / sizeof(void *)) : (g_env.lc +\
				g_env.lc->cmdsize / sizeof(void *));
	}
	reset_header(ptr);
}

void							save_sections(void)
{
	if (ft_strcmp(g_env.sectname, SECT_DATA) == 0)
		g_env.secs[g_env.secs_counter] = 'D';
	else if (ft_strcmp(g_env.sectname, SECT_TEXT) == 0)
		g_env.secs[g_env.secs_counter] = 'T';
	else if (ft_strcmp(g_env.sectname, SECT_BSS) == 0)
		g_env.secs[g_env.secs_counter] = 'B';
	else
		g_env.secs[g_env.secs_counter] = 'S';
	if (g_env.secs_counter == g_env.nb_secs - 1)
		g_env.secs[g_env.nb_secs] = '\0';
}

void							parse_lib(void *ptr)
{
	struct ar_hdr				*ar;
	struct ranlib				*ranlib;
	char						*str;
	int							size;
	unsigned long				i;

	ar = (void *)ptr + SARMAG;
	size = get_len_lib(ar->ar_name);
	str = (void *)ptr + sizeof(*ar) + SARMAG + size;
	ranlib = (void *)ptr + sizeof(*ar) + SARMAG + size + 4;
	i = 0;
	while (i < ((*((int *)str)) / sizeof(struct ranlib)))
	{
		ar = (void *)ptr + ranlib[i].ran_off;
		printf("\n%s(%s):\n", g_env.argv[1], ft_strchr(ar->ar_name, '\n') + 1);
		ft_nm((void *)ar + sizeof(*ar) + get_len_lib(ar->ar_name));
		i++;
	}
}
