TEST=test.out
VIEW_DIR=view/Viewer/
SOURCE_FILES=model/*.cpp
BD=./build/
BUILT_APP_PATH=
OS=$(shell uname)
CPP_CHECK=cppcheck --enable=all --suppress=unusedFunction \
					--suppress=missingInclude --suppress=unreadVariable \
					--language=c++ --std=c++17
ARCHIVE=3DViewer-2.00

ifeq ($(OS), Darwin)
	BUILT_APP_PATH=$(VIEW_DIR)Viewer.app/Contents/MacOS/Viewer
else 
ifeq ($(OS), Linux)
	BUILT_APP_PATH=$(VIEW_DIR)Viewer
endif
endif

.PHONY: tests all build clean_build install clean $(TEST)

all: install

install: build clean_build
	clear && echo "3D Viewer was installed in build directory"

# uninstall:
# 	rm -Rf $(BD)

# build:
# 	cd $(VIEW_DIR) && qmake Viewer.pro && make
# 	mkdir $(BD)
# 	cp $(BUILT_APP_PATH) $(BD)

check:
	cp ../materials/linters/.clang-format .
	clang-format -n model/*.cpp model/*.h
	$(CPP_CHECK) model/*.cpp model/*.h

	clang-format -n controller/*.cpp controller/*.h
	$(CPP_CHECK) controller/*.cpp controller/*.h

	clang-format -n $(VIEW_DIR)*.h $(VIEW_DIR)*.cpp
	$(CPP_CHECK) $(VIEW_DIR)*.h $(VIEW_DIR)*.cpp
	rm -f .clang-format

$(TEST):
	g++ $(SOURCE_FILES) -o $(TEST) -lgtest -lgtest_main -lpthread

tests: $(TEST)
	./$(TEST)

gcov_report: $(TEST)
	g++ --coverage $(SOURCE_FILES) -o $(TEST) -lgtest -lpthread
	./$(TEST)
	lcov -t $(TEST) --no-external -o test.info -c -d ./
	genhtml -o report test.info
	open report/index.html

# clean: clean_build  ЧЕКНУТЬ В ШКОЛЕ
clean:
	rm -f *.out *.o *.a $(TEST) *.gcda *.gcno *.info *.txt
	rm -Rf report
	rm -Rf $(BD) 
	rm -f $(ARCHIVE).tar.gz

clean_build:
	cd $(VIEW_DIR) && make clean && rm -Rf Calculator.app/ && rm -f .qmake.stash

dist:
	rm -rf $(ARCHIVE) && mkdir $(ARCHIVE)
	cp -r model controller view Makefile $(ARCHIVE)
	tar -czvf $(ARCHIVE).tar.gz $(ARCHIVE)
	rm -rf $(ARCHIVE)
