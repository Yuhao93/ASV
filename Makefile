CC = g++
SRCS = src/*.cpp
LIBS = -lncurses -lopencv_core -lopencv_imgproc -lopencv_calib3d -lopencv_video -lopencv_features2d -lopencv_ml -lopencv_highgui -lopencv_objdetect -lopencv_contrib -lopencv_legacy
asv: $(SRCS)
	$(CC) -std=c++0x -I include $(SRCS) -o asv $(LIBS)
