# The name of the project
NAME = minitalk.a

VAL = valgrind
VALFLAGS = --leak-check=full --show-leak-kinds=all

# Makefile flags
MAKEFLAGS += --no-print-directory

# Libft
LIBFT = ./libft/
LIBFT_LIB = $(LIBFT)libft.a

SERVER = server
CLIENT = client

# A list of all .c files in the current directory
HDERS = minitalk.h
SRCS_SERVER = server.c
SRCS_CLIENT = client.c
SRCS_COMMON = utils.c

# A list of all .o files that correspond to the .c files
OBJS_SERVER = server.o
OBJS_CLIENT = client.o
OBJS_COMMON = utils.o

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
ARFLAGS = -rc
RM = rm -f

COLOREND = \033[0m
GREEN = \033[1;32m
RED = \e[1;31m
YELLOW = \e[1;33m
BLUE = \033[0;34m
CIAN = \e[7;36m

# The default target - builds the project
all: $(NAME) $(CLIENT) $(SERVER)

# A rule to build the project from the .o files
$(NAME): $(LIBFT_LIB) $(OBJS_COMMON)
	$(AR) $(ARFLAGS) $@ $(OBJS_COMMON)
	ranlib $@

$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(NAME) $(LIBFT_LIB) -o $(CLIENT)
# $(OBJS_CLIENT): $(SRCS_CLIENT)
# 	$(CC) $(CFLAGS) 

$(SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(NAME) $(LIBFT_LIB) -o $(SERVER)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Compile libft
$(LIBFT_LIB):
	@echo "$(CIAN)Compiling libft...$(BLUE)"
	make -C $(LIBFT) -f Makefile

# A rule to remove all .o files
clean:
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_COMMON)
	make -C $(LIBFT) clean
	@echo "$(CIAN)Objects cleaned$(COLOREND)"

# A rule to remove all .o files and the project
fclean: clean
	$(RM) $(NAME) $(CLIENT) $(SERVER)
	make -C $(LIBFT) fclean
	@echo "$(CIAN)Full clean$(COLOREND)"

# A rule to rebuild everything from scratch
re: fclean all

norme:
	@echo "$(CIAN)SOURCES$(COLOREND)"
	@for file in $(SRCS); do \
		norminette $$file | grep "OK!" > /dev/null; \
		if [ $$? -eq 0 ]; then \
			echo "$(GREEN)$$file: OK!$(COLOREND)"; \
		else \
			echo "$(RED)"; \
			norminette $$file; \
			echo "$(COLOREND)"; \
		fi \
	done
	@echo "$(CIAN)\nHEADERS$(COLOREND)"
	@for header in $(HDERS); do \
		norminette $$header | grep "OK!" > /dev/null; \
		if [ $$? -eq 0 ]; then \
			echo "$(GREEN)$$header: OK!$(COLOREND)"; \
		else \
			echo "$(RED)"; \
			norminette $$header; \
			echo "$(COLOREND)"; \
		fi \
	done

# A special rule to tell make that these targets aren't files
.PHONY: all fclean re clean run error
