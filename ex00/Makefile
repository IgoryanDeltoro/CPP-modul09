TARGET := btc
CXX = c++
STD := -std=c++98
BUILD := ./build
CXXFLAGS := -Wall -Wextra -Werror $(STD)
RM := rm -fr
SRC := main.cpp BitcoinExchange.cpp
OBJ := $(SRC:%.cpp=$(BUILD)/%.o)
DEPS := $(OBJ:%.o=%.d)
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)
$(BUILD)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@
clean:
	$(RM) $(BUILD)
fclean: clean
	$(RM) $(TARGET)
re: fclean all
PHONY: all clean fclean re 
-include $(DEPS)