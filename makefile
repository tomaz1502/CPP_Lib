CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++1z -Wshadow -Wfloat-equal -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector
