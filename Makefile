NAME		  := minishell
.DEFAULT_GOAL := ceedling

# --------------------------------- includes --------------------------------- #

# INCS		= ./include \
# 				./include/libft/include

# LIB			:= ft
# LIB_FT		:= include/libft/libft.a

# BUILD_DIR	:= .build

# ---------------------------------------------------------------------------- #
#                                 source files                                 #
# ---------------------------------------------------------------------------- #

# VPATH		:= src/

# SRC			:= $(NAME).c

# SRCS		:= $(SRC)

# ---------------------------------------------------------------------------- #
#                             compilation arguments                            #
# ---------------------------------------------------------------------------- #

# OBJS		:= $(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))
# DEPS		:= $(OBJS:.o=.d)

# CC			:= clang
# CFLAGS		?= -g3 -Wall -Wextra -Werror#-Wpedantic
# CPPFLAGS	:= $(addprefix -I,$(INCS)) -MMD -MP
# LDFLAGS		= $(addprefix -L, $(dir $(LIB_FT)))
# LDLIB		:= $(addprefix -l, $(LIB))

MAKEFLAGS	+= --no-print-directory --silent

ifeq ($(uname -s),Darwin)
DONE		= printf "\033[0;32m\xE2\x9C\x93\033[0m "
DONE_NL		= printf "\033[0;32m\xE2\x9C\x93\n\033[0m"
else
DONE		= printf "\033[0;32m✓\033[0m "
DONE_NL		= printf "\033[0;32m✓\033[0m\n\n"
endif

# ---------------------------------------------------------------------------- #
#                             building the program                             #
# ---------------------------------------------------------------------------- #
ceedling: 
	cd include/libft && make ceedling
	ceedling release
# bonus: all
# all: $(NAME)

# $(LIB_FT):
# 	$(MAKE) -C $(@D) -B

# $(NAME): $(OBJS) $(LIB_FT)
# 	$(info creating $(NAME) executable)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIB_FT) $(CPPFLAGS) $(LDLIB) $(LDFLAGS) -o $(NAME)
# 	$(DONE_NL)

# $(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
# 	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< && $(DONE)
# 	echo $(notdir $<)
# info $($<)
$(BUILD_DIR):
	mkdir -p .build

# ---------------------------------------------------------------------------- #
#                                     rules                                    #
# ---------------------------------------------------------------------------- #

clean:
	$(info Cleaning...)
	rm -rf include/libft/build/*
	$(DONE_NL)

fclean: clean
	rm -rf build/*

re:
	$(MAKE) fclean
	$(MAKE) ceedling

# ----------------------------- additional rules ----------------------------- #
run: $(ceedling release)
	./minishell
.PHONY: run update upgrade re
# .SILENT:
-include $(DEPS)
