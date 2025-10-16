TARGET := pmergeme
CXX := c++
STD := -std=c++98
BUILD := build
CFLAGS := -Wall -Wextra -Werror $(STD)
RM := rm -rf
SRC := main.cpp PmergeMe.cpp
OBJ := $(SRC:%.cpp=$(BUILD)/%.o)
DEPS := $(OBJ:%.o=%.d)
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CXX) $(FLAGS) $(OBJ) -o $(TARGET)
$(BUILD)/%.o: %.cpp
	mkdir -p $(BUILD)
	$(CXX) $(FLAGS) -MMD -MP -c $< -o $@
clear:
	$(RM) $(BUILD)
fclean: clean
	$(RM) $(TARGET)
re: fclean all
.PHONY: all clean fclean re
-include $(DEPS)