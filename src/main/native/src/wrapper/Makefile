#!/usr/bin/make -f
#
# Makefile for native stuff
#

# c files to compile
C_SOURCES	:= tessbaseapi.cpp

# the name of the library to build
LIBNAME		:= tessbaseapi

C_SOURCE_DIR    := .
C_GENSOURCE_DIR := .

TARGET_DIR	:= .
C_BUILD_DIR    = $(TARGET_DIR)
JAVA_BUILD_DIR = ../../../../../target/classes
JAVA_RESOURCE_DIR = ../../../resources

# get our OS/architure
UNAME:= $(shell uname)
LIB_ARCH:= $(shell uname -m)

# find the jdk. if this doesn't work for you, define JAVA_HOME in your
# environment or on the make command line
JAVA_HOME ?= /Library/Java/JavaVirtualMachines/jdk1.7.0_21.jdk/Contents/Home

# tools and options
CFLAGS = -Wall -fpic
CPPFLAGS = -I$(JAVA_HOME)/include
JAVAH = $(JAVA_HOME)/bin/javah
JAVAH_FLAGS += -classpath $(JAVAH_CLASSPATH)
JAVAH_CMD = $(JAVAH) $(JAVAH_FLAGS) $(OUTPUT_OPTION)
LDFLAGS = -shared
LD_LIBS :=
LINK.so = $(CC) $(LDFLAGS) $(LD_LIBS)

ifdef DEBUG
CFLAGS += -g
LDFLAGS += -g
endif

# os-dependent bits
ifeq ($(UNAME),Linux)
LIB_EXTN = .so
CPPFLAGS += -fPIC -I../build/include -I$(JAVA_HOME)/include/linux
LD_LIBS += -L../build/lib -Wl,-Bstatic -Wl,-whole-archive -llept -ltesseract -Wl,-no-whole-archive -Wl,-Bdynamic
CC = g++
STRIP = strip --strip-unneeded
LIB_PLATFORM = linux
else
ifeq ($(findstring CYGWIN,$(UNAME)),CYGWIN)
LIB_EXTN = .dll
CPPFLAGS += -I$(JAVA_HOME)/include/win32
STRIP = echo
LIB_PLATFORM = win
else
ifeq ($(UNAME),Darwin)
LIB_EXTN = .dylib
CPPFLAGS += -I$(JAVA_HOME)/include/darwin -I../build/include
LD_LIBS += -L../build/lib -llept -ltesseract
CC = g++ 
STRIP = strip -S
LIB_PLATFORM = macosx
else
f := $(error Platform $(UNAME) not supported)
endif
endif
endif

# the name of the file we build
LIB_FILENAME     = $(LIBNAME)-$(LIB_PLATFORM)-$(LIB_ARCH)$(LIB_EXTN)
TARGET           = $(LIB_FILENAME)
TARGET_COPY      = $(JAVA_RESOURCE_DIR)/META-INF/lib/$(LIB_FILENAME)

# classpath for javah
ifdef CLASSPATH
JAVAH_CLASSPATH = $(JAVA_BUILD_DIR):$(CLASSPATH)
else
JAVAH_CLASSPATH = $(JAVA_BUILD_DIR)
endif

# we look in $(C_SOURCE_DIR) for c files...
vpath %.cpp $(C_SOURCE_DIR)

# convenience variables
C_OBJFILES = $(addprefix $(C_BUILD_DIR)/,$(subst .cpp,.o,$(C_SOURCES)))

# default target
all: $(TARGET_COPY)

# rule to compile the .c files
$(C_BUILD_DIR)/%.o: %.cpp
	@mkdir -p `dirname $@`
	$(COMPILE.c) $(OUTPUT_OPTION) $<

# link the C objects into a shared library
# and strip unneeded symbols to reduce file size
$(TARGET): $(C_OBJFILES) $(LDLIBS)
	@mkdir -p `dirname $@`
	$(LINK.so) $(OUTPUT_OPTION) $^
	$(STRIP) $(TARGET)

# copy the output to the JNI directory
$(TARGET_COPY): $(TARGET)
	@mkdir -p `dirname $@`
	cp $(TARGET) $(TARGET_COPY)
	
# a rule to build the .h file with javah
$(C_GENSOURCE_DIR)/com_apache_pdfbox_ocr_tesseract_TessBaseAPI.h: $(JAVA_BUILD_DIR)/com/apache/pdfbox/ocr/tesseract/TessBaseAPI.class
	rm -f $@
	$(JAVAH) $(JAVAH_FLAGS) $(OUTPUT_OPTION) com.apache.pdfbox.ocr.tesseract.TessBaseAPI

# the .o file depends on the .h file
$(C_BUILD_DIR)/tessbaseapi.o: $(C_GENSOURCE_DIR)/com_apache_pdfbox_ocr_tesseract_TessBaseAPI.h

clean::
	rm -f $(C_OBJFILES)
	rm -f $(TARGET)
	rm -f $(TARGET_COPY)
	rm -f $(C_BUILD_DIR)/jnirules.mak
