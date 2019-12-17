/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/18 00:45:10 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void init(t_readline *readline);

void end_readline(t_readline *readline)
{
	t_cmd_history *head;

	head = get_cmd_history_head();
	head->line = readline->cmd->tmp_line;
	head->tmp_line = NULL;
	head->len = readline->cmd->tmp_len;
	readline->cmd->tmp_line = NULL;
	clean_hsitory();
	// if (readline->cmd->tmp_len)
	// 	add_to_history(readline->cmd->tmp_line, readline->cmd->tmp_len);
	ft_printf("\n➜  ft_readline git:(master) ");
	init(readline);
}
