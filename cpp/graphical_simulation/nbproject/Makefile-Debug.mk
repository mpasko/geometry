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
<<<<<<< Updated upstream
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran.exe
AS=as.exe
=======
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as
>>>>>>> Stashed changes

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Figures_factory.o \
	${OBJECTDIR}/GSegment.o \
	${OBJECTDIR}/Display_properties.o \
	${OBJECTDIR}/GFigure.o \
	${OBJECTDIR}/OutputManager.o \
	${OBJECTDIR}/GPoint.o \
	${OBJECTDIR}/GPolygon.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lm
CXXFLAGS=-lm

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgraphical_simulation.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgraphical_simulation.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgraphical_simulation.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgraphical_simulation.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgraphical_simulation.a

${OBJECTDIR}/Figures_factory.o: Figures_factory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I../geometry -MMD -MP -MF $@.d -o ${OBJECTDIR}/Figures_factory.o Figures_factory.cpp

${OBJECTDIR}/GSegment.o: GSegment.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I../geometry -MMD -MP -MF $@.d -o ${OBJECTDIR}/GSegment.o GSegment.cpp

${OBJECTDIR}/Display_properties.o: Display_properties.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I../geometry -MMD -MP -MF $@.d -o ${OBJECTDIR}/Display_properties.o Display_properties.cpp

${OBJECTDIR}/GFigure.o: GFigure.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I../geometry -MMD -MP -MF $@.d -o ${OBJECTDIR}/GFigure.o GFigure.cpp

${OBJECTDIR}/OutputManager.o: OutputManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I../geometry -MMD -MP -MF $@.d -o ${OBJECTDIR}/OutputManager.o OutputManager.cpp

${OBJECTDIR}/GPoint.o: GPoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I../geometry -MMD -MP -MF $@.d -o ${OBJECTDIR}/GPoint.o GPoint.cpp

${OBJECTDIR}/GPolygon.o: GPolygon.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I../geometry -MMD -MP -MF $@.d -o ${OBJECTDIR}/GPolygon.o GPolygon.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgraphical_simulation.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
