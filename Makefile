LIB_SOURCES := $(shell find ichneutae/ -type f -name "*.cc" ! -name "*_test.cc")
IN_SOURCES := $(shell find cmd/in/ -type f -name "*.cc")
SATYR_SOURCES := $(shell find cmd/satyr/ -type f -name "*.cc")

CXXFLAGS := -std=c++20 -O3 -Wall -Werror -flto -static ${CXXFLAGS}

.PHONY: in
in:
	$(CXX) -o $@ -I. ${CFLAGS} ${CXXFLAGS} ${LIB_SOURCES} ${IN_SOURCES}

.PHONY: satyr
satyr:
	$(CXX) -o $@ -I. ${CFLAGS} ${CXXFLAGS} ${LIB_SOURCES} ${SATYR_SOURCES}
