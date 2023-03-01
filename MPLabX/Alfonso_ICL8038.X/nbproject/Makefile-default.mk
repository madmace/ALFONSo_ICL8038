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
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Alfonso_ICL8038.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Alfonso_ICL8038.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=ccp/CCPLib.c ccp/CCP2.c I2C/PCF8574/PCF8574.c I2C/I2CLib.c spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.c spi/MCP23S08/MCP23S08.c spi/MCP23S17/MCP23S17.c SPI/MCP425X/MCP425X.c SPI/MCP42XXX/MCP42XXX.c SPI/SPILib.c system/system.c system/usb_events.c usb/usb_device.c usb/usb_device_cdc.c usb/usb_descriptors.c utilities/utilities.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/ccp/CCPLib.p1 ${OBJECTDIR}/ccp/CCP2.p1 ${OBJECTDIR}/I2C/PCF8574/PCF8574.p1 ${OBJECTDIR}/I2C/I2CLib.p1 ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1 ${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1 ${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1 ${OBJECTDIR}/SPI/MCP425X/MCP425X.p1 ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1 ${OBJECTDIR}/SPI/SPILib.p1 ${OBJECTDIR}/system/system.p1 ${OBJECTDIR}/system/usb_events.p1 ${OBJECTDIR}/usb/usb_device.p1 ${OBJECTDIR}/usb/usb_device_cdc.p1 ${OBJECTDIR}/usb/usb_descriptors.p1 ${OBJECTDIR}/utilities/utilities.p1 ${OBJECTDIR}/main.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/ccp/CCPLib.p1.d ${OBJECTDIR}/ccp/CCP2.p1.d ${OBJECTDIR}/I2C/PCF8574/PCF8574.p1.d ${OBJECTDIR}/I2C/I2CLib.p1.d ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1.d ${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1.d ${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1.d ${OBJECTDIR}/SPI/MCP425X/MCP425X.p1.d ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1.d ${OBJECTDIR}/SPI/SPILib.p1.d ${OBJECTDIR}/system/system.p1.d ${OBJECTDIR}/system/usb_events.p1.d ${OBJECTDIR}/usb/usb_device.p1.d ${OBJECTDIR}/usb/usb_device_cdc.p1.d ${OBJECTDIR}/usb/usb_descriptors.p1.d ${OBJECTDIR}/utilities/utilities.p1.d ${OBJECTDIR}/main.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/ccp/CCPLib.p1 ${OBJECTDIR}/ccp/CCP2.p1 ${OBJECTDIR}/I2C/PCF8574/PCF8574.p1 ${OBJECTDIR}/I2C/I2CLib.p1 ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1 ${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1 ${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1 ${OBJECTDIR}/SPI/MCP425X/MCP425X.p1 ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1 ${OBJECTDIR}/SPI/SPILib.p1 ${OBJECTDIR}/system/system.p1 ${OBJECTDIR}/system/usb_events.p1 ${OBJECTDIR}/usb/usb_device.p1 ${OBJECTDIR}/usb/usb_device_cdc.p1 ${OBJECTDIR}/usb/usb_descriptors.p1 ${OBJECTDIR}/utilities/utilities.p1 ${OBJECTDIR}/main.p1

# Source Files
SOURCEFILES=ccp/CCPLib.c ccp/CCP2.c I2C/PCF8574/PCF8574.c I2C/I2CLib.c spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.c spi/MCP23S08/MCP23S08.c spi/MCP23S17/MCP23S17.c SPI/MCP425X/MCP425X.c SPI/MCP42XXX/MCP42XXX.c SPI/SPILib.c system/system.c system/usb_events.c usb/usb_device.c usb/usb_device_cdc.c usb/usb_descriptors.c utilities/utilities.c main.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Alfonso_ICL8038.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4550
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/ccp/CCPLib.p1: ccp/CCPLib.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ccp" 
	@${RM} ${OBJECTDIR}/ccp/CCPLib.p1.d 
	@${RM} ${OBJECTDIR}/ccp/CCPLib.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ccp/CCPLib.p1 ccp/CCPLib.c 
	@-${MV} ${OBJECTDIR}/ccp/CCPLib.d ${OBJECTDIR}/ccp/CCPLib.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ccp/CCPLib.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ccp/CCP2.p1: ccp/CCP2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ccp" 
	@${RM} ${OBJECTDIR}/ccp/CCP2.p1.d 
	@${RM} ${OBJECTDIR}/ccp/CCP2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ccp/CCP2.p1 ccp/CCP2.c 
	@-${MV} ${OBJECTDIR}/ccp/CCP2.d ${OBJECTDIR}/ccp/CCP2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ccp/CCP2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/I2C/PCF8574/PCF8574.p1: I2C/PCF8574/PCF8574.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/I2C/PCF8574" 
	@${RM} ${OBJECTDIR}/I2C/PCF8574/PCF8574.p1.d 
	@${RM} ${OBJECTDIR}/I2C/PCF8574/PCF8574.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/I2C/PCF8574/PCF8574.p1 I2C/PCF8574/PCF8574.c 
	@-${MV} ${OBJECTDIR}/I2C/PCF8574/PCF8574.d ${OBJECTDIR}/I2C/PCF8574/PCF8574.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/I2C/PCF8574/PCF8574.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/I2C/I2CLib.p1: I2C/I2CLib.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/I2C" 
	@${RM} ${OBJECTDIR}/I2C/I2CLib.p1.d 
	@${RM} ${OBJECTDIR}/I2C/I2CLib.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/I2C/I2CLib.p1 I2C/I2CLib.c 
	@-${MV} ${OBJECTDIR}/I2C/I2CLib.d ${OBJECTDIR}/I2C/I2CLib.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/I2C/I2CLib.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1: spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08" 
	@${RM} ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1.d 
	@${RM} ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1 spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.c 
	@-${MV} ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.d ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1: spi/MCP23S08/MCP23S08.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/spi/MCP23S08" 
	@${RM} ${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1.d 
	@${RM} ${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1 spi/MCP23S08/MCP23S08.c 
	@-${MV} ${OBJECTDIR}/spi/MCP23S08/MCP23S08.d ${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1: spi/MCP23S17/MCP23S17.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/spi/MCP23S17" 
	@${RM} ${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1.d 
	@${RM} ${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1 spi/MCP23S17/MCP23S17.c 
	@-${MV} ${OBJECTDIR}/spi/MCP23S17/MCP23S17.d ${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SPI/MCP425X/MCP425X.p1: SPI/MCP425X/MCP425X.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/SPI/MCP425X" 
	@${RM} ${OBJECTDIR}/SPI/MCP425X/MCP425X.p1.d 
	@${RM} ${OBJECTDIR}/SPI/MCP425X/MCP425X.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/SPI/MCP425X/MCP425X.p1 SPI/MCP425X/MCP425X.c 
	@-${MV} ${OBJECTDIR}/SPI/MCP425X/MCP425X.d ${OBJECTDIR}/SPI/MCP425X/MCP425X.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SPI/MCP425X/MCP425X.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1: SPI/MCP42XXX/MCP42XXX.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/SPI/MCP42XXX" 
	@${RM} ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1.d 
	@${RM} ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1 SPI/MCP42XXX/MCP42XXX.c 
	@-${MV} ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.d ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SPI/SPILib.p1: SPI/SPILib.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/SPI" 
	@${RM} ${OBJECTDIR}/SPI/SPILib.p1.d 
	@${RM} ${OBJECTDIR}/SPI/SPILib.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/SPI/SPILib.p1 SPI/SPILib.c 
	@-${MV} ${OBJECTDIR}/SPI/SPILib.d ${OBJECTDIR}/SPI/SPILib.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SPI/SPILib.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system/system.p1: system/system.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/system" 
	@${RM} ${OBJECTDIR}/system/system.p1.d 
	@${RM} ${OBJECTDIR}/system/system.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/system/system.p1 system/system.c 
	@-${MV} ${OBJECTDIR}/system/system.d ${OBJECTDIR}/system/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system/usb_events.p1: system/usb_events.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/system" 
	@${RM} ${OBJECTDIR}/system/usb_events.p1.d 
	@${RM} ${OBJECTDIR}/system/usb_events.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/system/usb_events.p1 system/usb_events.c 
	@-${MV} ${OBJECTDIR}/system/usb_events.d ${OBJECTDIR}/system/usb_events.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system/usb_events.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/usb_device.p1: usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb/usb_device.p1 usb/usb_device.c 
	@-${MV} ${OBJECTDIR}/usb/usb_device.d ${OBJECTDIR}/usb/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/usb_device_cdc.p1: usb/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device_cdc.p1.d 
	@${RM} ${OBJECTDIR}/usb/usb_device_cdc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb/usb_device_cdc.p1 usb/usb_device_cdc.c 
	@-${MV} ${OBJECTDIR}/usb/usb_device_cdc.d ${OBJECTDIR}/usb/usb_device_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/usb_device_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/usb_descriptors.p1: usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb/usb_descriptors.p1 usb/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/usb/usb_descriptors.d ${OBJECTDIR}/usb/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/utilities/utilities.p1: utilities/utilities.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/utilities" 
	@${RM} ${OBJECTDIR}/utilities/utilities.p1.d 
	@${RM} ${OBJECTDIR}/utilities/utilities.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/utilities/utilities.p1 utilities/utilities.c 
	@-${MV} ${OBJECTDIR}/utilities/utilities.d ${OBJECTDIR}/utilities/utilities.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/utilities/utilities.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/ccp/CCPLib.p1: ccp/CCPLib.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ccp" 
	@${RM} ${OBJECTDIR}/ccp/CCPLib.p1.d 
	@${RM} ${OBJECTDIR}/ccp/CCPLib.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ccp/CCPLib.p1 ccp/CCPLib.c 
	@-${MV} ${OBJECTDIR}/ccp/CCPLib.d ${OBJECTDIR}/ccp/CCPLib.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ccp/CCPLib.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ccp/CCP2.p1: ccp/CCP2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ccp" 
	@${RM} ${OBJECTDIR}/ccp/CCP2.p1.d 
	@${RM} ${OBJECTDIR}/ccp/CCP2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ccp/CCP2.p1 ccp/CCP2.c 
	@-${MV} ${OBJECTDIR}/ccp/CCP2.d ${OBJECTDIR}/ccp/CCP2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ccp/CCP2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/I2C/PCF8574/PCF8574.p1: I2C/PCF8574/PCF8574.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/I2C/PCF8574" 
	@${RM} ${OBJECTDIR}/I2C/PCF8574/PCF8574.p1.d 
	@${RM} ${OBJECTDIR}/I2C/PCF8574/PCF8574.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/I2C/PCF8574/PCF8574.p1 I2C/PCF8574/PCF8574.c 
	@-${MV} ${OBJECTDIR}/I2C/PCF8574/PCF8574.d ${OBJECTDIR}/I2C/PCF8574/PCF8574.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/I2C/PCF8574/PCF8574.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/I2C/I2CLib.p1: I2C/I2CLib.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/I2C" 
	@${RM} ${OBJECTDIR}/I2C/I2CLib.p1.d 
	@${RM} ${OBJECTDIR}/I2C/I2CLib.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/I2C/I2CLib.p1 I2C/I2CLib.c 
	@-${MV} ${OBJECTDIR}/I2C/I2CLib.d ${OBJECTDIR}/I2C/I2CLib.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/I2C/I2CLib.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1: spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08" 
	@${RM} ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1.d 
	@${RM} ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1 spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.c 
	@-${MV} ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.d ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/spi/MCP23S08/LCD44780_MCP23S08/LCD44780_MCP23S08.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1: spi/MCP23S08/MCP23S08.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/spi/MCP23S08" 
	@${RM} ${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1.d 
	@${RM} ${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1 spi/MCP23S08/MCP23S08.c 
	@-${MV} ${OBJECTDIR}/spi/MCP23S08/MCP23S08.d ${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/spi/MCP23S08/MCP23S08.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1: spi/MCP23S17/MCP23S17.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/spi/MCP23S17" 
	@${RM} ${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1.d 
	@${RM} ${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1 spi/MCP23S17/MCP23S17.c 
	@-${MV} ${OBJECTDIR}/spi/MCP23S17/MCP23S17.d ${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/spi/MCP23S17/MCP23S17.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SPI/MCP425X/MCP425X.p1: SPI/MCP425X/MCP425X.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/SPI/MCP425X" 
	@${RM} ${OBJECTDIR}/SPI/MCP425X/MCP425X.p1.d 
	@${RM} ${OBJECTDIR}/SPI/MCP425X/MCP425X.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/SPI/MCP425X/MCP425X.p1 SPI/MCP425X/MCP425X.c 
	@-${MV} ${OBJECTDIR}/SPI/MCP425X/MCP425X.d ${OBJECTDIR}/SPI/MCP425X/MCP425X.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SPI/MCP425X/MCP425X.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1: SPI/MCP42XXX/MCP42XXX.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/SPI/MCP42XXX" 
	@${RM} ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1.d 
	@${RM} ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1 SPI/MCP42XXX/MCP42XXX.c 
	@-${MV} ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.d ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SPI/MCP42XXX/MCP42XXX.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SPI/SPILib.p1: SPI/SPILib.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/SPI" 
	@${RM} ${OBJECTDIR}/SPI/SPILib.p1.d 
	@${RM} ${OBJECTDIR}/SPI/SPILib.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/SPI/SPILib.p1 SPI/SPILib.c 
	@-${MV} ${OBJECTDIR}/SPI/SPILib.d ${OBJECTDIR}/SPI/SPILib.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SPI/SPILib.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system/system.p1: system/system.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/system" 
	@${RM} ${OBJECTDIR}/system/system.p1.d 
	@${RM} ${OBJECTDIR}/system/system.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/system/system.p1 system/system.c 
	@-${MV} ${OBJECTDIR}/system/system.d ${OBJECTDIR}/system/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system/usb_events.p1: system/usb_events.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/system" 
	@${RM} ${OBJECTDIR}/system/usb_events.p1.d 
	@${RM} ${OBJECTDIR}/system/usb_events.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/system/usb_events.p1 system/usb_events.c 
	@-${MV} ${OBJECTDIR}/system/usb_events.d ${OBJECTDIR}/system/usb_events.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system/usb_events.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/usb_device.p1: usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb/usb_device.p1 usb/usb_device.c 
	@-${MV} ${OBJECTDIR}/usb/usb_device.d ${OBJECTDIR}/usb/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/usb_device_cdc.p1: usb/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device_cdc.p1.d 
	@${RM} ${OBJECTDIR}/usb/usb_device_cdc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb/usb_device_cdc.p1 usb/usb_device_cdc.c 
	@-${MV} ${OBJECTDIR}/usb/usb_device_cdc.d ${OBJECTDIR}/usb/usb_device_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/usb_device_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/usb_descriptors.p1: usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb/usb_descriptors.p1 usb/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/usb/usb_descriptors.d ${OBJECTDIR}/usb/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/utilities/utilities.p1: utilities/utilities.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/utilities" 
	@${RM} ${OBJECTDIR}/utilities/utilities.p1.d 
	@${RM} ${OBJECTDIR}/utilities/utilities.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/utilities/utilities.p1 utilities/utilities.c 
	@-${MV} ${OBJECTDIR}/utilities/utilities.d ${OBJECTDIR}/utilities/utilities.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/utilities/utilities.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Alfonso_ICL8038.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/Alfonso_ICL8038.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=pickit3  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -mrom=default,-7dc0-7fff -mram=default,-3f4-3ff,-f9c-f9c,-fd4-fd4,-fdb-fdf,-fe3-fe7,-feb-fef,-ffd-fff  $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/Alfonso_ICL8038.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/Alfonso_ICL8038.X.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/Alfonso_ICL8038.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/Alfonso_ICL8038.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"globals" -I"system" -I"usb" -I"spi" -I"ccp" -I"spi/MCP42XXX" -I"spi/MCP425X" -I"spi/MCP23S08" -I"spi/MCP23S08/LCD44780_MCP23S08" -I"spi/MCP23S17" -I"i2c" -I"i2c/PCF8574" -I"utilities" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/Alfonso_ICL8038.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
