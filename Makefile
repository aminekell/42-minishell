# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akella <akella@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 11:00:04 by zaissi            #+#    #+#              #
#    Updated: 2025/07/15 19:47:45 by akella           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LFLAGS		= -lreadline
LIBFT_DIR	= parsing/libft

MINISHELL	= minishell.c

EXECUTE		= execution/_main.c \
			  execution/sys_utils.c \
			  execution/buildin_cmd.c \
			  execution/environment.c \
			  execution/epc.c \
			  execution/_sys_utils.c \
			  execution/redirection.c \
			  execution/process.c \
			  execution/heredoc.c \
			  execution/help.c \
			  execution/build_cmd/export.c \
			  execution/build_cmd/cd.c \
			  execution/build_cmd/unset.c \
			  execution/build_cmd/echo.c \
			  execution/build_cmd/env.c \
			  execution/build_cmd/add_env.c \
			  execution/build_cmd/ft_export_utils.c \
			  execution/build_cmd/ft_env_utils.c \
			  execution/help_free.c \
			  execution/build_cmd/env_utils.c \
			  execution/redirection_utils.c \
			  execution/wird_cart_help.c \
			  execution/wird_cart_utils.c \
			  execution/wird_cart.c \
			  execution/help_utils.c \
			  execution/build_cmd/history.c \
			  execution/sort.c

PARSING_SRCS = parsing/parsing.c \
			   parsing/ft_exite.c \
			   parsing/ft_size.c \
			   parsing/ft_splite_shell.c \
			   parsing/ft_type.c \
			   parsing/splite_utils.c \
			   parsing/parsing_utils.c \
			   parsing/syntax_error/ft_syntax_error.c \
			   parsing/syntax_error/syntax_other.c \
			   parsing/syntax_error/syntax_pipes.c \
			   parsing/syntax_error/helper_functions.c \
			   parsing/tokenize/file_redirection.c \
			   parsing/tokenize/quotes.c \
			   parsing/tokenize/build_rederections.c \
			   parsing/tokenize/quotes_helper.c \
			   parsing/tokenize/helper.c \
			   parsing/tokenize/redirection.c \
			   parsing/tokenize/ft_toknize.c \
			   parsing/file_1.c \
			   parsing/file_2.c \
			   parsing/file_3.c \
			   parsing/file_4.c \
			   parsing/file_5.c \
			   parsing/syntax_error/syntax_helper.c \
			   parsing/parsing_helper.c \
			   parsing/expanding/build_expanded.c \
			   parsing/expanding/dollar.c \
			   parsing/expanding/expanded_length.c \
			   parsing/expanding/expanding_utils.c \
			   parsing/expanding/handle_d_s_q.c \
			   parsing/expanding/heredoc_expand.c \
			   parsing/expanding/splite_functions.c \
			   parsing/parsing_utils_2.c \
			   parsing/creat_word.c \
			   parsing/signal.c \
			   parsing/signal_helper.c \
			   parsing/gc_helper.c \
			   parsing/ft_alloc.c

LIBFT_FILE = $(LIBFT_DIR)/ft_atoi.c \
			 $(LIBFT_DIR)/ft_bzero.c \
			 $(LIBFT_DIR)/ft_calloc.c \
			 $(LIBFT_DIR)/ft_isalnum.c \
			 $(LIBFT_DIR)/ft_isalpha.c \
			 $(LIBFT_DIR)/ft_isascii.c \
			 $(LIBFT_DIR)/ft_isdigit.c \
			 $(LIBFT_DIR)/ft_isprint.c \
			 $(LIBFT_DIR)/ft_itoa.c \
			 $(LIBFT_DIR)/ft_memchr.c \
			 $(LIBFT_DIR)/ft_memcmp.c \
			 $(LIBFT_DIR)/ft_memcpy.c \
			 $(LIBFT_DIR)/ft_memmove.c \
			 $(LIBFT_DIR)/ft_memset.c \
			 $(LIBFT_DIR)/ft_putchar_fd.c \
			 $(LIBFT_DIR)/ft_putendl_fd.c \
			 $(LIBFT_DIR)/ft_putnbr_fd.c \
			 $(LIBFT_DIR)/ft_putstr_fd.c \
			 $(LIBFT_DIR)/ft_strchr.c \
			 $(LIBFT_DIR)/ft_strdup.c \
			 $(LIBFT_DIR)/ft_strjoin.c \
			 $(LIBFT_DIR)/ft_strlcat.c \
			 $(LIBFT_DIR)/ft_strlcpy.c \
			 $(LIBFT_DIR)/ft_strlen.c \
			 $(LIBFT_DIR)/ft_strmapi.c \
			 $(LIBFT_DIR)/ft_strnstr.c \
			 $(LIBFT_DIR)/ft_strrchr.c \
			 $(LIBFT_DIR)/ft_strtrim.c \
			 $(LIBFT_DIR)/ft_substr.c \
			 $(LIBFT_DIR)/ft_tolower.c \
			 $(LIBFT_DIR)/ft_toupper.c

OBJ_MINISHELL = $(MINISHELL:%.c=%.o) $(EXECUTE:%.c=%.o) $(PARSING_SRCS:%.c=%.o) $(LIBFT_FILE:%.c=%.o) 

all: $(NAME)

$(NAME): $(OBJ_MINISHELL)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ_MINISHELL) -o $(NAME)

%.o: %.c minishell.h parsing/expanding/expande.h parsing/libft/libft.h parsing/parsing.h parsing/syntax_error/syntax_checks.h parsing/tokenize/quotes.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_MINISHELL)

fclean: clean
	rm -f $(NAME)

re: fclean all
