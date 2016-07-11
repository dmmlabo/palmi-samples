CC = arm-linux-gnueabi-gcc
GCC = arm-linux-gnueabi-gcc
GXX = arm-linux-gnueabi-g++
CXX = arm-linux-gnueabi-g++

OUTPUT_DIR = .

MOD_NAME = SpcPocoConfigurationSample
MOD_LIB = $(OUTPUT_DIR)/$(MOD_NAME)
MOD_SRC =    SpcBaseCode.cpp
MOD_OBJ = $(MOD_SRC:.cpp=.o)

INC_PATH = -I./ 
CFLAGS = -Wall -c -Wno-deprecated 

LFLAGS = -Wl 
LIB_PATH = -L. -L/usr/local/lib 
LIB_FILE = -lspc2 -lpthread -lspcif -lPocoFoundation -lPocoUtil

all:release

release: CFLAGS += -O3
release: $(MOD_LIB)

debug: CFLAGS += -g
debug: $(MOD_LIB)

$(MOD_LIB):$(MOD_OBJ)
	$(CXX) $(LFLAGS) -o $@ $(MOD_OBJ) $(LIB_PATH) $(LIB_FILE)

.cpp.o:
	$(CXX) $(CFLAGS) $(INC_PATH) -MMD -MP -o"$@" "$<" 

.c.o:
	$(CC) $(CFLAGS) $(INC_PATH) -MMD -MP -o"$@" "$<" 

clean:
	rm -f $(MOD_OBJ) $(MOD_LIB)
