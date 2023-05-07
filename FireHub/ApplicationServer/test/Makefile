# Common configuration
SOAP_DIR=./soap
SCHEMA_DIR=../../schema
#SERVER_IMPLEMENTATION=../Handlers.cpp
SERVER_IMPLEMENTATION=server_stubs.c

# Stub generator configuration
SCHEMA_2_H=wsdl2h
STUBGEN=soapcpp2
STUBGEN_FLAGS=-c++11 -L -s -v -x -c
SCHEMA_NAME=ApplicationServer
SOAP_STUB_OUTPUT_DIR=$(SOAP_DIR)

# Compiler configuration
CXX=g++
CXX_OPTS=-g -Wall -Werror -Wextra -std=gnu++11 -fsanitize=address \
		-fsanitize=undefined -Winline # -O3 -finline-functions -Winline
CXX_INCLUDES=$(SOAP_STUB_OUTPUT_DIR) .. ../../common
CXX_INCLUDE_DIRS=$(patsubst %,-I%,$(CXX_INCLUDES))
CXX_LIBS=-lgsoap++ -lfmt
CXX_FLAGS=$(CXX_OPTS) $(CXX_INCLUDE_DIRS) $(CXX_LIBS)

# C/CPP files to link with
CXX_LINK_FILES=$(SOAP_STUB_OUTPUT_DIR)/*.cpp ctest.c $(SERVER_IMPLEMENTATION)

# Individial test targets
TEST_FILES := $(wildcard test_*.c)
TESTS := $(patsubst %.c,%,$(TEST_FILES))
EXEC := $(patsubst %.c,.__test_exec_%,$(TEST_FILES))

# Required test resources
APP_CGI := ../$(SCHEMA_NAME).cgi
CGI_STAGING_DIR := ./cgi-bin
TEST_SERVER := ./test_server.py
TEST_SERVER_SHUTDOWN_FILE := /tmp/stop_firestreamer_test_server

xsd_headers: $(SCHEMA_DIR)/$(SCHEMA_NAME).xsd
	mkdir -p $(SOAP_STUB_OUTPUT_DIR)/
	$(SCHEMA_2_H) $(SCHEMA_DIR)/$(SCHEMA_NAME).xsd -o $(SOAP_STUB_OUTPUT_DIR)/$(SCHEMA_NAME).h

xsd_stubs: xsd_headers $(SOAP_STUB_OUTPUT_DIR)/$(SCHEMA_NAME).h $(SOAP_STUB_OUTPUT_DIR)
	$(STUBGEN) $(STUBGEN_FLAGS) $(SOAP_STUB_OUTPUT_DIR)/$(SCHEMA_NAME).h -d$(SOAP_STUB_OUTPUT_DIR)/

clean:
	@rm -rf $(TESTS) $(EXEC) $(SOAP_STUB_OUTPUT_DIR)

compile: xsd_stubs $(TESTS)

copy_cgi: $(APP_CGI)
	@cp $(APP_CGI) $(CGI_STAGING_DIR)/

start_server:
	rm -rf $(TEST_SERVER_SHUTDOWN_FILE)
	$(TEST_SERVER) 1>/dev/null 2>/dev/null &

stop_server:
	touch $(TEST_SERVER_SHUTDOWN_FILE)

test: copy_cgi xsd_stubs start_server $(EXEC) stop_server clean

.DELETE_ON_ERROR:
$(EXEC):
	@$(CXX) $(CXX_LINK_FILES) $(patsubst .__test_exec_%,%.c,$@) $(CXX_FLAGS) -o $@
	@./$@
	@rm -rf $@

$(TESTS):
	@$(CXX) $(CXX_LINK_FILES) $@.c $(CXX_FLAGS) -o $@
