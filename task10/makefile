.PHONY: all clean run_leak_check_front run_leak_check_back run_leak_check_lang frontend_lang backend_lang middleend_lang run_leak_check_middle generate_asm run_leak_check_gen_asm
# эти цели не являются файлами выполняй их даже если соотв файлы существуют
all: lang 

OPT ?= 1
INPUT ?= tests/test_fib.uccello
FLAGS ?= -S
ASM_FILE ?= demo.s
OUT ?= zhopa.bin

COMP=clang++

# FLAGS ------------------------------------------------------------------

CFLAGS_DEBUG = -D_DEBUG -DDEBUG_SMALL_TREE
COMMON_CFLAGS = -DASSEMBLER -DPROCESSOR -ggdb3 -std=c++20 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -fPIE -Werror=vla -Wno-c++11-extensions -g -fsanitize=address,leak,undefined    
LDFLAGS = -fsanitize=address,leak,undefined

# СOMMON ------------------------------------------------------------------

TREE = $(shell find tree -type f -name "*.cpp")
TREE_OBJS = $(TREE:%.cpp=%.o)

DEBUG_OUTPUT = $(shell find debug_output -type f -name "*.cpp")
DEBUG_OUTPUT_OBJS = $(DEBUG_OUTPUT:%.cpp=%.o)

$(TREE_OBJS): %.o: %.cpp                            
	$(COMP) -c $< -o $@ $(CFLAGS) 

$(DEBUG_OUTPUT_OBJS): %.o: %.cpp                            
	$(COMP) -c $< -o $@ $(CFLAGS) 

# FRONTEND ------------------------------------------------------------------

FRNTD = $(shell find frontend include -type f -name "*.cpp")
FRNTD_OBJS = $(FRNTD:%.cpp=%.o)

$(FRNTD_OBJS): %.o: %.cpp                            
	$(COMP) -c $< -o $@ $(CFLAGS) 

frontend_lang: $(FRNTD_OBJS)  $(TREE_OBJS) $(DEBUG_OUTPUT_OBJS)
	$(COMP) -o $@ $^ $(LDFLAGS)

run_leak_check_front: frontend_lang
	ASAN_OPTIONS="detect_leaks=1:verbosity=1:print_stacktrace=1" ./frontend_lang $(INPUT)

# MIDDLEEND -----------------------------------------------------------------

MDLND = $(shell find middleend -type f -name "*.cpp")
MDLND_OBJS = $(MDLND:%.cpp=%.o)

BCKND_MID_HELP = $(shell find backend/make_backend_tree/read_tree_from_file -type f -name "*.cpp")
BCKND_MID_HELP_OBJS= $(BCKND_MID_HELP:%.cpp=%.o)

PUT_TREE_CPP = $(wildcard frontend/io/put_tree_to_file.cpp)
PUT_TREE_CPP_OBJS= $(PUT_TREE_CPP:%.cpp=%.o)

$(MDLND_OBJS): %.o: %.cpp                            
	$(COMP) -c $< -o $@ $(CFLAGS) 

$(BCKND_MID_HELP_OBJS): %.o: %.cpp                            
	$(COMP) -c $< -o $@ $(CFLAGS) 

$(PUT_TREE_CPP_OBJS): %.o: %.cpp                            
	$(COMP) -c $< -o $@ $(CFLAGS) 

middleend_lang: $(MDLND_OBJS) $(TREE_OBJS) $(BCKND_MID_HELP_OBJS) $(DEBUG_OUTPUT_OBJS) $(PUT_TREE_CPP_OBJS)
	$(COMP) -o $@ $^ $(LDFLAGS)

run_leak_check_middle: middleend_lang
	ASAN_OPTIONS="detect_leaks=1:verbosity=1:print_stacktrace=1" ./middleend_lang $(OPT) 


# BACKEND ------------------------------------------------------------------

BCKND = $(shell find backend -type f -name "*.cpp")
BCKND_OBJS = $(BCKND:%.cpp=%.o)

$(BCKND_OBJS): %.o: %.cpp                            
	$(COMP) -c $< -o $@ $(CFLAGS) 

backend_lang: $(TREE_OBJS) $(BCKND_OBJS) $(DEBUG_OUTPUT_OBJS)
	$(COMP) -o $@ $^ $(LDFLAGS) -lbsd

run_leak_check_back: backend_lang
	ASAN_OPTIONS="detect_leaks=1:verbosity=1:print_stacktrace=1" ./backend_lang $(OUT) $(FLAGS) $(ASM_FILE)

# Frontend, middleend and backend --------------------------------------------------------

lang:
	make frontend_lang && ./frontend_lang $(INPUT) && \
	rm -f $(FRNTD_OBJS)	frontend_lang  && make middleend_lang && ./middleend_lang $(OPT)  && \
	rm -f $(MDLND_OBJS)	middleend_lang && make backend_lang && ./backend_lang $(OUT) $(FLAGS) $(ASM_FILE) && \
	rm -f $(BCKND_OBJS) backend_lang && chmod +x $(OUT)

run_leak_check_lang:
	export ASAN_OPTIONS="detect_leaks=1:verbosity=1:print_stacktrace=1" && \
	make frontend_lang && ./frontend_lang $(INPUT) && \
	rm -f $(FRNTD_OBJS)	frontend_lang  && make middleend_lang && ./middleend_lang $(OPT) && \
	rm -f $(MDLND_OBJS)	middleend_lang && make backend_lang && ./backend_lang $(OUT) $(FLAGS) $(ASM_FILE) && \
	rm -f $(BCKND_OBJS)  && chmod +x $(OUT)
clean:
	rm -f frontend_lang backend_lang middleend_lang lang 
	rm -f $(FRNTD_OBJS) $(TREE_OBJS) $(MDLND_OBJS) $(MAIN_RUN_ASM_OBJS) $(DEBUG_OUTPUT_OBJS) $(BCKND_OBJS)
	rm -f debug_output/images/*.dot
	rm -f debug_output/images/*.svg