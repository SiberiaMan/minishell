cmake_minimum_required(VERSION 3.19)
project(shell C)

set(CMAKE_C_STANDARD 99)

add_executable(shell minishell.h get_normal_form.c backslash.c pretokenizer_handler.c libft_utills.c quotes_handler.c)