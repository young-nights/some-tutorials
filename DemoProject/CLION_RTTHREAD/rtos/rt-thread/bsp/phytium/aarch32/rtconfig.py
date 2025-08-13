import os
import rtconfig

# toolchains options
ARCH        ='arm'
CPU         ='cortex-a'
CROSS_TOOL  = 'gcc'
PLATFORM    = 'gcc'
EXEC_PATH   = os.getenv('RTT_EXEC_PATH') or r'/usr/bin'
BUILD       = 'debug'

LINK_SCRIPT = 'link.lds'


if PLATFORM == 'gcc':
    PREFIX  = os.getenv('RTT_CC_PREFIX') or 'arm-none-eabi-'
    CC      = PREFIX + 'gcc'
    CXX     = PREFIX + 'g++'
    CPP     = PREFIX + 'cpp'
    AS      = PREFIX + 'gcc'
    AR      = PREFIX + 'ar'
    LINK    = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE    = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY  = PREFIX + 'objcopy'
    STRIP   = PREFIX + 'strip'
    CFPFLAGS = ' -msoft-float'
    AFPFLAGS = ' -mfloat-abi=softfp -mfpu=neon'
    DEVICE   = ' -march=armv8-a -ftree-vectorize -ffast-math -funwind-tables -fno-strict-aliasing'

    CPPFLAGS= ' -E -P -x assembler-with-cpp'
    CXXFLAGS= DEVICE + CFPFLAGS + ' -Wall -fdiagnostics-color=always'
    CFLAGS  = DEVICE + CFPFLAGS + ' -Wall -Wno-cpp -std=gnu99 -D_POSIX_SOURCE -fdiagnostics-color=always'
    AFLAGS  = DEVICE + ' -c' + AFPFLAGS + ' -x assembler-with-cpp'    
    LFLAGS  = DEVICE + ' -Wl,--gc-sections,-Map=rtthread_a32.map,-cref,-u,system_vectors -T '+ LINK_SCRIPT + ' -lsupc++ -lgcc -static'
    CPATH   = ''
    LPATH   = ''

    if BUILD == 'debug':
        CFLAGS   += ' -O0 -gdwarf-2'
        CXXFLAGS += ' -O0 -gdwarf-2'
        AFLAGS   += ' -gdwarf-2'
    else:
        CFLAGS   += ' -Os'
        CXXFLAGS += ' -Os'
    CXXFLAGS += ' -Woverloaded-virtual -fno-rtti'

    M_CFLAGS = CFLAGS + ' -mlong-calls -fPIC '
    M_CXXFLAGS = CXXFLAGS + ' -mlong-calls -fPIC'
    M_LFLAGS = DEVICE + CXXFLAGS + ' -Wl,--gc-sections,-z,max-page-size=0x4' +\
                                    ' -shared -fPIC -nostartfiles -nostdlib -static-libgcc'
    M_POST_ACTION = STRIP + ' -R .hash $TARGET\n' + SIZE + ' $TARGET \n'

    DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtthread_a32.asm\n'
    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread_a32.bin\n' + SIZE + ' $TARGET \n'
