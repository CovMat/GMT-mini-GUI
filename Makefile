PROJDIR=$(CURDIR)

# Build out of source directory for Linux/macOS
build:
	mkdir -p build; \
	cd build; \
	qmake DESTDIR=${PROJDIR} ${PROJDIR}/src; \
	make -j

# Packaging for macOS
macos_package: build
	macdeployqt GMT-GUI.app; \
	zip -r GMT-GUI.app.zip GMT-GUI.app

# Packaging for Linux
linux_package: build
	mkdir -p package; \
	mv GMT-GUI package/; \
	linuxdeployqt package/GMT-GUI -no-copy-copyright-files -no-translations; \
	mv package GMT-GUI; \
	tar cvzf GMT-GUI_Linux-64bit.tar.gz GMT-GUI

clean:
	-rm -rf build
