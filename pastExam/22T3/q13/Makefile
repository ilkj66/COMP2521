# closeFollowers

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Wvla -Werror -gdwarf-4

########################################################################

.PHONY: asan msan nosan

asan: CFLAGS += -fsanitize=address,leak,undefined
asan: all

msan: CFLAGS += -fsanitize=memory,undefined -fsanitize-memory-track-origins
msan: all

nosan: all

########################################################################

all: testCloseFollowers

testCloseFollowers: testCloseFollowers.c closeFollowers.c Graph.c
	$(CC) $(CFLAGS) -o testCloseFollowers testCloseFollowers.c closeFollowers.c Graph.c

clean:
	rm -f testCloseFollowers

