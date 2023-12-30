.PHONY: all
all: build/main

build/%.o: src/%.c
	mkdir -p build
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf build
