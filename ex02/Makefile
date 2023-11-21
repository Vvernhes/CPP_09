##################
##	VARIABLES	##
##################

NAME      = PmergeMe
VPATH     = SRC
OBJDIR    = OBJ
INCLDIR   = INCL

SRCS      = main.cpp PmergeMe.cpp 

OBJ       = $(SRCS:%.cpp=$(OBJDIR)/%.o)

CXX       = c++
CXXFLAGS  = -Wall -Werror -Wextra -std=c++98
INCFLAGS  = -I./$(INCLDIR)
RM        = rm -rf

##################
##    RULES     ##
##################

$(OBJDIR)/%.o:	%.cpp | $(OBJDIR)
		$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
		$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR):
		mkdir $(OBJDIR)

all:	$(NAME)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME) $(OBJDIR)

re:	fclean all

.PHONY:	all clean fclean re