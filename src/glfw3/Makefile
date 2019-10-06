LIBS= \
	glew \
	glfw3 \

ARFLAGS+=-U
CXXFLAGS+=-I../../include $(shell pkg-config --cflags $(LIBS))

OBJS= \
	window.o \

TARGET=libglfw3.a

$(TARGET): $(TARGET)($(OBJS))

.PHONY: clean
clean:
	$(RM) -f $(OBJS) $(TARGET)
