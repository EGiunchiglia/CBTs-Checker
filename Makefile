#define input file
INFILE = "./input/fig1.xml"

#define output folder
OUTFOLDER = "./output/"

#define the limboole folder
LIMBOOLEPATH = "../limboole1.1/limboole" 
 
# define the C compiler to use
CCXX = g++ -std=c++11

# define any compile-time flags
CXXFLAGS = -g -Wall

# define any directories containing header files other than /usr/include
INCLUDES = -I./include

#define the directory for src files
SRCDIR = ./src

#define the directory for test files
TESTDIR = ./test

#define the directory for the structural test files inside TESTDIR
TEST_STRUCT_DIR = test_strutturali

#define the directory for the functional test files inside TESTDIR
TEST_FUNC_DIR = test_funzionali

#define the directory for object files
OBJDIR = ./build

#define the directory for executable file
EXEDIR = ./bin

# define the C source files
SRCS = $(addprefix $(SRCDIR)/, action.cpp conditioned_behavior_tree.cpp control_flow_node.cpp execution_node.cpp main.cpp task.cpp) 

# define the C source files
SRCS_TEST = $(addprefix $(SRCDIR)/, action.cpp conditioned_behavior_tree.cpp control_flow_node.cpp execution_node.cpp task.cpp) $(addprefix $(TESTDIR)/, $(TEST_FUNC_DIR)/test_funzionali.cpp $(addprefix $(TEST_STRUCT_DIR)/, stage_1.cpp stage_2.cpp stage_3.cpp stage_4.cpp stage_5.cpp) test.cpp) 

# define the C object files 
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# define the C object files 
OBJS_TEST = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS_TEST))

# define the executable file 
MAIN = CBT_requirements_calculator

#define the executable file for functional tests 
MAIN_TEST = CBT_requirements_calculator_test

.PHONY: depend clean run

compile: $(MAIN)
	@echo Program compiled and built

$(MAIN): $(OBJS) 
	$(CCXX) $(CXXFLAGS) $(INCLUDES) -o $(EXEDIR)/$(MAIN) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling: " $@
	$(CCXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	$(RM) ./build/*.o *~ $(EXEDIR)/$(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

run: $(MAIN)
	$(EXEDIR)/$(MAIN) $(INFILE) $(OUTFOLDER) $(LIMBOOLEPATH)


$(MAIN_TEST): $(OBJS_TEST) 
	$(CCXX) $(CXXFLAGS) $(INCLUDES) -o $(EXEDIR)/$(MAIN_TEST) $(OBJS_TEST)

test: $(MAIN_TEST)
	$(EXEDIR)/$(MAIN_TEST) $

