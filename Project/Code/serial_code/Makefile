CC          := gcc
FLAGS       := -Wall -g
LIBS        := -lm
EXEC        := serial_main
DEP         := functions.h
SRC         := $(wildcard *.c)
LDFLAGS     := -L../simple-jpeg/ -lsimplejpeg


.PHONY : clean

# default: $(EXEC)
# all: default


OBJECTS     := $(patsubst *.c, *.o, $(wildcard *.c))
HEADERS     := $(wildcard *.h)


%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< $@

$(EXEC): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LIBS) -o $@ $(LDFLAGS)
	@echo $(EXEC) ready!


# tar :
#           tar cvzf IN3200_PE_15222.tar.gz IN3200_PE_15222


clean :
	@rm -f *.o $(EXEC)
	@echo "Clean-up complete!"
