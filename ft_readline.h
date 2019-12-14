/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:55:33 by yabakhar          #+#    #+#             */
/*   Updated: 2019/12/14 10:42:32 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "libft/includes/libft.h"
#include <sys/ioctl.h>
#define BUTTON_UP 4283163
#define BUTTON_DOWN 4348699
#define BUTTON_RIGHT 4414235
#define BUTTON_ALT_RIGHT 26139
#define BUTTON_LEFT 4479771
#define BUTTON_ALT_LEFT 25115
#define BUTTON_SPACE 32
#define BUTTON_ENTER 10
#define BUTTON_DEL 127
#define BUTTON_DEL2 2117294875
#define BUTTON_END 4610843
#define BUTTON_HOME 4741915
#define BUTTON_R 114

typedef struct s_readline
{
	struct termios config;
	char *line;
	char *tmp_line;
	int line_len;
	int col;
	int row;
	int cursor;
	int origin_cursor;
} t_readline;

typedef struct s_item
{
	char *content;
	_Bool selected;
	int len;
} t_item;

typedef struct s_ft_select
{
	t_item *items;
	struct termios config0;
	struct termios config;
	int fd;
	int cursor;
	int count;
	int col;
	int rows_count;
	int win_col;
	int max_col;
	int max_len;
} t_ft_select;

t_readline *g_readline;

void get_cursor_position(t_readline *readline);
void cur_up(t_readline *readline);
void cur_down(t_readline *readline);
void cur_right(t_readline *readline);
void cur_left(t_readline *readline);
void cur_move_by_word(t_readline *readline, int button);
void cursor_move(t_readline *readline, int old_cursor, int new_cursor);
void cur_goto(t_readline *readline, int cursor);

void set_signal(void);

int output(int str);
void print_args(t_readline *readline);
void set_items(int ac, char **av, t_readline *readline);

void configure_terminal(t_readline *readline);

void deactive_modes();
void active_modes(t_readline *readline, int cursor);

void delete_char(t_readline *readline, size_t num);
void delete_last_line(t_readline *readline);
void clean_win(t_readline *readline);

void insert_in_line(t_readline *readline, char *str);
void remove_from_line(t_readline *readline);
void rewrite_line(t_readline *readline);



void		signal_resize(int sig);
void sig_dispatch(int a);
