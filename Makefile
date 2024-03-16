#//= Colors =//#
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

NAME = philo

#NAME_BONUS = 

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

LIB_PROJECT = philo.a

INCLUDES = -I ./includes

#LIBRARIES =

#BONUS = 

LIB = ar rcs

SRCS =  

OBJS = $(SRCS:.c=.o)

#SRCS_BONUS =

#OBJS_BONUS = $(SRCS_BONUS:.c=.o)

$(NAME) :	$(OBJS) 
			@echo "$(MAGENTA)$(BOLD)Compiling Philosophers...$(RESET)"
			@$(LIB) $(MINISHELL) $(OBJS)
			@$(CC) $(CFLAGS) $(INCLUDES) $(LIB_PROJECT) -o $(NAME)
			@echo "$(CYAN)$(BOLD)Done$(RESET)"

$(OBJS):	src/%.o : src/%.c 
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
			@make -s -C $(LIBFT_PATH)
			@make bonus -s -C $(LIBFT_PATH)

all : $(NAME)

bonus : $(NAME_BONUS)

clean:
			@echo "$(RED)$(BOLD)Cleaning objects from Philosophers...$(RESET)"
			@rm -f $(OBJS) $(OBJS_BONUS)
			@echo "$(GREEN)$(BOLD)Done.$(RESET)"
			@make clean -s -C $(LIBFT_PATH)

fclean:
			@echo "$(RED)$(BOLD)Cleaning all files from Philosophers...$(RESET)"
			@rm -f $(NAME) $(OBJS) $(LIBFT) $(LIB_PROJECT)
			@echo "$(GREEN)$(BOLD)Done.$(RESET)"
			@make fclean -s -C $(LIBFT_PATH)

re : fclean all

mini : fclean all clean

.PHONY : all re fclean clean bonus mini