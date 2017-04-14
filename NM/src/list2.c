/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 10:52:54 by ssicard           #+#    #+#             */
/*   Updated: 2017/04/14 10:53:35 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_sym		*list_switch(t_sym *l, t_sym *r)
{
	l->next = r->next;
	r->next = l;
	return (r);
}

void		list_cmp(t_sym **p, t_sym **q, t_sym **top, int *changed)
{
	*changed = 0;
	*q = *top;
	*p = (*top)->next;
	while ((*p)->next != NULL)
	{
		if (strcmp((*p)->name, (*p)->next->name) > 0)
		{
			(*q)->next = list_switch(*p, (*p)->next);
			*changed = 1;
		}
		*q = *p;
		if ((*p)->next != NULL)
			*p = (*p)->next;
	}
}

t_sym		*list_sort(t_sym *head)
{
	t_sym	*p;
	t_sym	*q;
	t_sym	*top;
	int		changed;

	changed = 1;
	if (!(top = malloc(sizeof(*top))))
		ft_putendl_fd("Malloc failed", 2);
	top->next = head;
	while (changed)
	{
		list_cmp(&p, &q, &top, &changed);
	}
	p = top->next;
	free(top);
	return (p);
}
