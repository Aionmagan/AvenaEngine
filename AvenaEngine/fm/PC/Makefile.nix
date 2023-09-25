TARGET := $(GAME_NAME)
CC = gcc 
CFLAGS += -D__PC__=1 
#CFLAGS += -D__PC__=1 -D__DEBUG__=1
LIBS = -lm -lpng -lSDL2 -lSDL2main -lGL -lGLU 
OBJS := render.o ctrl.o mesh.o obj.o \
		pngloader.o aabb.o audio.o timer.o \
		md2.o vec3.o $(OBJ)

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

clean: 
	rm -f $(OBJS) $(TARGET) 

run: $(TARGET)
	./$(TARGET)
