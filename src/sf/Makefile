ARFLAGS+=-U
CXXFLAGS+=-I../../include

OBJS= \
	face.o \
	geom.o \
	qtrn.o \
	sf.o \
	spheroid.o \

TARGET=libsf.a

$(TARGET): $(TARGET)($(OBJS))

.PHONY: clean
clean:
	$(RM) -f $(OBJS) $(TARGET)
