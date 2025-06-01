CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TARGET = chess
SRCDIR = src
OBJDIR = obj

# Source files
SOURCES = main.cpp \
          $(SRCDIR)/utils/move.cpp \
          $(SRCDIR)/utils/move_parser.cpp \
          $(SRCDIR)/utils/path_validator.cpp \
          $(SRCDIR)/utils/move_validator.cpp \
          $(SRCDIR)/utils/board_renderer.cpp \
          $(SRCDIR)/pieces/sliding_piece.cpp \
          $(SRCDIR)/pieces/pawn.cpp \
          $(SRCDIR)/pieces/rook.cpp \
          $(SRCDIR)/pieces/knight.cpp \
          $(SRCDIR)/pieces/bishop.cpp \
          $(SRCDIR)/pieces/queen.cpp \
          $(SRCDIR)/pieces/king.cpp \
          $(SRCDIR)/board/chessboard.cpp \
          $(SRCDIR)/game/game_state.cpp \
          $(SRCDIR)/game/chess_game.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Create target directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Rebuild everything
rebuild: clean all

# Performance test
PERF_TARGET = perf_test
PERF_SOURCES = performance_test.cpp \
               $(SRCDIR)/utils/move.cpp \
               $(SRCDIR)/utils/move_parser.cpp \
               $(SRCDIR)/utils/path_validator.cpp \
               $(SRCDIR)/utils/move_validator.cpp \
               $(SRCDIR)/utils/board_renderer.cpp \
               $(SRCDIR)/pieces/sliding_piece.cpp \
               $(SRCDIR)/pieces/pawn.cpp \
               $(SRCDIR)/pieces/rook.cpp \
               $(SRCDIR)/pieces/knight.cpp \
               $(SRCDIR)/pieces/bishop.cpp \
               $(SRCDIR)/pieces/queen.cpp \
               $(SRCDIR)/pieces/king.cpp \
               $(SRCDIR)/board/chessboard.cpp \
               $(SRCDIR)/game/game_state.cpp \
               $(SRCDIR)/game/chess_game.cpp

PERF_OBJECTS = $(PERF_SOURCES:.cpp=.o)

performance_test: $(PERF_OBJECTS)
	$(CXX) $(PERF_OBJECTS) -o $(PERF_TARGET)
	./$(PERF_TARGET)

# Clean performance test files
clean_perf:
	rm -f $(PERF_TARGET) performance_test.o

.PHONY: all clean rebuild performance_test clean_perf 