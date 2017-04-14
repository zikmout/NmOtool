/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 16:32:56 by ssicard           #+#    #+#             */
/*   Updated: 2017/04/14 11:01:38 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
# define LCS(x) ((x == 64) ? (LC_SEGMENT_64) : (LC_SEGMENT))
# include "libft.h"
# include <sys/mman.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <ar.h>
# include <mach-o/ranlib.h>
# include <mach/machine.h>

typedef struct s_sym	t_sym;
struct					s_sym
{
	uint64_t			value;
	uint8_t				type;
	char				*name;
	t_sym				*next;
};

typedef struct s_env	t_env;
struct					s_env
{
	char				**argv;
	int					argc;
	int					is_swap;
	int					type;
	int					is_fat;
	int					is_ppc;
	char				*secs;
	int					nb_secs;
	int					secs_counter;
	struct load_command	*lc;
	uint32_t			ncmds;
	uint32_t			nsects;
	char				*sectname;
	uint32_t			lcmd;
	char				*name;
	t_sym				*head;
	uint32_t			nsyms;
	uint32_t			symoff;
	uint32_t			val;
};

t_env					g_env;

char					**init_env(int ac, char **av);
int						ft_check_arg(void *ptr, int ac_nb, char **av);
void					ft_nm(void *ptr);
void					print_env(void);
void					debug_nm(void *ptr);
void					print_magic_type(unsigned int magic, void *ptr);
uint32_t				rev_32(uint32_t	num);
char					get_sector_type(uint8_t sect, char *secs);
char					get_symbol_type(uint8_t type, uint8_t sect,\
		char *secs, uint32_t soffset);
int						get_len_lib(char *name);
int						ft_check_arg1(int *fd, int ac_nb, char **av);
void					get_header32_info(void *ptr);
void					get_header64_info(void *ptr);
void					map_sections(void *ptr, uint32_t i);
void					cast_section_32_64_len(struct\
		segment_command_64 *sg_64, struct segment_command *sg_32,\
		struct section_64 *sc_64, struct section *sc_32);
void					cast_section_32_64_map(struct\
		segment_command_64 **sg_64, struct segment_command **sg_32,\
		struct section_64 **sc_64, struct section **sc_32);
void					reset_header(void *ptr);
void					section_len(void *ptr, uint32_t i);
void					save_sections(void);
void					parse_lib(void *ptr);
void					handle(void *ptr);
void					print_scmd_32(void *ptr);
void					print_scmd_64(void *ptr);
t_sym					*list_find_end(t_sym *head);
void					list_push(t_sym **head, uint64_t value,\
		uint8_t type, char *name);
void					list_print(t_sym **head);
void					list_print_32(t_sym **head);
void					list_print_64(t_sym **head);
t_sym					*list_sort(t_sym *head);
t_sym					*list_switch(t_sym *l, t_sym *r);
void					parse_fat(void *ptr);
void					parse_fat2(void *ptr);
#endif
