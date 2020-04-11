RM := rm -rf

# All of the sources participating in the build are defined here
C_UPPER_SRCS := 
CXX_SRCS := 
C++_SRCS := 
OBJ_SRCS := 
CC_SRCS := 
ASM_SRCS := 
CPP_SRCS := 
C_SRCS := 
O_SRCS := 
S_UPPER_SRCS := 
CC_DEPS := 
C++_DEPS := 
EXECUTABLES := 
C_UPPER_DEPS := 
CXX_DEPS := 
OBJS := 
CPP_DEPS := 
C_DEPS :=

OPT_FLAGS = -fsigned-char		\
	-fno-omit-frame-pointer		\
	-fvar-tracking-assignments	\
	-fdiagnostics-show-option	\
	-frecord-gcc-switches		\
	-fdiagnostics-color=auto

OPTIMIZE := -O3
EXTRA_CFLAGS := 

WARNINGS = ${WERROR}		        \
	-Wstrict-prototypes		        \
	-Wextra				            \
	-Wno-sign-compare		        \
	-Wno-pointer-sign		        \
	-Wno-error=maybe-uninitialized	\
	-Wno-error=clobbered

#CFLAGS = $(WARNINGS) -rdynamic $(OPTIMIZE_FLAGS) $(OPT_FLAGS) $(EXTRA_CFLAGS)
CFLAGS :=

#LINKER_FLAGS = -rdynamic $(OPT_FLAGS)
LINKER_FLAGS :=

DEFINES :=

CPP_SRCS += $(sort $(wildcard *.cpp))

C_SRCS += $(sort $(wildcard *.c))
C_SRCS += ../mqtt/mqtt.c

C_OBJS = $(patsubst %.c,%.o,$(C_SRCS))
CXX_OBJS += $(patsubst %.cpp,%.o,$(CPP_SRCS))
C_DEPS = $(patsubst %.o,%.d,$(C_OBJS))
CXX_DEPS = $(patsubst %.o,%.d,$(CXX_OBJS))

# Each subdirectory must supply rules for building sources it contributes
%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ $(OPTIMIZE) -g3 -Wall $(CFLAGS) -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc $(OPTIMIZE) -g3 -Wall $(CFLAGS) -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

USER_OBJS :=
LIBS := -lrt -lpthread

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: dht11Subscriber

# Tool invocations
dht11Subscriber: $(C_OBJS) $(CXX_OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  $(LINKER_FLAGS) -o "dht11Subscriber" $(C_OBJS) $(CXX_OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES) $(C_OBJS) $(CXX_OBJS) $(C_DEPS) $(CXX_DEPS) dht11Subscriber
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
