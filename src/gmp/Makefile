ARFLAGS+=-U

OBJS= \
	mpz.o \

TARGET=libgmp.a

$(TARGET): $(TARGET)($(OBJS))

.PHONY: clean
clean:
	$(RM) -f $(OBJS) $(TARGET)
