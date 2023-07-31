/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:12:22 by heson             #+#    #+#             */
/*   Updated: 2023/07/31 15:57:58 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/my_types.h"
#include <stdio.h>

int	free_map(char **map, int h)
{
	while (h-- > 0)
		free(map[h]);
	free(map);
	return (ERROR_INT);
}

int	perror_n_return_false(char *error_message)
{
	printf("Error\n");
	printf("%s\n", error_message);
	return (FALSE);
}

