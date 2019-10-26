ARFLAGS+=-U
CXXFLAGS+=-I../../include

OBJS= \
	geom.o \
	qtrn.o \
	sf.o \
	spheroid.o \
	tetra.o \

TARGET=libsf.a

$(TARGET): $(TARGET)($(OBJS))

.PHONY: clean
clean:
	$(RM) -f $(OBJS) $(TARGET)
