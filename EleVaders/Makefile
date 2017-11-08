# The compiler
#CXX = /usr/lib/gcc-snapshot/bin/g++
CXX = g++
CXXFLAGS = -fmessage-length=0 -std=c++11 -DTWODIM=0

# Specify the main target
TARGET = Elevaders

# Default build type. Run "make TYPE=xxx" to override default build type.
TYPE = release
#TYPE = profile
#TYPE = debug

# Which directories contain source files
DIRS = . src
# Which libraries are linked
LIBS = SDL
# Dynamic libraries
DLIBS =

# The next blocks change some variables depending on the build type

ifeq ($(TYPE),win)
CXX = x86_64-w64-mingw32-g++
SDLFLAGS = -I/usr/include -D_GNU_SOURCE=1 -D_REENTRANT
MACROS = NDEBUG DEBUG=0 
CCPARAM = $(CXXFLAGS) -Ofast -pipe -mtune=native -march=native -m64  -flto -fuse-linker-plugin -funroll-loops -finline-small-functions -finline-functions-called-once -fno-finite-math-only  $(SDLFLAGS) $(foreach MACRO,$(MACROS),-D$(MACRO)) -o Ele.exe
LDPARAM = $(CCPARAM) sdl-config --libs -s
endif


ifeq ($(TYPE),release)
MACROS = NDEBUG DEBUG=0 
CCPARAM = $(CXXFLAGS) -Ofast -pipe -mtune=native -march=native -m64  -flto -fuse-linker-plugin -funroll-loops -finline-small-functions -finline-functions-called-once -fno-finite-math-only $(foreach MACRO,$(MACROS),-D$(MACRO))
LDPARAM = $(CCPARAM) -s
endif

ifeq ($(TYPE),profile)
MACROS = NDEBUG DEBUG=0
CCPARAM = $(CXXFLAGS) -pg  $(foreach MACRO,$(MACROS),-D$(MACRO))
LDPARAM = $(CCPARAM)
endif

ifeq ($(TYPE),debug)
MACROS = DEBUG=1
CCPARAM = $(CXXFLAGS) -g3 -Og -fno-inline  -Wall -Wextra -Wshadow -Wundef -Wwrite-strings -Woverloaded-virtual -Weffc++ -Wold-style-cast -pedantic -Winline -Wunreachable-code $(foreach MACRO,$(MACROS),-D$(MACRO))
LDPARAM = $(CCPARAM)
endif



# Add directories to the include and library paths
INCPATH = .
LIBPATH = 

# Which files to add to backups, apart from the source code
EXTRA_FILES = Makefile

# Where to store object and dependancy files.
STORE = build-$(TYPE)
# Makes a list of the source (.cpp) files.
SOURCE := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.cpp))
# List of header files.
HEADERS := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.h))
# Makes a list of the object files that will have to be created.
OBJECTS := $(addprefix $(STORE)/, $(SOURCE:.cpp=.o))
# Same for the .d (dependancy) files.
DFILES := $(addprefix $(STORE)/,$(SOURCE:.cpp=.d))

all: $(TARGET)

# Main target. The @ in front of a command prevents make from displaying
# it to the standard output.
$(TARGET): dirs $(OBJECTS)
	@echo Linking $(TARGET).
	@$(CXX) -o $(TARGET) $(OBJECTS) $(LDPARAM) $(foreach LIBRARY, \
	$(LIBS),-l$(LIBRARY)) $(foreach LIB,$(LIBPATH),-L$(LIB))
	@mv $(TARGET) $(STORE)
	@echo Build: $(TYPE)
	
# Rule for creating object file and .d file, the sed magic is to add
# the object path at the start of the file because the files gcc
# outputs assume it will be in the same dir as the source file.
$(STORE)/%.o: %.cpp
	@echo Creating object file for $*...
	@$(CXX) -Wp,-MMD,$(STORE)/$*.dd $(CCPARAM) $(foreach INC,$(INCPATH),-I$(INC))\
	$(foreach MACRO,$(MACROS),-D$(MACRO)) -c $< -o $@
	@sed -e '1s/^\(.*\)$$/$(subst /,\/,$(dir $@))\1/' $(STORE)/$*.dd > $(STORE)/$*.d
	@rm -f $(STORE)/$*.dd

# Empty rule to prevent problems when a header is deleted.
%.h: ;



# Backup the source files.
backup:
	@-if [ ! -e .backup ]; then mkdir .backup; fi;
	@zip .backup/backup_`date +%d-%m-%y_%H.%M`.zip $(SOURCE) $(HEADERS) $(EXTRA_FILES)

# Create necessary directories
dirs:
	@-if [ ! -e $(STORE) ]; then mkdir $(STORE); fi;
	@-$(foreach DIR,$(DIRS), if [ ! -e $(STORE)/$(DIR) ]; \
	then mkdir $(STORE)/$(DIR); fi; )

# Includes the .d files so it knows the exact dependencies for every source.
-include $(DFILES)

# Precompile all.h
pre:
	@cd src; $(CXX) $(CCPARAM) all.h

# Cleans up the objects, .d files and executables.
clean:
	@echo Making clean.
	@-rm -f $(foreach DIR,$(DIRS),$(STORE)/$(DIR)/*.d $(STORE)/$(DIR)/*.o)
	@-rm -f $(TARGET)
	
# Remove ALL the bullshit
distclean:
	@-rm -rf build-release
	@-rm -rf build-profile
	@-rm -rf build-debug
	@-rm -rf build-debugMore
	@-rm -rf build-fulldebug
	@-rm src/all.h.gch
	@-rm -rf doxygen

# Generate documentaion
doc:
	@doxygen dox

# Generate ctags
tags:
	@cd src; ctags-exuberant *.*; cscope-indexer
	