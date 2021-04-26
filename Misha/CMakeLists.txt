cmake_minimum_required(VERSION 3.19)
project(shell C)

set(CMAKE_C_STANDARD 99)

add_executable(shell minishell.h backslash.c pretokenizer_handler.c libft_utills.c quotes_handler.c
        parser.c parser.h syntax_err.c tokenizer_functions.c)