#!/bin/bash

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         --track-fds=yes \
         --show-leak-kinds=all \
         --suppressions=.ignore_readline \
         -q \
         ./minishell