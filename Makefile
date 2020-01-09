build:
	mkdir build; \
	cd build; \
	qmake ../src/GMT-GUI.pro; \
	make -j

clean:
	rm -r build
