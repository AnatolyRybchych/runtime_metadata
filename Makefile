
objects	:= obj/main.o
objects	+= obj/metadata.o
objects	+= obj/metadata_symbol.o

build: $(objects)
	gcc -Iinclude/ -o run.exe $^

obj/%.o: src/%.c
	gcc -c -Iinclude/ -o $@ $<

run: build
	./run.exe