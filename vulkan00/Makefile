BIN=flvulkan
SRC=Fl_Vulkan_Window.cxx fl_vulkan.mm main.cpp
SRC_H=Fl_Vulkan_Window.H fl_vulkan.H
CXX=clang++ -std=c++11
VULKAN_ROOT=$(HOME)/apps/vulkansdk-macos/macOS
CFLAGS=$(shell fltk-config --cflags) -I $(VULKAN_ROOT)/include
LDFLAGS=$(shell fltk-config --ldflags) -L $(VULKAN_ROOT)/lib
LIBS=$(shell fltk-config --libs) -lvulkan

all : $(BIN)

run : $(BIN)
	PATH=$(PATH):$(VULKAN_ROOT)/bin \
	VK_ICD_FILENAMES=$(VULKAN_ROOT)/etc/vulkan/icd.d/MoltenVK_icd.json \
	VK_LAYER_PATH=$(VULKAN_ROOT)/etc/vulkan/explicit_layers.d \
	DYLD_LIBRARY_PATH=$(VULKAN_ROOT)/lib \
	./$(BIN)

$(BIN) : $(SRC) $(SRC_H)
	$(CXX) -o $(BIN) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBS)

clean :
	rm -f $(BIN)
