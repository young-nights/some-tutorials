CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR cortex-m3)
#SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_C_COMPILER "D:/RT-ThreadStudio/env-windows/tools/bin/../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-gcc.exe")
SET(CMAKE_ASM_COMPILER "D:/RT-ThreadStudio/env-windows/tools/bin/../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-gcc.exe")
SET(CMAKE_C_FLAGS " -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g")
SET(CMAKE_ASM_FLAGS " -c -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -x assembler-with-cpp -Wa,-mimplicit-it=thumb  -gdwarf-2")
SET(CMAKE_C_COMPILER_WORKS TRUE)

SET(CMAKE_CXX_COMPILER "D:/RT-ThreadStudio/env-windows/tools/bin/../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-g++.exe")
SET(CMAKE_CXX_FLAGS " -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g")
SET(CMAKE_CXX_COMPILER_WORKS TRUE)

SET(CMAKE_OBJCOPY "D:/RT-ThreadStudio/env-windows/tools/bin/../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-objcopy.exe")
SET(CMAKE_SIZE "D:/RT-ThreadStudio/env-windows/tools/bin/../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-size.exe")

SET(CMAKE_EXE_LINKER_FLAGS " -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -Wl,--gc-sections,-Map=rt-thread.map,-cref,-u,Reset_Handler -T ${CMAKE_SOURCE_DIR}/board/linker_scripts/link.lds")

SET(CMAKE_CXX_STANDARD 14)
PROJECT(rtthread C CXX ASM)
INCLUDE_DIRECTORIES(
	applications
	../../rtos/rt-thread/components/libc/compilers/common/include
	../../rtos/rt-thread/components/libc/compilers/newlib
	../../rtos/rt-thread/components/drivers/include
	board
	board/CubeMX_Config/Inc
	../../rtos/rt-thread/bsp/stm32/libraries/HAL_Drivers/drivers
	../../rtos/rt-thread/bsp/stm32/libraries/HAL_Drivers/drivers/config
	../../rtos/rt-thread/bsp/stm32/libraries/HAL_Drivers
	../../rtos/rt-thread/bsp/stm32/libraries/HAL_Drivers/CMSIS/Include
	../../rtos/rt-thread/components/finsh
	.
	../../rtos/rt-thread/include
	../../rtos/rt-thread/libcpu/arm/common
	../../rtos/rt-thread/libcpu/arm/cortex-m3
	"I:/GitHub/some_tutorials/DemoProject/CLION_RTTHREAD/rtos/platform/stm32_libraries/STM32F1xx_HAL/CMSIS/Device/ST/STM32F1xx/Include",
	"I:/GitHub/some_tutorials/DemoProject/CLION_RTTHREAD/rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Inc",
	../../rtos/rt-thread/components/libc/posix/io/epoll
	../../rtos/rt-thread/components/libc/posix/io/eventfd
	../../rtos/rt-thread/components/libc/posix/io/poll
	../../rtos/rt-thread/components/libc/posix/ipc
)

ADD_DEFINITIONS(
	-DRT_USING_LIBC
	-DRT_USING_NEWLIBC
	-DSTM32F103xE
	-DUSE_HAL_DRIVER
	-D_POSIX_C_SOURCE=1
	-D__RTTHREAD__
)

SET(PROJECT_SOURCES
	applications/main.c
	../../rtos/rt-thread/components/libc/compilers/common/cctype.c
	../../rtos/rt-thread/components/libc/compilers/common/cstdlib.c
	../../rtos/rt-thread/components/libc/compilers/common/cstring.c
	../../rtos/rt-thread/components/libc/compilers/common/ctime.c
	../../rtos/rt-thread/components/libc/compilers/common/cunistd.c
	../../rtos/rt-thread/components/libc/compilers/common/cwchar.c
	../../rtos/rt-thread/components/libc/compilers/newlib/syscalls.c
	../../rtos/rt-thread/components/drivers/core/device.c
	../../rtos/rt-thread/components/drivers/ipc/completion.c
	../../rtos/rt-thread/components/drivers/ipc/condvar.c
	../../rtos/rt-thread/components/drivers/ipc/dataqueue.c
	../../rtos/rt-thread/components/drivers/ipc/pipe.c
	../../rtos/rt-thread/components/drivers/ipc/ringblk_buf.c
	../../rtos/rt-thread/components/drivers/ipc/ringbuffer.c
	../../rtos/rt-thread/components/drivers/ipc/waitqueue.c
	../../rtos/rt-thread/components/drivers/ipc/workqueue.c
	../../rtos/rt-thread/components/drivers/pin/pin.c
	../../rtos/rt-thread/components/drivers/serial/serial.c
	board/CubeMX_Config/Src/stm32f1xx_hal_msp.c
	board/board.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xe.s
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cec.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_crc.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_usart.c
	../../rtos/rt-thread/bsp/stm32/libraries/HAL_Drivers/drivers/drv_gpio.c
	../../rtos/rt-thread/bsp/stm32/libraries/HAL_Drivers/drivers/drv_usart.c
	../../rtos/rt-thread/bsp/stm32/libraries/HAL_Drivers/drv_common.c
	../../rtos/rt-thread/components/finsh/msh_parse.c
	../../rtos/rt-thread/components/finsh/cmd.c
	../../rtos/rt-thread/components/finsh/msh.c
	../../rtos/rt-thread/components/finsh/shell.c
	../../rtos/rt-thread/src/clock.c
	../../rtos/rt-thread/src/components.c
	../../rtos/rt-thread/src/idle.c
	../../rtos/rt-thread/src/ipc.c
	../../rtos/rt-thread/src/irq.c
	../../rtos/rt-thread/src/klibc/kstdio.c
	../../rtos/rt-thread/src/klibc/kstring.c
	../../rtos/rt-thread/src/kservice.c
	../../rtos/rt-thread/src/mem.c
	../../rtos/rt-thread/src/mempool.c
	../../rtos/rt-thread/src/object.c
	../../rtos/rt-thread/src/scheduler_comm.c
	../../rtos/rt-thread/src/scheduler_up.c
	../../rtos/rt-thread/src/thread.c
	../../rtos/rt-thread/src/timer.c
	../../rtos/rt-thread/libcpu/arm/common/atomic_arm.c
	../../rtos/rt-thread/libcpu/arm/common/div0.c
	../../rtos/rt-thread/libcpu/arm/common/showmem.c
	../../rtos/rt-thread/libcpu/arm/cortex-m3/context_gcc.S
	../../rtos/rt-thread/libcpu/arm/cortex-m3/cpuport.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_crc.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_usart.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cec.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
	../../rtos/platform/stm32_libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
)

LINK_DIRECTORIES(
)

LINK_LIBRARIES(
	c
	m
)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf ${PROJECT_SOURCES})
ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD 
COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf)