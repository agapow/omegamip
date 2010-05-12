### Settings

# set to non-zero for the parallel version
MPI = 1

# set to non-zero for the debug version
DEBUG = 1

# set to non-zero for the profiled version
PROFILE = 1

# set flags
ifneq (${DEBUG},0)
	CXXFLAGS = -ggdb -DNDEBUG
else
	CXXFLAGS = -Wall -Wno-deprecated -O3
endif

# set compiler
ifneq ($(MPI),0)
	CXXFLAGS += -DMPI_ENABLED -lmpi
	CXX = mpic++
else
	CXX = gcc
endif

# set profiler
ifneq (${PROFILE},0)
	CXXFLAGS += -g -pg
endif

# set libraries
LIBS += -lm -lstdc++

LDFLAGS = $(CXXFLAGS)
LDLIBS = $(LIBS)

OBJECTS = likelihood.o main.o om_app.o io.o mcmc.o om_math.o
PROGS = omegamip 

all: $(PROGS) 

clean:
	rm -f *.o

showdep: 
	@$(CXX) -MM main.cpp likelihood.cpp mcmc.cpp io.cpp tools.cpp om_app.cpp

omegamip: $(OBJECTS)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o omegamip $(OBJECTS)

main.o: main.cpp om_app.h myutils.h myerror.h utils.h vector.h matrix.h \
  lotri_matrix.h random.h DNA.h
likelihood.o: likelihood.cpp om_app.h myutils.h myerror.h utils.h \
  vector.h matrix.h lotri_matrix.h random.h DNA.h om_math.h
mcmc.o: mcmc.cpp om_app.h myutils.h myerror.h utils.h vector.h matrix.h \
  lotri_matrix.h random.h DNA.h om_incl.h
io.o: io.cpp om_app.h myutils.h myerror.h utils.h vector.h matrix.h \
  lotri_matrix.h random.h DNA.h controlwizard.h
om_math.o: om_math.cpp om_math.h om_incl.h
om_app.o: om_app.cpp om_app.h myutils.h myerror.h utils.h vector.h \
  matrix.h lotri_matrix.h random.h DNA.h controlwizard.h argumentwizard.h
