ifdef OS
  OS := $(strip $(OS))
else
  OS := $(strip $(shell uname))
endif

BINGERNAME = gerenciador
BINGAMENAME = undertale_trunfo
BUILDPATH = build
BINGAMEPATH = build/bin

ifeq ($(OS),Windows_NT)

    BINGER = $(BUILDPATH)/$(BINGERNAME).exe
    BIN = $(BINGAMEPATH)/$(BINGAMENAME).exe

    RMGER = rm -f $(BINGER)
    RM = rm -f $(BIN)
    EXECGAME = cd $(BUILDPATH) && ./bin/$(BINGAMENAME).exe john_doe 1
    EXEGER = cd $(BUILDPATH) && ./$(BINGERNAME).exe
    INCLUDE = -I./game/include/ -L./game/libwin -Wl,-rpath=./game/libwin
    EXTRA_FLAGS = -Wall -Wextra -std=c99 -Wno-missing-braces -lraylib -lm -lopengl32 -lgdi32 -lwinmm -Wno-unused-parameter

else

    BINGER = $(BUILDPATH)/$(BINGERNAME)
    BIN = $(BINGAMEPATH)/$(BINGAMENAME)

    RMGER = rm -f $(BINGER)
    RM = rm -f $(BIN)

    EXECGAME = cd $(BUILDPATH) && ./bin/$(BINGAMENAME) anon 0
    EXEGER = cd $(BUILDPATH) && $(BINGERNAME)
    
    INCLUDE = -I./game/include/ -L./game/lib
    EXTRA_FLAGS = -Wall -Wextra -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wno-unused-parameter -std=c2x -Wl,-rpath=./game/lib
endif

SRCGER = $(wildcard gerenciador/*.c) $(wildcard gerenciador/src/*.c)
SRCGAME = $(wildcard game/*.c) $(wildcard game/src/*.c)

all: $(BIN) $(BINGER)

$(BIN): $(SRCGAME)
	gcc $(SRCGAME) -I./game/include $(INCLUDE) $(EXTRA_FLAGS) -o $(BIN)
	echo "Compilado: $(BIN)"

$(BINGER): $(SRCGER)
	gcc $(SRCGER) -I./gerenciador/includes $(INCLUDE) $(EXTRA_FLAGS) -o $(BINGER)
	echo "Compilado: $(BINGER)"

run-ger:
	$(EXEGER)

run-game:
	$(EXECGAME)

clean:
	$(RM)
	$(RMGER)

clean-ger:
	$(RMGER)

clean-game:
	$(RM)