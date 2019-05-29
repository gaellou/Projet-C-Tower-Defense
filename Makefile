CC = gcc
CFLAGS = -Wall  -g
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lm -lSDL_ttf
APP_BIN = itd

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = -I/usr/X11R6/include -I include
BIN_PATH = bin
LIB_PATH = lib

SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.c')
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o, $(SRC_FILES))

all: $(APP_BIN)

$(APP_BIN): $(OBJ_FILES)
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(APP_BIN) $(OBJ_FILES) $(LDFLAGS)
	@echo "--------------------------------------------------------------"
	@echo "       To start the program please write : bin/$(APP_BIN)     "
	@echo "--------------------------------------------------------------"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)

clean:
	rm $(OBJ_FILES) $(BIN_PATH)/$(APP_BIN)
	@echo "--------------------------------------------------------------"
	@echo "                 Clean bin folder and objects                 "
	@echo "--------------------------------------------------------------"

tar: clean
	tar -pvczf TowerDefense.tar.gz ./*
	@echo "------------------------------------------------------------------"
	@echo "  Creation of a compressed version tar.gz : TowerDefense   "
	@echo "------------------------------------------------------------------"
