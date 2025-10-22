TARGET := PmergeMe

CXX := c++

STD := -std=c++98

BUILD := build

CXXFLAGS := -Wall -Wextra -Werror $(STD) 

RM := rm -rf

SRC := main.cpp

OBJ := $(SRC:%.cpp=$(BUILD)/%.o)

DEPS := $(OBJ:%.o=%.d)

# Default build type: release
MODE ?= release

# === MODE CONFIG ===
ifeq ($(MODE),debug)
    CXXFLAGS += -DDEBUG=1
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

$(BUILD)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

debug:
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -DDEBUG=1" all

clean:
	$(RM) $(BUILD)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

.PHONY: all clean fclean re debug

-include $(DEPS)