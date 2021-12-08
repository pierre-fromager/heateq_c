CXX = gcc
CC = $(CXX)
CFLAGS = -O2 -Werror -Wall -Wextra -Wpedantic -std=c99 -I./include \
	-g -s \
	-Wno-unused-function -Wno-unused-parameter -Wno-unused-variable \
	-lm \
	-fno-asm -std=c11 \
	-Wno-format-nonliteral \
	-Wformat=2 -Wformat-security \
	-Wnull-dereference -Wstack-protector -Wtrampolines -Wvla \
	-Warray-bounds=2 \
	-Wtraditional-conversion -Wshift-overflow=2 -Wcast-qual \
	-Wconversion -Wlogical-op -Wduplicated-cond \
	-Wformat-signedness -Wshadow -Wstrict-overflow=4 \
	-Wundef -Wstrict-prototypes -Wswitch-default -Wswitch-enum \
	-Wstack-usage=10000 \
	-D_FORTIFY_SOURCE=2 \
	#-fstack-protector-strong -fPIE -fsanitize=address \
	-fsanitize=leak -fno-omit-frame-pointer -fsanitize=undefined \
	-fsanitize=bounds-strict -fsanitize=float-divide-by-zero \
	-fsanitize=float-cast-overflow

DOC = doc
SRC = src
TST = test
LIB_VER_MAJ = .1
LIB_VER_MIN = .0
SRC_FILES = $(wildcard $(SRC)/*.c) $(wildcard$(SRC)/**/*.c)
TST_FILES = $(wildcard $(TST)/*.c) $(wildcard $(TST)/**/*.c) $(wildcard $(TST)/**/**/*.c)
ALL_SRC_BUT_MAIN = $(filter-out $(SRC)/main.c,  $(SRC_FILES))

OBJECTS = $(SRC_FILES:%.c=%.o)
OBJECTS_TO_TEST = $(ALL_SRC_BUT_MAIN:%.c=%.o)
OBJECTS_TEST = $(TST_FILES:%.c=%.o)
TARGET = mollier
TARGET_TEST = mollier_test

.PHONY: all
	all: $(TARGET) $(TARGET_TEST)

$(TARGET): $(OBJECTS)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJECTS)  

.PHONY: doc
doc:
	doxygen $(DOC)/surfaces.conf

.PHONY: cleandoc
cleandoc:
	rm -rf $(DOC)/html

.PHONY: check
check:
	cppcheck -I./include --check-config --enable=all --std=c99 --suppress=missingIncludeSystem $(SRC) -I $(SRC)

.PHONY: test
test:$(OBJECTS_TEST) 
	$(CXX) $(OBJECTS_TO_TEST) $(OBJECTS_TEST) $(CFLAGS) -lcunit -o $(TARGET_TEST)

.PHONY: cleantest
cleantest:
	rm -rf $(TARGET_TEST) $(OBJECTS_TEST)	
