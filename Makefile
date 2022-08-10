CXX=g++
CXXFLAGS= --std=c++11 -g  -Wall -Wextra -fstack-protector-strong
ifeq ($(DEBUG), y)
	CXXFLAGS += -O0 -DDEBUG
else
	CXXFLAGS += -O3 -DNDEBUG
endif
OBJS = $(patsubst %.cc,%.o,$(shell ls src/*.cc))
#OBJS += $(patsubst %.cc,%.o,$(shell ls src/proto/*.cc))

TARGET = calculator
#CXXLDFLAGS = -Lthird_party/3rdlib \
#             -Wl,-rpath=third_party/3rdlib

INCLUDE = -Isrc
#LIBS = -lmuduo_net -lmuduo_base -lgflags -lpthread

all:$(TARGET)
$(TARGET):$(OBJS)
	$(CXX) $(CXXLDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(OBJS):%.o:%.cc
	$(CXX) -c $(CXXFLAGS) $< $(INCLUDE) -o $@
clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
