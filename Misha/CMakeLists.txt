cmake_minimum_required(VERSION 3.19)
project(shell C)

set(CMAKE_C_STANDARD 99)
set(GCC_COVERAGE_COMPILE_FLAGS "-ltermcap")
SET(GCC_COVERAGE_LINK_FLAGS    "-ltermcap")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(shell minishell.h parser/backslash.c parser/quotes_handler.c parser/redirects_syntax.c
        parser/parser.c parser/parser.h parser/syntax_err.c tokenizer/redirects.c
        tokenizer/tokenizer.h tokenizer/dollar_sign_assign.c tokenizer/cmd.c tokenizer/dollar_sign_cnt.c
        tokenizer/conditions.c tokenizer/redirect_error.c executing/executing.h executing/executing.c
        termcap/termcap.h termcap/check_for_exit.c main.c termcap/keys.c termcap/keys2.c termcap/term_utills.c executing/free_functions.c
        tokenizer/free_and_exit_tokenizer.c tokenizer/check_cmd.c executing/change_io.c
        builtins/check_export.c builtins/env_alpha.c builtins/export_utills.c builtins/is_builtin.c
        builtins/manage_duplications.c  builtins/export.c executing/executing_utils.c executing/child_process.c
        minishell_utils/ft_itoa.c minishell_utils/ft_split.c minishell_utils/memory_handle_utils.c minishell_utils/string_utils1.c
        minishell_utils/string_utils2.c minishell_utils/minishell_utils.h tokenizer/get_redirect.c
        tokenizer/check_directory.c tokenizer/conditions_utils.c minishell_utils/string_utils3.c builtins/echo.c
        builtins/cd.c builtins/pwd.c minishell_utils/string_utils4.c)