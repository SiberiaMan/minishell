cmake_minimum_required(VERSION 3.19)
project(shell C)

set(CMAKE_C_STANDARD 99)
SET(GCC_COVERAGE_COMPILE_FLAGS "-ltermcap")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_executable(shell minishell.h parser/backslash.c libft_utills.c parser/quotes_handler.c
        parser/parser.c parser/parser.h parser/syntax_err.c tokenizer/redirects.c
        tokenizer/tokenizer.h tokenizer/dollar_sign_assign.c tokenizer/cmd.c tokenizer/dollar_sign_cnt.c
        tokenizer/conditions.c tokenizer/redirect_error.c executing/executing.h executing/kern.c
        U/history1.h U/check_for_exit.c main.c U/keys.c U/keys2.c U/term_utills.c)