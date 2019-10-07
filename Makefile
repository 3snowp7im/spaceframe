LIBS= \
	glew \
	glfw3 \
	spdlog \

OBJS= \
	src/spaceframe/spaceframe.o \

MODULES= \
	glfw3 \
	sf \
	mpfr \
	spdlog \

TARGET=src/spaceframe/spaceframe

$(TARGET): CXXFLAGS+=-Iinclude
$(TARGET): LDLIBS+=-lstdc++ -lm -lmpfr -lpthread $(shell pkg-config --libs $(LIBS))

$(TARGET): \
	$(OBJS) \
	$(foreach module,$(MODULES),src/$(module)/lib$(module).a) \

define GEN_MODULE_RULE
src/$1/lib$1.a:
	$$(MAKE) -C $$(dir $$@)
endef

$(foreach module,$(MODULES),$(eval $(call GEN_MODULE_RULE,$(module))))

.PHONY: clean
clean:
	$(RM) -f $(OBJS) $(TARGET)
	$(foreach module,$(MODULES),$(MAKE) -C src/$(module) clean;)
