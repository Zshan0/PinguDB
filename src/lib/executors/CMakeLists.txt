add_library(DATABASE_EXEC
  cross.cpp
  distinct.cpp
  export.cpp
  index.cpp
  join.cpp
  list.cpp
  load.cpp
  print.cpp
  projection.cpp
  rename.cpp
  selection.cpp
  sort.cpp
  source.cpp
  transpose.cpp
)

target_include_directories(DATABASE_EXEC PUBLIC ../../include)
