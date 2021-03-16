TARGET = sdlevents

OPTFLAGS=-O3 -fomit-frame-pointer

KOS_CFLAGS+= -I$(KOS_BASE)/addons/include/SDL -I$(KOS_BASE)/addons/include $(OPTFLAGS) 

KOS_CFLAGS+= -I. -DDREAMCAST

all: $(TARGET).bin

include $(KOS_BASE)/Makefile.rules

.SRCS	=	sdlevents.c 

OBJS = $(.SRCS:.c=.o)

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin

$(TARGET).elf: $(OBJS)
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET).elf $(KOS_START) \
		$(OBJS) -lSFont -lSDL_image_124  -lSDL_1213  -lpng_128 -lz_123 -lm $(OBJEXTRA) $(KOS_LIBS)

$(TARGET).bin: $(TARGET).elf
	$(KOS_OBJCOPY) -R .stack -O binary $(TARGET).elf $(TARGET).bin

run: $(TARGET).bin
	$(KOS_LOADER) $(TARGET).bin

