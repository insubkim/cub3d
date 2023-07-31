/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 21:27:09 by inskim            #+#    #+#             */
/*   Updated: 2023/07/31 15:50:23 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/get_next_line.h"

t_gnl_list	*get_node(t_gnl_list *lst, int fd)
{
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst -> fd == fd)
			return (lst);
		lst = lst -> next;
	}
	return (0);
}

int	add_buf(t_gnl_list **lst, int fd, char *read_buf)
{
	t_gnl_list	*node;

	node = get_node(*lst, fd);
	if (!node)
	{
		node = (t_gnl_list *)malloc(sizeof(t_gnl_list));
		if (!node)
			return (0);
		node -> str = 0;
		if (node != *lst)
			node -> next = *lst;
		*lst = node;
	}
	node -> str = gnl_strjoin(node -> str, read_buf);
	node -> fd = fd;
	if (!(node -> str))
		return (0);
	return (1);
}

int	set_node_str(t_gnl_list *node, int len)
{
	if (gnl_strlen(node -> str) == len)
		node -> str = 0;
	else
	{
		node -> str = gnl_substr(node -> str, len, gnl_strlen(node -> str));
		if (!(node -> str))
			return (0);
	}
	return (1);
}

char	*get_line(t_gnl_list **lst, int fd)
{
	t_gnl_list	*node;
	int			len;
	char		*str;
	char		*tmp;

	node = get_node(*lst, fd);
	if (!node || !(node -> str))
		return (error_handle(lst, fd, 0));
	len = 0;
	while ((node -> str)[len])
		if ((node -> str)[len++] == '\n')
			break ;
	str = gnl_substr(node -> str, 0, len);
	if (!str)
		return (error_handle(lst, fd, str));
	tmp = node -> str;
	if (!set_node_str(node, len))
	{
		free(str);
		return (0);
	}
	free(tmp);
	return (str);
}

char	*get_next_line(int fd, int *is_eof)
{
	char				*read_buf;
	static t_gnl_list	*lst;
	int					bytes;

	read_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buf || BUFFER_SIZE <= 0)
		return (error_handle(&lst, fd, read_buf));
	while (has_newline(lst, fd) == 0)
	{
		bytes = read(fd, read_buf, BUFFER_SIZE);
		if (bytes < 0)
			return (error_handle(&lst, fd, read_buf));
		if (bytes == 0)
		{
			*is_eof = 1;
			break ;
		}
		read_buf[bytes] = 0;
		if (add_buf(&lst, fd, read_buf) == 0)
			return (error_handle(&lst, fd, read_buf));
	}
	free(read_buf);
	return (get_line(&lst, fd));
}
