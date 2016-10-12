CC = gcc

NAME = fractol

CFLAGS = -Wall -Wextra -Werror

INC = -I /usr/include/mlx.h -L/usr/local/lib -lmlx -framework OPENGL \
	  -framework AppKit

OBJDIR = obj/

HEADERDIR = .

SRCS = main.c				\
	   julia.c				\
	   mbrot.c				\
	   bs.c					\
	   el.c					\
	   draw.c

HEADER = fractal.h

OBJS = $(addprefix $(OBJDIR),$(subst .c,.o,$(SRCS)))

INCLUDES = -I libft/includes

define colorecho
      @tput setaf 14
      @echo $1
      @tput sgr0
endef

define colorecho2
      @tput setaf 2
      @echo $1
      @tput sgr0
endef

.PHONY: all clean fclean re proper libft

all: libft $(NAME) $(CUDA_NAME)

$(NAME): qme libft/libft.a $(OBJS) $(HEADER)
	@$(call colorecho,"Compiling program.")
	@$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME) $(INCLUDES) -L libft -lft
	@clear
	@$(call colorecho,"Done Compiling.")

libft:
	make -C libft

$(OBJS): | $(OBJDIR)

$(OBJDIR)%.o : %.cu $(HEADER)
	@$(call colorecho,"Compiling object.")
	$(NVCC) -c $(CUDA_CFLAGS) $< -o $@ $(INCLUDES)

$(OBJDIR)%.o : %.c $(HEADER)
	@$(call colorecho,"Compiling object.")
	@$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDES)

$(OBJDIR):
	@$(call colorecho,"Checking if objects folder needs to be made")
	@if [ ! -d "$(OBJDIR)" ]; then \
		mkdir $(OBJDIR);\
		fi

clean:
	@$(call colorecho,"Cleaning libft objects")
	@make clean -C libft
	@$(call colorecho,"Cleaning Objects")
	@rm -rf $(OBJS)
	@rm -rf $(OBJDIR)
	@$(call colorecho,"Done cleaning.")

fclean: clean
	@$(call colorecho,"Cleaning Libft")
	@rm -rf libft/libft.a
	@$(call colorecho,"Removing evecutable")
	@rm -rf $(NAME)
	@clear
	@$(call colorecho,"Done cleaning everything.")

proper: all clean

re: fclean all

format: qme norme me
	@$(call colorecho2,"All good!\n")

norme:
	@$(call colorecho2,"Norme:\n")
	@norminette $(SRCS)
	@norminette $(HEADER)

me: qme
	@$(call colorecho2,"Author:\n")
	cat -e author

qme:
	@rm -Rf author
	@whoami > author
