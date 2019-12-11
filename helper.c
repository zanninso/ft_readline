/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:38 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/11 03:10:44 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void insert_in_line(t_readline *readline, char c)
{
	char *new_line;
	char *line;
	char *tmp = (char []){c, 0};

	readline->line[readline->cursor] = 0;
	line = readline->line;
	if (readline->line_len == readline->cursor)
		new_line = ft_strjoin(readline->line, tmp);
	else
		new_line = ft_strnjoin((char *[]){line, tmp, &line[readline->cursor + 1]}, 3);
	if (new_line)
	{
		free(line);
		readline->line = new_line;
		readline->line_len++;
		readline->cursor++;
	}
	
}

void cur_goto(t_readline *readline, int cursor)
{
	int co;
	int li;

	li = cursor / readline->row;
	co = cursor % readline->row;
	;
	tputs(tgoto(tgetstr("cm", 0), co, li), 0, output);
}

int output(int c)
{
	ft_putchar(c);
	return (0);
}
// void	configure_terminal(t_ft_select *ft_select)
// {
// 	if (tcgetattr(0, &ft_select->config) < 0)
// 		ft_die(ERR_TERM_GET_ARG, -2);
// 	ft_select->config.c_lflag &= ~(ECHO | ICANON);
// 	if (tcsetattr(0, 0, &ft_select->config) < 0)
// 		ft_die(ERR_TERM_SET_ARG, -3);
// 	if (tgetent(NULL, getenv("TERM")) <= 0)
// 		ft_die(ERR_TERM_INIT, -4);
// 	tputs(tgetstr("ti", 0), 0, output);
// 	tputs(tgetstr("vi", 0), 0, output);
// }
