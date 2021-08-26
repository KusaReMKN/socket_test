PROGRAMS = tcpcl udpcl tcpsv udpsv
TCPCL_OBJS = tcpcl.o tcpclient.o
UDPCL_OBJS = udpcl.o udpclient.o
TCPSV_OBJS = tcpsv.o tcpclient.o tcpserver.o
UDPSV_OBJS = udpsv.o udpclient.o udpserver.o
ALL_OBJS = $(TCPCL_OBJS) $(UDPCL_OBJS) $(TCPSV_OBJS) $(UDPSV_OBJS)

VPATH = src
CXXFLAGS = -O2 -Iinclude

.PHONY: all
all: $(PROGRAMS)

tcpcl: $(TCPCL_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

udpcl: $(UDPCL_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

tcpsv: $(TCPSV_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

udpsv: $(UDPSV_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) $(PROGRAMS) $(ALL_OBJS)
