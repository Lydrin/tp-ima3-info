all: $(patsubst %.c,%,$(shell ls *.c))

%: %.c
	clang -Wall -Wextra $< -o $@

.PHONY: all clean

clean:
	rm *.exe
