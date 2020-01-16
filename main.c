/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 00:57:15 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/16 23:35:57 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include <readline/readline.h>

char *remove_unprintable_chars(char *str)
{
	char *ret;
	int i;

	ret = str;
	i = 0;
	if (str)
	{
		while (*str)
		{
			if (ft_isprint(*str) || *str == '\n')
			{
				ret[i++] = *str;
			}
			str++;
		}
		ret[i] = 0;
	}
	return (ret);
}

int key_handel(t_readline *env, int b, int r)
{
	if (b == BUTTON_UP && !(r = 0))
		set_cur_history(env, env->cmd->next);
	else if (b == BUTTON_DOWN && !(r = 0))
		set_cur_history(env, env->cmd->prev);
	else if (b == BUTTON_RIGHT && !(r = 0))
		cur_right(env);
	else if (b == BUTTON_LEFT && !(r = 0))
		cur_left(env);
	else if (b == BUTTON_PUP && !(r = 0))
		cur_up(env);
	else if (b == BUTTON_PDOWN && !(r = 0))
		cur_down(env);
	else if ((b == BUTTON_HOME || b == BUTTON_END) && !(r = 0))
		to_start_or_end(env, b);
	else if ((b == BUTTON_ALT_RIGHT || b == BUTTON_ALT_LEFT) && !(r = 0))
		cur_move_by_word(env, b);
	else if ((b == BUTTON_DEL || b == BUTTON_DEL2) && !(r = 0))
		remove_from_line(env, env->line_index - 1, env->line_index - 1);
	else if (b == BUTTON_ENTER && !(r = 0))
		end_readline(env, 1);
	else if (b == BUTTON_SELECT && !(r = 0))
		selection(env);
	else if (b == BUTTON_PAST && !(r = 0))
		insert_in_line(env, remove_unprintable_chars(env->to_past));
	return (r);
}

void init(t_readline *readline)
{
	g_readline = readline;
	ft_bzero(readline, sizeof(t_readline));
	if (tcgetattr(0, &readline->config) < 0)
		puts("error");
	readline->config.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(0, 0, &readline->config) < 0)
		puts("error");
	tgetent(NULL, getenv("TERM"));
	signal_resize(0);
	get_cursor_position(readline);
	add_to_history(ft_strdup(""), 0);
	readline->cmd = get_cmd_history_head();
	readline->line_props.linecount = 1;
	readline->line_props.details = ft_memalloc(sizeof(int));
}


void end_readline(t_readline *readline, int suit)
{
	t_cmd_history *head;
	char *tmp;

	head = get_cmd_history_head();
	if (suit && head->next)
	{
		tmp = ft_strnjoin((char *[]){head->next->line, "\n", readline->cmd->tmp_line}, 3);
		ft_strdel(&head->line);
		free(readline->cmd->tmp_line);
		readline->cmd->tmp_line = tmp;
		readline->cmd->tmp_len = head->next->len + readline->cmd->tmp_len + 1;
		head = head->next;
	}
	head->line = readline->cmd->tmp_line;
	head->len = readline->cmd->tmp_len;
	readline->cmd->tmp_line = NULL;
	ft_strdel(&head->tmp_line);
	clean_hsitory();
	ft_printf("\n➜  ft_readline git:(master) ");
	init(readline);
}

int everything_is_ok(t_readline *readline)
{
	int ret;

	ret = 1;
	ret &= (readline->cmd && readline->cmd->tmp_line);
	ret &= (readline->line_props.details != NULL);
	if(ret)
	{
		readline->line_index %= readline->cmd->tmp_len + 1;
		readline->line_props.index %= readline->line_props.linecount;
		readline->cursor %= readline->line_props.details[readline->line_props.index] + 1;
	}
	return(ret);
}

int main()
{
	t_readline readline;
	char buff[2049];
	int r;
	int button;
	// int fd = open("/dev/ttys002", O_WRONLY);

	ft_printf("➜  ft_readline git:(master) ");
	init(&readline);
	while (everything_is_ok(&readline))
	{
		ft_bzero(buff, 2049);
		if ((r = read(0, buff, 2048)) > 0)
		{
			// ft_putnbr_fd(((int *)buff)[0], fd);
			// ft_putstr_fd("   ", fd);
			button = *((int *)buff);
			if (key_handel(&readline, button, 1))
				insert_in_line(&readline, remove_unprintable_chars(buff));
		}
	}
	// end_readline(&readline, 0);
}
