#mkdir ./build
#cd ./build
#cmake ..
#make -j4
#doxygen ../doc/Doxyfile
#./08_async
#seq 0 82115 | ./bulkmt 4
#ltrace -e malloc -e free ./tree_04
#valgrind --tool=memcheck seq 0 10 | ./bulkmt 3
#valgrind --leak-check=full --show-leak-kinds=all seq 1 8213 | ./bulkmt 3
valgrind --leak-check=full --show-leak-kinds=all ./CompRoutes

