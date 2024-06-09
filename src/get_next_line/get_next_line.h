/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:34:14 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/05 03:14:04 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# if BUFFER_SIZE == INT_MAX || BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

char	*get_next_line(int fd);
char	*ft_gen_ans(int fd, char *box[OPEN_MAX + 1]);
void	ft_free_null(char *box[OPEN_MAX + 1]);
size_t	ft_strlen(const char *str);
int		ft_find_nl(char *str);
int		ft_gen_help(char *buf, char **ans_p, size_t *start_end);
char	*ft_gen_ans_h(char *box[OPEN_MAX + 1], int fd, char **ap, size_t *se);
char	*ft_join_ans(char **old_ans_p, char *buf, size_t *start_end);
void	ft_join_ans_h(char *new_ans, char *buf, size_t len, size_t *start_end);

#endif
