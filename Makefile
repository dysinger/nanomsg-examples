PROGS = pipeline reqrep pair pubsub survey bus

SRC_PATH = src/
BIN_PATH = bin/

# same as PROGS, but with a leading BIN_PATH
PROG_TARGETS = $(patsubst %,$(BIN_PATH)/%,$(PROGS))

LDFLAGS = -lnanomsg

all: $(BIN_PATH) $(PROG_TARGETS)

# make the bin directory if it is not present
$(BIN_PATH):
	mkdir -p $(BIN_PATH)

clean:
	rm -rf $(BIN_PATH)

# macro to compile a c program into corresponding program
$(BIN_PATH)%: $(SRC_PATH)%.c
	gcc $< -o $@ $(LDFLAGS)
