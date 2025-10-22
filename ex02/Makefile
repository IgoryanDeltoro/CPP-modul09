TARGET := PmergeMe

CXX := c++

STD := -std=c++98

BUILD := build

CXXFLAGS := -Wall -Wextra -Werror $(STD)

RM := rm -rf

SRC := main.cpp

OBJ := $(SRC:%.cpp=$(BUILD)/%.o)

DEPS := $(OBJ:%.o=%.d)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

$(BUILD)/%.o: %.cpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

debug:
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -g -D DEBUG=1"

clear:
	$(RM) $(BUILD)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

.PHONY: all clean fclean re debug

-include $(DEPS)