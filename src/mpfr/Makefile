ARFLAGS+=-U

OBJS= \
	mpf.o \

TARGET=libmpfr.a

$(TARGET): $(TARGET)($(OBJS))

.PHONY: clean
clean:
	$(RM) -f $(OBJS) $(TARGET)
