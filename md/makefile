EXECUTABLE := md
LIBDIR := ../lib
LIBS := thostmduserapi hiredis pthread
INCLUDES := h
SRCDIR := cpp

CC := g++
CFLAGS := -ggdb
CPPFLAGS := $(CFLAGS)
CPPFLAGS += $(addprefix -I,$(INCLUDES))
CPPFLAGS += -MMD

RM-F := rm -f

SRCS := $(wildcard *.cpp) $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
DEPS := $(patsubst %.o,%d,$(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)),$(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d,%.cpp,$(MISSING_DEPS)))

.PHONY : all deps objs clean veryclean rebuild info

all: $(EXECUTABLE)

deps: $(DEPS)

objs: $(OBJS)

clean:
	@$(RM-F) *.o
	@$(RM-F) *.d
	@$(RM-F) $(SRCDIR)/*.o
	@$(RM-F) $(SRCDIR)/*.d

veryclean: clean
	@$(RM-F) $(EXECUTABLE)

rebuild: veryclean all

ifneq ($(MISSING_DEPS),)

$(MISSING_DEPS):
	@$(RM-F) $(patsubst %.d,%.o,$@)

endif

-include $(DEPS)
$(EXECUTABLE): $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS)) $(CFLAGS)

info:
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(DEPS)
	@echo $(MISSING_DEPS)
	@echo $(MISSING_DEPS_SOURCES)
