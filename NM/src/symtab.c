/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:27:21 by ssicard           #+#    #+#             */
/*   Updated: 2017/04/14 11:09:09 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void							handle(void *ptr)
{
	uint32_t					i;

	g_env.head = NULL;
	i = 0;
	while (i < g_env.ncmds)
	{
		g_env.lcmd = (g_env.is_swap) ? (\
				rev_32(g_env.lc->cmd)) : (g_env.lc->cmd);
		if (g_env.lcmd == LC_SYMTAB && g_env.type == 32)
			print_scmd_32(ptr);
		else if (g_env.lcmd == LC_SYMTAB && g_env.type == 64)
			print_scmd_64(ptr);
		g_env.lc = (g_env.is_swap) ? ((void *)(g_env.lc) +\
				rev_32(g_env.lc->cmdsize)) : (\
				(void *)g_env.lc + g_env.lc->cmdsize);
		i++;
	}
}

void							push_smcd_32(struct nlist *el, int i,\
		void *ptr, struct symtab_command *sym)
{
	g_env.val = (g_env.is_swap) ? (rev_32(el[i].n_value)) : (el[i].n_value);
	g_env.name = (g_env.is_swap) ? (ptr + rev_32(sym->stroff) +\
			rev_32(el[i].n_un.n_strx)) : (ptr +\
			sym->stroff + el[i].n_un.n_strx);
	if (!g_env.is_ppc)
		list_push(&(g_env.head), el[i].n_value, get_symbol_type(el[i].n_type,\
					el[i].n_sect, g_env.secs, el[i].n_value), g_env.name);
	else
		list_push(&(g_env.head), rev_32(el[i].n_value),\
				get_symbol_type(el[i].n_type, el[i].n_sect,\
					g_env.secs, el[i].n_value), g_env.name);
}

void							print_scmd_32(void *ptr)
{
	struct symtab_command		*sym;
	struct segment_command		*sg;
	struct section				*section;
	struct nlist				*el;
	uint32_t					i;

	sym = (struct symtab_command *)(g_env.lc);
	sg = (struct segment_command *)(g_env.lc);
	section = (struct section *)(g_env.lc);
	g_env.symoff = (g_env.is_swap) ? (rev_32(sym->symoff)) : (sym->symoff);
	g_env.nsyms = (g_env.is_swap) ? (rev_32(sym->nsyms)) : (sym->nsyms);
	el = ptr + g_env.symoff;
	i = 0;
	while (i < g_env.nsyms)
	{
		push_smcd_32(el, i, ptr, sym);
		i++;
	}
	g_env.head = list_sort(g_env.head);
	list_print_32(&(g_env.head));
}

void							push_smcd_64(struct nlist_64 *el, int i,\
		void *ptr, struct symtab_command *sym)
{
	g_env.val = (g_env.is_swap) ? (rev_32(el[i].n_value)) : (el[i].n_value);
	g_env.name = (g_env.is_swap) ? (ptr + rev_32(sym->stroff) +\
			rev_32(el[i].n_un.n_strx)) : (ptr +\
			sym->stroff + el[i].n_un.n_strx);
	if (!g_env.is_ppc)
		list_push(&(g_env.head), el[i].n_value, get_symbol_type(el[i].n_type,\
					el[i].n_sect, g_env.secs, el[i].n_value), g_env.name);
	else
		list_push(&(g_env.head), rev_32(el[i].n_value),\
				get_symbol_type(el[i].n_type, el[i].n_sect,\
					g_env.secs, el[i].n_value), g_env.name);
}

void							print_scmd_64(void *ptr)
{
	struct symtab_command		*sym;
	struct segment_command_64	*sg;
	struct section_64			*section;
	struct nlist_64				*el;
	uint32_t					i;

	sym = (struct symtab_command *)(g_env.lc);
	sg = (struct segment_command_64 *)(g_env.lc);
	section = (struct section_64 *)(g_env.lc);
	g_env.symoff = (g_env.is_swap) ? (rev_32(sym->symoff)) : (sym->symoff);
	g_env.nsyms = (g_env.is_swap) ? (rev_32(sym->nsyms)) : (sym->nsyms);
	el = ptr + g_env.symoff;
	i = 0;
	while (i < g_env.nsyms)
	{
		push_smcd_64(el, i, ptr, sym);
		i++;
	}
	g_env.head = list_sort(g_env.head);
	list_print_64(&(g_env.head));
}
