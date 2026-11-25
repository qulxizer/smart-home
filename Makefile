.PHONY: build-run build run

build-run: build run

build:
	mkdir -p build/
	g++ main.cpp -o ./build/app

run:
	./build/app
