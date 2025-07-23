CC=gcc
CFLAGS=-Wall -Wextra -std=c99
TARGET=tetris
SOURCE=tetris.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	@echo "Building Ubuntu-BSD Tetris..."
	@if ! pkg-config --exists ncurses; then \
		echo ""; \
		echo "ERROR: NCurses library not found!"; \
		echo ""; \
		echo "Please install it first:"; \
		echo "  sudo apt install libncurses-dev"; \
		echo ""; \
		echo "Then run 'make' again."; \
		echo ""; \
		exit 1; \
	fi
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) -lncurses
	@echo "Build complete! Run with: ./tetris"

install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/
	@echo "Tetris installed! Run 'tetris' from anywhere."

clean:
	rm -f $(TARGET)
	@echo "Clean complete."

uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "Tetris uninstalled."

.PHONY: all clean install uninstall
