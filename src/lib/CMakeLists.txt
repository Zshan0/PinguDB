add_library(DATABASE_LIB 
  bufferManager.cpp
  clear.cpp
  cursor.cpp
  executor.cpp
  logger.cpp
  matrixCatalogue.cpp
  matrix.cpp
  page.cpp
  semanticParser.cpp
  syntacticParser.cpp
  tableCatalogue.cpp
  table.cpp
)

target_include_directories(DATABASE_LIB PUBLIC ../include)

target_link_libraries(DATABASE_LIB PUBLIC DATABASE_EXEC)

add_subdirectory(executors)
