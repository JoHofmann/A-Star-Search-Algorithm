# --- add headers for IDE support ---
# message(${a_star_search_SOURCE_DIR})
set(HEADER_LIST "../include/a_star/")

# --- add libraries ---
add_library(a_starLib
  ${HEADER_LIST}
  a_star.cpp
  node.cpp
)

# We need this directory, and users of our library will need it too
target_include_directories(a_starLib PUBLIC ../include)

# All users of this library will need at least C++11
target_compile_features(a_starLib PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
# source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})

