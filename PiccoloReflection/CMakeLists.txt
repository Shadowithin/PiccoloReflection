# CMakeList.txt: PiccoloReflection 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
set(TARGET_NAME PiccoloReflection)

set(REFLECTION_ROOT_DIR "${PICCOLO_ROOT_DIR}/PiccoloReflection")

# Json  第三方库
set(THIRD_PARTY_DIR "${REFLECTION_ROOT_DIR}/3rdparty")
set(json_inlcude ${THIRD_PARTY_DIR}/json11)
set(json_lib_dir ${THIRD_PARTY_DIR}/lib/json11)

add_library(json11 ${json_inlcude}/json11.cpp)
set_target_properties(json11 PROPERTIES FOLDER "ThirdParty/json11" )

set(CODEGEN_TARGET "PiccoloPreCompile")
set(PARSER_TARGET PiccoloParser)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ReflectionCore)

add_subdirectory(MetaParser)
add_subdirectory(ReflectionCore)

include("${REFLECTION_ROOT_DIR}/precompile/precompile.cmake")
set_target_properties("${CODEGEN_TARGET}" PROPERTIES FOLDER "PiccoloReflection" )

add_dependencies(ReflectionCore "${CODEGEN_TARGET}")
add_dependencies("${CODEGEN_TARGET}" "${PARSER_TARGET}")

# TODO: 如有需要，请添加测试并安装目标。
