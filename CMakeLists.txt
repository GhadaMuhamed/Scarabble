cmake_minimum_required(VERSION 3.8)
project(Scrabble)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SuperLeavesTrie/SuperLeavesTrie.h SuperLeavesTrie/SuperLeavesTrie.cpp Heuristic/Heuristic.cpp Heuristic/Heuristic.h Simulate/simulate.cpp Simulate/simulate.h Bstar/Bstar.cpp Bstar/Bstar.h Bag/Bag.cpp Bag/Bag.h Board/Board.cpp Board/Board.h Player/Player.cpp Player/Player.h Move/Move.h Move/Move.cpp Judge/Judge.cpp Judge/Judge.h Dictionary/dictionary.cpp Dictionary/dictionary.h Dictionary/GADDAG.h Dictionary/GADDAG.cpp main.cpp )
add_executable(Scrabble ${SOURCE_FILES})