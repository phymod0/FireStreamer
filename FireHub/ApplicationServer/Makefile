# Stub generator configuration
SCHEMA_2_H=wsdl2h
STUBGEN=soapcpp2
STUBGEN_FLAGS=-c++11 -L -S -s -v -w -x
SCHEMA_DIR=../schema
SCHEMA_NAME=ApplicationServer
STUB_OUTPUT_DIR=./soap

# Compiler configuration
CXX=g++
CXX_OPTS=-g
CXX_INCLUDE_DIRS=-I./soap -I./
CXX_FLAGS=$(CXX_OPTS) $(CXX_INCLUDE_DIRS)
CXX_LIBS=-lgsoap++

# Global config
APPNAME=$(SCHEMA_NAME)

remake_cgi: clean cgi

cgi: xsd_stubs
	$(CXX) $(CXX_FLAGS) -o $(APPNAME).cgi $(APPNAME).cpp $(STUB_OUTPUT_DIR)/*.cpp $(CXX_LIBS)

xsd_stubs: xsd_headers $(STUB_OUTPUT_DIR)/$(SCHEMA_NAME).h $(STUB_OUTPUT_DIR)
	$(STUBGEN) $(STUBGEN_FLAGS) $(STUB_OUTPUT_DIR)/$(SCHEMA_NAME).h -d$(STUB_OUTPUT_DIR)/

xsd_headers: $(SCHEMA_DIR)/$(SCHEMA_NAME).xsd
	mkdir $(STUB_OUTPUT_DIR)/
	$(SCHEMA_2_H) $(SCHEMA_DIR)/$(SCHEMA_NAME).xsd -o $(STUB_OUTPUT_DIR)/$(SCHEMA_NAME).h

clean:
	rm -rf $(STUB_OUTPUT_DIR) $(APPNAME).cgi
