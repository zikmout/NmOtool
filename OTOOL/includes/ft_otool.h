/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 16:32:56 by ssicard           #+#    #+#             */
/*   Updated: 2017/04/14 15:36:45 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H
# define LCS(x) ((x == 64) ? (LC_SEGMENT_64) : (LC_SEGMENT))
# include "libft.h"
# include "printf.h"
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
	char				*segname;
	uint32_t			lcmd;
	char				*name;
};

t_env					g_env;

char					**init_env(int ac, char **av);
int						ft_check_arg(void *ptr, int ac_nb, char **av);
void					ft_otool(void *ptr);
void					print_env(void);
void					debug_nm(void *ptr);
void					print_magic_type(unsigned int magic, void *ptr);
uint32_t				rev_32(uint32_t	num);
int						get_len_lib(char *name);
void					ft_nm_env(unsigned int magic);
void					get_header32_info(void *ptr);
void					get_header64_info(void *ptr);
char					read_tab(int i);
char					*ft_itoa_base(int val, int base,\
		int output_size);
void					go_tool(void *ptr);
void					print_res(long unsigned int addr,\
		unsigned int size, char *ptr);
void					parse_lib(void *ptr);
void					parse_fat(void *ptr);
#endif
