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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Action.o \
	${OBJECTDIR}/ActionDatabase.o \
	${OBJECTDIR}/GtkBoursoramaActionWindow.o \
	${OBJECTDIR}/GtkBoursoramaApp.o \
	${OBJECTDIR}/GtkBoursoramaAppWindow.o \
	${OBJECTDIR}/GtkColoredCellRenderer.o \
	${OBJECTDIR}/download.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/parser.o


# C Compiler Flags
CFLAGS=`pkg-config --cflags --libs glib-2.0 gtk+-3.0`  

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boursorama

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boursorama: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boursorama ${OBJECTFILES} ${LDLIBSOPTIONS} -lcurl `pkg-config --cflags --libs glib-2.0 gtk+-3.0` 

${OBJECTDIR}/Action.o: Action.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Action.o Action.c

${OBJECTDIR}/ActionDatabase.o: ActionDatabase.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ActionDatabase.o ActionDatabase.c

${OBJECTDIR}/GtkBoursoramaActionWindow.o: GtkBoursoramaActionWindow.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GtkBoursoramaActionWindow.o GtkBoursoramaActionWindow.c

${OBJECTDIR}/GtkBoursoramaApp.o: GtkBoursoramaApp.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GtkBoursoramaApp.o GtkBoursoramaApp.c

${OBJECTDIR}/GtkBoursoramaAppWindow.o: GtkBoursoramaAppWindow.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GtkBoursoramaAppWindow.o GtkBoursoramaAppWindow.c

${OBJECTDIR}/GtkColoredCellRenderer.o: GtkColoredCellRenderer.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GtkColoredCellRenderer.o GtkColoredCellRenderer.c

${OBJECTDIR}/download.o: download.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/download.o download.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/parser.o: parser.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser.o parser.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/boursorama

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
