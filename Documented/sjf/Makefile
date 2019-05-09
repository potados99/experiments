#################################################

# Makefile boilerplate version 0.1.0 (20190416)

TARGET_INITIAL	:= sjf
TARGET		:= $(TARGET_INITIAL)

CC		:= gcc
CFLAGS		:= -Wall
LIB		:=

SRC_DIR		:= src
INC_DIR		:= include
RES_DIR		:= res

TARGET_DIR	:= bin
OBJ_DIR		:= build
SRC_EXT		:= c
OBJ_EXT		:= o

#################################################

## DO NOT EDIT BELOW ##

SOURCES := $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
OBJECTS := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SOURCES:.$(SRC_EXT)=.$(OBJ_EXT)))

all: directories resources $(TARGET)
	@echo [$@]
	@echo "All done."

directories:
	@echo [$@]
	@mkdir -p $(TARGET_DIR) $(OBJ_DIR)

resources:
	@echo [$@]
	@cp $(RES_DIR)/* $(TARGET_DIR)

clean:
	@echo [$@]
	rm -rf $(TARGET_DIR) $(OBJ_DIR)
	rm $(TARGET)

# LINK
$(TARGET): $(OBJECTS)
	@echo [$@]
	$(LINK.c) -o $(TARGET_DIR)/$(TARGET) $^ $(LIB)
	@ln -sf $(TARGET_DIR)/$(TARGET) ./

# COMPILE
$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT)
	@echo [$@]
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INC_DIR)
