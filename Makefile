.PHONY: cmake
cmake:
	cmake -B build
	cmake --build build -j 8

clean:
	rm -rf .cache/ 
	rm -rf build/
	rm -rf vector/build/
	rm -rf ring-buffer/build/

