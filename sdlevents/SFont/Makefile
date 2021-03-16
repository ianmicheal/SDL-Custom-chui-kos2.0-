INCS = $(KOS_INCS) -I../SDL-1.2.9/include -I.
DEFS =  -DPACKAGE=\"SFont\" -DDC -DDREAMCAST
KOS_CFLAGS+=$(DEFS) $(INCS) $(OPTFLAGS)


TARGET = libSFont.a

all: $(TARGET)

include $(KOS_BASE)/Makefile.rules

SRCS =	\
	SFont.c


OBJS = $(SRCS:.c=.o)

clean:
	rm -f $(OBJS)

$(TARGET) : $(OBJS)
	rm -f $(KOS_BASE)/addons/lib/dreamcast/$(TARGET)
	$(KOS_AR) rcs $(KOS_BASE)/addons/lib/dreamcast/$(TARGET) $(OBJS)
	$(KOS_RANLIB) $(KOS_BASE)/addons/lib/dreamcast/$(TARGET)
