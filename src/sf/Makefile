ARFLAGS+=-U
CXXFLAGS+=-I../../include

OBJS= \
	mat4.o \
	qtrn.o \
	spheroid.o \
	tetra.o \
	vec3.o \
	vec4.o \

TARGET=libsf.a

$(TARGET): $(TARGET)($(OBJS))

.PHONY: clean
clean:
	$(RM) -f $(OBJS) $(TARGET)
