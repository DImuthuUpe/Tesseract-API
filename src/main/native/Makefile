#!/usr/bin/make -f
#
# Makefile for native stuff
#

# c files to compile
C_SOURCES	:= tessbaseapi.cpp

# the name of the library to build
LIBNAME		:= tessbaseapi

C_SOURCE_DIR    := src
C_GENSOURCE_DIR := src

TARGET_DIR	:= ../../../target
C_BUILD_DIR    = $(TARGET_DIR)/native
JAVA_BUILD_DIR = $(TARGET_DIR)/classes

# the name of the file we build
TARGET		= $(JAVA_BUILD_DIR)/META-INF/lib/$(LIB_PREFIX)$(LIBNAME)$(LIB_EXTN)

# find the jdk. if this doesn't work for you, define JAVA_HOME in your
# environment or on the make command line
JAVA_HOME ?= /usr/local/j2ee/jdk

# tools and options
CFLAGS = -Wall -fpic
CPPFLAGS = -I$(C_SOURCE_DIR) -I$(C_GENSOURCE_DIR) -Iinclude \
	-I$(JAVA_HOME)/include
JAVAH = $(JAVA_HOME)/bin/javah
JAVAH_FLAGS += -classpath $(JAVAH_CLASSPATH)
JAVAH_CMD = $(JAVAH) $(JAVAH_FLAGS) $(OUTPUT_OPTION)
LDFLAGS = -shared
LINK.so = $(CC) $(LDFLAGS) $(LD_LIBS)

ifdef DEBUG
CFLAGS += -g
LDFLAGS += -g
endif

# os-dependent bits
UNAME := $(shell uname)

ifeq ($(UNAME),Linux)
LIB_PREFIX = lib
LIB_EXTN = .so
CPPFLAGS += -I$(JAVA_HOME)/include/linux
else
ifeq ($(findstring CYGWIN,$(UNAME)),CYGWIN)
LIB_PREFIX =
LIB_EXTN = .dll
CPPFLAGS += -I$(JAVA_HOME)/include/win32
else
ifeq ($(UNAME),Darwin)
LIB_PREFIX = lib
LIB_EXTN = .dylib
CPPFLAGS += -I/System/Library/Frameworks/JavaVM.framework/Headers -I ./includes/leptonica -I ./includes/tesseract
else
f := $(error Platform $(UNAME) not supported)
endif
endif
endif

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
all: $(TARGET)

# rule to compile the .c files
$(C_BUILD_DIR)/%.o: %.cpp
	@mkdir -p `dirname $@`
	$(COMPILE.c) $(OUTPUT_OPTION) $<

# link the C objects into a shared library
$(TARGET): $(C_OBJFILES) $(LDLIBS)
	@mkdir -p `dirname $@`
	$(LINK.so) $(OUTPUT_OPTION) $^

# a rule to build the .h file with javah
$(C_GENSOURCE_DIR)/com_apache_pdfbox_ocr_tesseract_TessBaseAPI.h: $(JAVA_BUILD_DIR)/com/apache/pdfbox/ocr/tesseract/TessBaseAPI.class
	rm -f $@
	$(JAVAH) $(JAVAH_FLAGS) $(OUTPUT_OPTION) com.apache.pdfbox.ocr.tesseract.TessBaseAPI

# the .o file depends on the .h file
$(C_BUILD_DIR)/tessbaseapi.o: $(C_GENSOURCE_DIR)/com_apache_pdfbox_ocr_tesseract_TessBaseAPI.h

clean::
	rm -f $(C_OBJFILES)
	rm -f $(TARGET)
	rm -f $(C_BUILD_DIR)/jnirules.mak

