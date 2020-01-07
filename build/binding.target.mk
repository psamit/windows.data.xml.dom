# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := binding
### Rules for final target.
LDFLAGS_Debug := \
	-pthread \
	-rdynamic \
	-m64

LDFLAGS_Release := \
	-pthread \
	-rdynamic \
	-m64

LIBS :=

$(obj).target/binding.node: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/binding.node: LIBS := $(LIBS)
$(obj).target/binding.node: TOOLSET := $(TOOLSET)
$(obj).target/binding.node:  FORCE_DO_CMD
	$(call do_cmd,solink_module)

all_deps += $(obj).target/binding.node
# Add target alias
.PHONY: binding
binding: $(builddir)/binding.node

# Copy this to the executable output path.
$(builddir)/binding.node: TOOLSET := $(TOOLSET)
$(builddir)/binding.node: $(obj).target/binding.node FORCE_DO_CMD
	$(call do_cmd,copy)

all_deps += $(builddir)/binding.node
# Short alias for building this executable.
.PHONY: binding.node
binding.node: $(obj).target/binding.node $(builddir)/binding.node

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/binding.node

