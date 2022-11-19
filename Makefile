# Parameter
YAXI_BACKEND ?= minilibx

# Folders
SOURCE_PATH := src
CACHE_PATH  := cache
HEADER_PATH := include

SUB_FOLDERS := image_formats $(YAXI_BACKEND)
SOURCE_SUBS := $(addprefix $(SOURCE_PATH)/,$(SUB_FOLDERS))
CACHE_SUBS  := $(addprefix $(CACHE_PATH)/,$(SUB_FOLDERS))

# Files
NAME          := yaxi
TARGET_STATIC := lib$(NAME).a
TARGET_SHARED := lib$(NAME).so
FILES         := $(shell find $(SOURCE_SUBS) $(SOURCE_PATH) -maxdepth 1 -name '*.c')
OBJECTS       := $(FILES:$(SOURCE_PATH)%.c=$(CACHE_PATH)%.o)

# Compiler
CC       ?= gcc
CFLAGS   += -Wall -Wextra
CPPFLAGS += -I $(HEADER_PATH)

static: $(TARGET_STATIC)

shared: $(TARGET_SHARED)

$(TARGET_STATIC): $(OBJECTS)
	$(AR) rcs $@ $^

$(TARGET_SHARED): $(OBJECTS)
	$(CC) -shared $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(CACHE_PATH)/%.o: $(SOURCE_PATH)/%.c | $(CACHE_PATH)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(CACHE_PATH):
	mkdir -p $(CACHE_SUBS)

clean:
	$(RM) -r $(CACHE_PATH)

fclean: clean
	$(RM) $(TARGET_STATIC) $(TARGET_SHARED)

.PHONY: static shared clean fclean
