CC=g++
CFLAGC=-c -Wall -fpic
CFLAGS=-shared
INCLUDES=-IInclude
APPINCLUDE=./Source/main.cpp
OUTPUT=run
#Compile and build engine to a shared lib
engine:
	$(CC) $(CFLAGC) $(INCLUDES) ./Source/Core.cpp -o Core.o
	$(CC) $(CFLAGC) $(INCLUDES) ./Source/Input.cpp -o Input.o
	$(CC) $(CFLAGC) $(INCLUDES) ./Source/Timer.cpp -o Timer.o
	$(CC) $(CFLAGC) $(INCLUDES) ./Source/Vector.cpp -o Vector.o
	$(CC) $(CFLAGC) $(INCLUDES) ./Source/FileReader.cpp -o FileReader.o
	$(CC) $(CFLAGC) $(INCLUDES) ./Source/Shader.cpp -o Shader.o
	$(CC) $(CFLAGC) $(INCLUDES) ./Source/ShaderManager.cpp -o ShaderManager.o
	$(CC) $(CFLAGC) $(INCLUDES) ./Source/GameObject.cpp -o GameObject.o
	$(CC) $(CFLAGC) $(INCLUDES) ./Source/PrimitiveShapes.cpp -o PrimitiveShapes.o
	#$(CC) $(CFLAGC) $(INCLUDES) ./Source/External/stb_image.cpp -o stb_image.o
	$(CC) $(CFLAGS) ./FileReader.o ./PrimitiveShapes.o ./GameObject.o ./Vector.o ./ShaderManager.o ./Shader.o ./Core.o ./Input.o ./Timer.o -o engine.so
#Compile application to object code
application:
	$(CC) -c -fpic -IInclude $(APPINCLUDE) -o app.o
#Link GL libs , engine libs and application code
link:
	$(CC) ./app.o ./engine.so /usr/lib64/libGLEW.so.2.1 /usr/local/lib/libglfw.so -lGL -o $(OUTPUT)
clean:
	rm -f ./*.so ./*.o ./$(OUTPUT)
run:
	./$(OUTPUT)
all: clean engine application link