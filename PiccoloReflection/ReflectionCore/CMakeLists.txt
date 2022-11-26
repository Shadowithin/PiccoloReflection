
# PackageProject.cmake will be used to make our target installable
set(TARGET_NAME ReflectionCore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

#source_group(TREE "${ENGINE_ROOT_DIR}/schema" FILES ${SCHEMA_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PICCOLO_ROOT_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PICCOLO_ROOT_DIR}/bin)


# if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/schema/)
#   file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/schema/" DESTINATION "${CMAKE_BINARY_DIR}/schema")
# endif()

# if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/asset/)
#   file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/asset/" DESTINATION "${CMAKE_BINARY_DIR}/asset")
# endif()
# ---- Create library ----

# Note: for header-only libraries change all PUBLIC flags to INTERFACE and create an interface
# target: add_library(${TARGET_NAME} INTERFACE)
# add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})
add_executable(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "PiccoloReflection")

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/WX->")

# Link dependencies    
target_link_libraries(${TARGET_NAME} PRIVATE $<BUILD_INTERFACE:json11>)


target_include_directories(
  ${TARGET_NAME} 
  PUBLIC $<BUILD_INTERFACE:${REFLECTION_ROOT_DIR}>
  $<INSTALL_INTERFACE:include/${TARGET_NAME}-${PROJECT_VERSION}>
)


target_include_directories(
  ${TARGET_NAME} 
  PUBLIC $<BUILD_INTERFACE:${json_inlcude}>
)


target_include_directories(
  ${TARGET_NAME} 
  PUBLIC $<BUILD_INTERFACE:${REFLECTION_ROOT_DIR}/RelfectionCore>
  $<INSTALL_INTERFACE:include/${TARGET_NAME}-${PROJECT_VERSION}>
)


# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match the project's regular
# header paths
string(TOLOWER ${TARGET_NAME}/version.h VERSION_HEADER_LOCATION)


### precompile
# set global vari used by precompile
set(PICCOLO_RUNTIME_HEADS "${HEADER_FILES}" PARENT_SCOPE)
