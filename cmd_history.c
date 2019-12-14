/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 08:55:45 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/14 09:23:46 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static char	**history_list = NULL;
static size_t history_count = 0;
static size_t history_size = 0;

int	init_history()
{
	if (history_list)
		return (1);
	if ((history_list = (char **)malloc(sizeof(char *) * 100)))
		return (1);
	return(0);
}

void add_to_history(char *str)
{
	char **tmp;
	if(!str)
		return ;
	if(history_count == history_size)
	{
		if(tmp = (char **)malloc(sizeof(char *) * (history_size + 100)))
		{
			ft_memcpy(tmp, history_list, history_size);
			history_size += 100;
		}
		else 
			return ;
	}
	history_list[history_count++] = str;
}

free_history()
{
	ft_lstdel(history_list);
}
