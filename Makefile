PROGS = pipeline reqrep pair pubsub survey bus

SRC_PATH = src/
BIN_PATH = bin/

LDFLAGS = -lnanomsg

all: prepare $(PROGS)

prepare:
	@if [ ! -f $(BIN_PATH) ] ;\
		then mkdir -p $(BIN_PATH) ;\
		echo "Create folder for binaries: $(shell pwd)/$(BIN_PATH)" ;\
	fi

pipeline: $(SRC_PATH)pipeline.c
	gcc $(SRC_PATH)pipeline.c -o $(BIN_PATH)pipeline $(LDFLAGS)

reqrep: $(SRC_PATH)reqrep.c
	gcc $(SRC_PATH)reqrep.c -o $(BIN_PATH)reqrep $(LDFLAGS)

pair: $(SRC_PATH)pair.c
	gcc $(SRC_PATH)pair.c -o $(BIN_PATH)pair $(LDFLAGS)

pubsub: $(SRC_PATH)pubsub.c
	gcc $(SRC_PATH)pubsub.c -o $(BIN_PATH)pubsub $(LDFLAGS)

survey: $(SRC_PATH)survey.c
	gcc $(SRC_PATH)survey.c -o $(BIN_PATH)survey $(LDFLAGS)

bus: $(SRC_PATH)bus.c
	gcc $(SRC_PATH)bus.c -o $(BIN_PATH)bus $(LDFLAGS)

clean:
	rm -rf $(BIN_PATH)

