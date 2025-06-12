# leafCount

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

all: testLeafCount

testLeafCount: testLeafCount.c leafCount.c BSTree.c
	$(CC) $(CFLAGS) -o testLeafCount testLeafCount.c leafCount.c BSTree.c

clean:
	rm -f testLeafCount

