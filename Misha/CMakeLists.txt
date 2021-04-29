cmake_minimum_required(VERSION 3.19)
project(shell C)

set(CMAKE_C_STANDARD 99)

add_executable(shell minishell.h parser/backslash.c pretokenizer_handler.c libft_utills.c parser/quotes_handler.c
        parser/parser.c parser/parser.h parser/syntax_err.c tokenizer_functions.c tokenizer/tokenizer.h)