################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FlatBloofiTest.c \
../src/FlatBloofiTestInteri.c \
../src/TestFlatBloomFilter.c \
../src/bitset.c \
../src/bloom.c \
../src/flatBloofi.c \
../src/hasher.c \
../src/hashtable.c \
../src/list.c \
../src/provaSingolaTest.c 

OBJS += \
./src/FlatBloofiTest.o \
./src/FlatBloofiTestInteri.o \
./src/TestFlatBloomFilter.o \
./src/bitset.o \
./src/bloom.o \
./src/flatBloofi.o \
./src/hasher.o \
./src/hashtable.o \
./src/list.o \
./src/provaSingolaTest.o 

C_DEPS += \
./src/FlatBloofiTest.d \
./src/FlatBloofiTestInteri.d \
./src/TestFlatBloomFilter.d \
./src/bitset.d \
./src/bloom.d \
./src/flatBloofi.d \
./src/hasher.d \
./src/hashtable.d \
./src/list.d \
./src/provaSingolaTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


