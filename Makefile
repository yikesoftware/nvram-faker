TRUNK ?=.
include $(TRUNK)/arch.mk

AR?=ar

CFLAGS+=-ggdb
CFLAGS+= -DINI_MAX_LINE=2000
CFLAGS+= -DINI_USE_STACK=0
export CFLAGS
EXE=nvram_faker_exe
EXE_OBJ=nvram_faker_main.o
OBJS=nvram-faker.o dictionary.o
LIB=libnvram-faker.so

all:$(LIB)

exe: export CFLAGS+=-DNVRAM_EXE -DDEBUG
exe: export CFLAGS+=-DICT_FILE_PATH=\"./nvram.ini\"
exe: $(EXE)

%.o:%.c
	$(CC) -Wall $(INCLUDES) $(CFLAGS) -fPIC -c -o $@ $<

$(LIB): $(OBJS)
	$(CC) -shared -o $@ $^ -Wl,-nostdlib

nvram_faker_exe:$(EXE_OBJ) $(OBJS)
	$(CC) -Wall -o $@ $^ 

clean:
	-rm *.o
	-rm *.so
	-rm $(EXE)


