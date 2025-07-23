ROCM_PATH ?= $(wildcard /opt/rocm)
HIPCC = $(ROCM_PATH)/bin/hipcc
CXX = $(HIPCC)

# targets and source files
TARGETS = reduce_v0
SRCS = reduce_v0.cpp
OBJS = $(SRCS:.cpp=.o)


# compiler flags
CXXFLAGS = --offload-arch=gfx942 -std=c++20 \
           -U__HIP_NO_HALF_OPERATORS__ \
           -U__HIP_NO_HALF_CONVERSIONS__ \
           -DHIP_ENABLE_WARP_SYNC_BUILTINS \
		   -Wno-unused-result

CFLAGS = -Ofast -ffast-math -march=native \
           -funroll-loops -fomit-frame-pointer

INCLUDES = -I$(ROCM_PATH)/include -I../../include
LIBS = -L$(ROCM_PATH)/lib -lamdhip64

# compilation rules
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.hip
	$(HIPCC) $(HIPFLAGS) $(INCLUDES) -c $< -o $@

all: $(TARGETS)

# linking rules
reduce_v0: $(OBJS)
	$(HIPCC) $(OBJS) -o $@ $(LIBS)


# cleaning rules
clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY: all clean
