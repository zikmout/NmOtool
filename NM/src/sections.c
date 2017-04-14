/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 10:32:42 by ssicard           #+#    #+#             */
/*   Updated: 2017/04/14 11:08:13 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void							cast_section_32_64_len(struct\
		segment_command_64 *sg_64, struct segment_command *sg_32,\
		struct section_64 *sc_64, struct section *sc_32)
{
	if (g_env.type == 64)
	{
		sg_64 = (struct segment_command_64 *)(g_env.lc);
		sc_64 = (struct section_64 *)(sg_64 + sizeof(sg_64) / sizeof(void *));
		g_env.nsects = (g_env.is_swap) ? (\
				rev_32(sg_64->nsects)) : (sg_64->nsects);
	}
	else
	{
		sg_32 = (struct segment_command *)(g_env.lc);
		sc_32 = (struct section *)(sg_32 + sizeof(sg_32) / sizeof(void *));
		g_env.nsects = (g_env.is_swap) ? (\
				rev_32(sg_32->nsects)) : (sg_32->nsects);
	}
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
	}
	else
	{
		*sg_32 = (struct segment_command *)(g_env.lc);
		*sc_32 = (struct section *)((*sg_32) +\
				sizeof(*sg_32) / sizeof(void *));
		g_env.nsects = (g_env.is_swap) ? (rev_32(\
					(*sg_32)->nsects)) : ((*sg_32)->nsects);
	}
}

void							reset_header(void *ptr)
{
	if (g_env.type == 64)
		get_header64_info(ptr);
	else
		get_header32_info(ptr);
}

void							parse_secs(struct section_64 **sc_64,\
		struct section **sc_32)
{
	uint32_t					j;

	j = -1;
	while (++j < g_env.nsects)
	{
		g_env.sectname = (g_env.type == 64) ? (ft_strdup(\
					(*sc_64)->sectname)) : (ft_strdup((*sc_32)->sectname));
		save_sections();
		free(g_env.sectname);
		g_env.secs_counter++;
		if (g_env.type == 64)
			*sc_64 = (struct section_64 *)(((void *)(*sc_64)) +\
					sizeof(struct section_64));
		else
			*sc_32 = (struct section *)(((void *)(*sc_32)) +\
					sizeof(struct section));
	}
}

void							map_sections(void *ptr, uint32_t i)
{
	struct section_64			*sc_64;
	struct section				*sc_32;
	struct segment_command_64	*sg_64;
	struct segment_command		*sg_32;

	i = -1;
	section_len(ptr, i);
	if (!(g_env.secs = (char *)malloc(sizeof(char) * g_env.nb_secs + 1)))
		ft_putendl_fd("Erreur malloc\n", 2);
	i = -1;
	while (++i < g_env.ncmds)
	{
		g_env.lcmd = (g_env.is_swap) ? (\
				rev_32(g_env.lc->cmd)) : (g_env.lc->cmd);
		if (g_env.lcmd == LCS(g_env.type))
		{
			cast_section_32_64_map(&sg_64, &sg_32, &sc_64, &sc_32);
			parse_secs(&sc_64, &sc_32);
		}
		g_env.lc = (g_env.is_swap) ? (g_env.lc +\
				rev_32(g_env.lc->cmdsize) / sizeof(void *)) : (g_env.lc +\
				g_env.lc->cmdsize / sizeof(void *));
	}
	reset_header(ptr);
}
