cmake_minimum_required (VERSION 2.6)
project (MathScraps)

set (MathScraps_VERSION_MAJOR 1)
set (MathScraps_VERSION_MINOR 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

include_directories("${PROJECT_BINARY_DIR}")
