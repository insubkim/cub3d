/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 21:27:09 by inskim            #+#    #+#             */
/*   Updated: 2023/07/25 19:14:56 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# define BUFFER_SIZE 4096
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	int				fd;
	char			*str;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*error_handle(t_list **lst, int fd, char *read_buf);
int		has_newline(t_list *lst, int fd);
int		ft_strlen(const char *s);
char	*gnl_strjoin(char *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, int len);
t_list	*get_node(t_list *lst, int fd);

#endif
