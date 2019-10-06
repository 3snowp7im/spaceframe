LIBS= \
	spdlog \

ARFLAGS+=-U
CXXFLAGS+=-I../../include $(shell pkg-config --cflags $(LIBS))

OBJS= \
	log.o \

TARGET=libspdlog.a

$(TARGET): $(TARGET)($(OBJS))

.PHONY: clean
clean:
	$(RM) -f $(OBJS) $(TARGET)
