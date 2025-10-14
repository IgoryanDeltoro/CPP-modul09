TARGET := RPN
CXX := c++
STD := -std=c++98
CFLAGS := -Wall -Wextra -Werror $(STD)
RM := rm -fr
BUILD := build
SRC := main.cpp RPN.cpp
OBJ := $(SRC:%.cpp=$(BUILD)/%.o)
DEPS := $(OBJ:%.o=%.d)
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(TARGET)
$(BUILD)/%.o: %.cpp
	mkdir -p $(BUILD)
	$(CXX) $(CFLAGS) -MMD -MP -c $< -o $@
clean:
	$(RM) $(BUILD)
fclean: clean
	$(RM) $(TARGET)
re: fclean all
.PHONY: all clean fclean re
-include $(DEPS)