PROGS = pipeline reqrep pair pubsub survey bus

all: $(PROGS)

pipeline: pipeline.c
	gcc pipeline.c -o pipeline -lnanomsg

reqrep: reqrep.c
	gcc reqrep.c -o reqrep -lnanomsg

pair: pair.c
	gcc pair.c -o pair -lnanomsg

pubsub: pubsub.c
	gcc pubsub.c -o pubsub -lnanomsg

survey: survey.c
	gcc survey.c -o survey -lnanomsg

bus: bus.c
	gcc bus.c -o bus -lnanomsg

clean:
	rm -f ${PROGS} *.o

