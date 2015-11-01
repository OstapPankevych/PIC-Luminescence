#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Luminescence.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Luminescence.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Source/main.c ../Source/Usb/usb_descriptors.c ../Source/Usb/usb_device.c ../Source/Usb/usb_function_hid.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1728301206/main.o ${OBJECTDIR}/_ext/940237505/usb_descriptors.o ${OBJECTDIR}/_ext/940237505/usb_device.o ${OBJECTDIR}/_ext/940237505/usb_function_hid.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1728301206/main.o.d ${OBJECTDIR}/_ext/940237505/usb_descriptors.o.d ${OBJECTDIR}/_ext/940237505/usb_device.o.d ${OBJECTDIR}/_ext/940237505/usb_function_hid.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1728301206/main.o ${OBJECTDIR}/_ext/940237505/usb_descriptors.o ${OBJECTDIR}/_ext/940237505/usb_device.o ${OBJECTDIR}/_ext/940237505/usb_function_hid.o

# Source Files
SOURCEFILES=../Source/main.c ../Source/Usb/usb_descriptors.c ../Source/Usb/usb_device.c ../Source/Usb/usb_function_hid.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Luminescence.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4550
MP_PROCESSOR_OPTION_LD=18f4550
MP_LINKER_DEBUG_OPTION=-r=ROM@0x7DC0:0x7FFF -r=RAM@GPR:0x3F4:0x3FF -u_DEBUGSTACK
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1728301206/main.o: ../Source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1728301206" 
	@${RM} ${OBJECTDIR}/_ext/1728301206/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../Include" -I"../../../../../../Program Files (x86)/Microchip/mplabc18/v3.47/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/main.o   ../Source/main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/940237505/usb_descriptors.o: ../Source/Usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/940237505" 
	@${RM} ${OBJECTDIR}/_ext/940237505/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/940237505/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../Include" -I"../../../../../../Program Files (x86)/Microchip/mplabc18/v3.47/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/940237505/usb_descriptors.o   ../Source/Usb/usb_descriptors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/940237505/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/940237505/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/940237505/usb_device.o: ../Source/Usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/940237505" 
	@${RM} ${OBJECTDIR}/_ext/940237505/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/940237505/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../Include" -I"../../../../../../Program Files (x86)/Microchip/mplabc18/v3.47/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/940237505/usb_device.o   ../Source/Usb/usb_device.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/940237505/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/940237505/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/940237505/usb_function_hid.o: ../Source/Usb/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/940237505" 
	@${RM} ${OBJECTDIR}/_ext/940237505/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/940237505/usb_function_hid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../Include" -I"../../../../../../Program Files (x86)/Microchip/mplabc18/v3.47/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/940237505/usb_function_hid.o   ../Source/Usb/usb_function_hid.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/940237505/usb_function_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/940237505/usb_function_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/_ext/1728301206/main.o: ../Source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1728301206" 
	@${RM} ${OBJECTDIR}/_ext/1728301206/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../Include" -I"../../../../../../Program Files (x86)/Microchip/mplabc18/v3.47/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/main.o   ../Source/main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/940237505/usb_descriptors.o: ../Source/Usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/940237505" 
	@${RM} ${OBJECTDIR}/_ext/940237505/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/940237505/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../Include" -I"../../../../../../Program Files (x86)/Microchip/mplabc18/v3.47/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/940237505/usb_descriptors.o   ../Source/Usb/usb_descriptors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/940237505/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/940237505/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/940237505/usb_device.o: ../Source/Usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/940237505" 
	@${RM} ${OBJECTDIR}/_ext/940237505/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/940237505/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../Include" -I"../../../../../../Program Files (x86)/Microchip/mplabc18/v3.47/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/940237505/usb_device.o   ../Source/Usb/usb_device.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/940237505/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/940237505/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/940237505/usb_function_hid.o: ../Source/Usb/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/940237505" 
	@${RM} ${OBJECTDIR}/_ext/940237505/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/940237505/usb_function_hid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../Include" -I"../../../../../../Program Files (x86)/Microchip/mplabc18/v3.47/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/940237505/usb_function_hid.o   ../Source/Usb/usb_function_hid.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/940237505/usb_function_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/940237505/usb_function_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Luminescence.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../rm18f4550\ -\ HID\ Bootload.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "..\rm18f4550 - HID Bootload.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"$(BINDIR_)$(TARGETBASE).map" -w -l"../../../../../../_MCC18/lib" -l"."  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/Luminescence.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/Luminescence.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../rm18f4550\ -\ HID\ Bootload.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "..\rm18f4550 - HID Bootload.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"$(BINDIR_)$(TARGETBASE).map" -w -l"../../../../../../_MCC18/lib" -l"."  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/Luminescence.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
