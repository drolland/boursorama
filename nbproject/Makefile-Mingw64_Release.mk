#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Mingw64_Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/GtkBoursoramaApp.o \
	${OBJECTDIR}/GtkBoursoramaAppWindow.o \
	${OBJECTDIR}/GtkColoredCellRenderer.o \
	${OBJECTDIR}/action.o \
	${OBJECTDIR}/download.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/parser.o


# C Compiler Flags
CFLAGS=`pkgconf --cflags --libs glib-2.0 gtk+-3.0`  

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../../../../msys64/usr/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boursorama.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boursorama.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boursorama ${OBJECTFILES} ${LDLIBSOPTIONS} -lcurl -lgtk-3 -lgdk-3 -lgdi32 -limm32 -lshell32 -lole32 -Wl,-luuid -lwinmm -ldwmapi -lz -lpangowin32-1.0 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -L/mingw64/lib -lglib-2.0 -lintl

${OBJECTDIR}/GtkBoursoramaApp.o: GtkBoursoramaApp.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../../../../../msys64/mingw64/include -I../../../../../msys64/mingw64/include/gtk-3.0 -I../../../../../msys64/mingw64/include/glib-2.0 -I../../../../../msys64/mingw64/lib/glib-2.0/include -I../../../../../msys64/mingw64/include/pango-1.0 -I../../../../../msys64/mingw64/include/cairo -I../../../../../msys64/mingw64/include/gdk-pixbuf-2.0 -I../../../../../msys64/mingw64/include/pixman-1 -I../../../../../msys64/mingw64/include/freetype2 -I../../../../../msys64/mingw64/include/harfbuzz -I../../../../../msys64/mingw64/include/libpng16 -I../../../../../msys64/mingw64/include/atk-1.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GtkBoursoramaApp.o GtkBoursoramaApp.c

${OBJECTDIR}/GtkBoursoramaAppWindow.o: GtkBoursoramaAppWindow.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../../../../../msys64/mingw64/include -I../../../../../msys64/mingw64/include/gtk-3.0 -I../../../../../msys64/mingw64/include/glib-2.0 -I../../../../../msys64/mingw64/lib/glib-2.0/include -I../../../../../msys64/mingw64/include/pango-1.0 -I../../../../../msys64/mingw64/include/cairo -I../../../../../msys64/mingw64/include/gdk-pixbuf-2.0 -I../../../../../msys64/mingw64/include/pixman-1 -I../../../../../msys64/mingw64/include/freetype2 -I../../../../../msys64/mingw64/include/harfbuzz -I../../../../../msys64/mingw64/include/libpng16 -I../../../../../msys64/mingw64/include/atk-1.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GtkBoursoramaAppWindow.o GtkBoursoramaAppWindow.c

${OBJECTDIR}/GtkColoredCellRenderer.o: GtkColoredCellRenderer.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../../../../../msys64/mingw64/include -I../../../../../msys64/mingw64/include/gtk-3.0 -I../../../../../msys64/mingw64/include/glib-2.0 -I../../../../../msys64/mingw64/lib/glib-2.0/include -I../../../../../msys64/mingw64/include/pango-1.0 -I../../../../../msys64/mingw64/include/cairo -I../../../../../msys64/mingw64/include/gdk-pixbuf-2.0 -I../../../../../msys64/mingw64/include/pixman-1 -I../../../../../msys64/mingw64/include/freetype2 -I../../../../../msys64/mingw64/include/harfbuzz -I../../../../../msys64/mingw64/include/libpng16 -I../../../../../msys64/mingw64/include/atk-1.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GtkColoredCellRenderer.o GtkColoredCellRenderer.c

${OBJECTDIR}/action.o: action.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../../../../../msys64/mingw64/include -I../../../../../msys64/mingw64/include/gtk-3.0 -I../../../../../msys64/mingw64/include/glib-2.0 -I../../../../../msys64/mingw64/lib/glib-2.0/include -I../../../../../msys64/mingw64/include/pango-1.0 -I../../../../../msys64/mingw64/include/cairo -I../../../../../msys64/mingw64/include/gdk-pixbuf-2.0 -I../../../../../msys64/mingw64/include/pixman-1 -I../../../../../msys64/mingw64/include/freetype2 -I../../../../../msys64/mingw64/include/harfbuzz -I../../../../../msys64/mingw64/include/libpng16 -I../../../../../msys64/mingw64/include/atk-1.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/action.o action.c

${OBJECTDIR}/download.o: download.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../../../../../msys64/mingw64/include -I../../../../../msys64/mingw64/include/gtk-3.0 -I../../../../../msys64/mingw64/include/glib-2.0 -I../../../../../msys64/mingw64/lib/glib-2.0/include -I../../../../../msys64/mingw64/include/pango-1.0 -I../../../../../msys64/mingw64/include/cairo -I../../../../../msys64/mingw64/include/gdk-pixbuf-2.0 -I../../../../../msys64/mingw64/include/pixman-1 -I../../../../../msys64/mingw64/include/freetype2 -I../../../../../msys64/mingw64/include/harfbuzz -I../../../../../msys64/mingw64/include/libpng16 -I../../../../../msys64/mingw64/include/atk-1.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/download.o download.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../../../../../msys64/mingw64/include -I../../../../../msys64/mingw64/include/gtk-3.0 -I../../../../../msys64/mingw64/include/glib-2.0 -I../../../../../msys64/mingw64/lib/glib-2.0/include -I../../../../../msys64/mingw64/include/pango-1.0 -I../../../../../msys64/mingw64/include/cairo -I../../../../../msys64/mingw64/include/gdk-pixbuf-2.0 -I../../../../../msys64/mingw64/include/pixman-1 -I../../../../../msys64/mingw64/include/freetype2 -I../../../../../msys64/mingw64/include/harfbuzz -I../../../../../msys64/mingw64/include/libpng16 -I../../../../../msys64/mingw64/include/atk-1.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/parser.o: parser.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../../../../../msys64/mingw64/include -I../../../../../msys64/mingw64/include/gtk-3.0 -I../../../../../msys64/mingw64/include/glib-2.0 -I../../../../../msys64/mingw64/lib/glib-2.0/include -I../../../../../msys64/mingw64/include/pango-1.0 -I../../../../../msys64/mingw64/include/cairo -I../../../../../msys64/mingw64/include/gdk-pixbuf-2.0 -I../../../../../msys64/mingw64/include/pixman-1 -I../../../../../msys64/mingw64/include/freetype2 -I../../../../../msys64/mingw64/include/harfbuzz -I../../../../../msys64/mingw64/include/libpng16 -I../../../../../msys64/mingw64/include/atk-1.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser.o parser.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boursorama.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
