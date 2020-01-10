# Build for Linux/macOS
build:
	mkdir build; \
	cd build; \
	qmake ../src/GMT-GUI.pro; \
	make -j

# Package for macOS
macos_package: build
	cd build; \
	macdeployqt GMT-GUI.app; \
	zip -r GMT-GUI.app.zip GMT-GUI.app

clean:
	rm -r build
