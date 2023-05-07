# Stub generator configuration
SCHEMA_2_H=wsdl2h
STUBGEN=soapcpp2
STUBGEN_FLAGS=-c++11 -L -s -v -x -S
SCHEMA_DIR=../schema
SCHEMA_NAME=ApplicationServer
STUB_OUTPUT_DIR=./soap

# Global config
APPNAME=$(SCHEMA_NAME)

# Other config settings
LOG_FILEPATH=./FireStreamer.log
COMMONS_DIR=../common

# Compiler configuration
CXX=g++
CXX_OPTS=-g
CXX_INCLUDE_DIRS=-I./ -I$(COMMONS_DIR) -I./soap/
CXX_FLAGS=$(CXX_OPTS) $(CXX_INCLUDE_DIRS)
CXX_LIBS=-lgsoap++ -ljsoncpp -lfmt -lsqlite3

# C/CPP files to compile
CXX_FILES=*.cpp $(COMMONS_DIR)/*.cpp $(STUB_OUTPUT_DIR)/*.cpp

remake_cgi: clean cgi

cgi: xsd_stubs
	$(CXX) $(CXX_FLAGS) -o $(APPNAME).cgi $(CXX_FILES) $(CXX_LIBS)

xsd_stubs: xsd_headers $(STUB_OUTPUT_DIR)/$(SCHEMA_NAME).h $(STUB_OUTPUT_DIR)
	$(STUBGEN) $(STUBGEN_FLAGS) $(STUB_OUTPUT_DIR)/$(SCHEMA_NAME).h -d$(STUB_OUTPUT_DIR)/

xsd_headers: $(SCHEMA_DIR)/$(SCHEMA_NAME).xsd
	mkdir -p $(STUB_OUTPUT_DIR)/
	$(SCHEMA_2_H) $(SCHEMA_DIR)/$(SCHEMA_NAME).xsd -o $(STUB_OUTPUT_DIR)/$(SCHEMA_NAME).h

clean:
	rm -rf $(STUB_OUTPUT_DIR) $(APPNAME).cgi $(LOG_FILEPATH)

test: remake_cgi
	$(MAKE) -C test test
