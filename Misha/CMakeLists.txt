cmake_minimum_required(VERSION 3.19)
project(shell C)

set(CMAKE_C_STANDARD 99)

add_executable(shell main.c parser.c minishell.h executing.c get_normal_form.c syntax_err.c tokens_handler.c)