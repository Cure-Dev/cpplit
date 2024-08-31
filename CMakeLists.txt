cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lit)

# Dependencies
set(DEPS_DIR ${PROJECT_SOURCE_DIR}/deps) # set dependencies directory
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".so" ".lib" ".dll" ".dylib")

## GMP
set(GMP_DIR ${DEPS_DIR}/gmp)
find_library(GMP_LIBRARY NAMES gmp PATHS ${GMP_DIR}/lib NO_DEFAULT_PATH REQUIRED) 
find_library(GMPXX_LIBRARY NAMES gmpxx PATHS ${GMP_DIR}/lib NO_DEFAULT_PATH REQUIRED)

## Losh
set(LOSH_DIR ${DEPS_DIR}/losh)
find_library(LOSH_LIBRARY NAMES losh PATHS ${LOSH_DIR}/lib NO_DEFAULT_PATH REQUIRED)

## codec
set(CODEC_DIR ${DEPS_DIR}/codec)
find_library(CODEC_LIBRARY NAMES codec PATHS ${CODEC_DIR}/lib NO_DEFAULT_PATH REQUIRED)

## number_converter
set(NUMBER_CONVERTER_DIR ${DEPS_DIR}/number_converter)
find_library(NUMBER_CONVERTER_LIBRARY NAMES number_converter PATHS ${NUMBER_CONVERTER_DIR}/lib NO_DEFAULT_PATH REQUIRED)

## ranges
set(RANGES_DIR ${DEPS_DIR}/ranges)
find_library(RANGES_LIBRARY NAMES ranges PATHS ${RANGES_DIR}/lib NO_DEFAULT_PATH REQUIRED)

## trie
set(TRIE_DIR ${DEPS_DIR}/trie)

include_directories("src/exceptions") #..
include_directories("src/language") #..

# sources
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

## tokens
add_library(${PROJECT_NAME}_tokens INTERFACE)
target_include_directories(${PROJECT_NAME}_tokens INTERFACE "${SOURCE_DIR}/tokens/include")

target_include_directories(${PROJECT_NAME}_tokens INTERFACE ${CODEC_DIR}/include)

## file reader
set(READER_DIR "${SOURCE_DIR}/reader")
file(GLOB_RECURSE READER_SOURCES "${READER_DIR}/implement/*.cpp")
add_library(${PROJECT_NAME}_reader STATIC ${READER_SOURCES})

target_include_directories(${PROJECT_NAME}_reader PRIVATE "${READER_DIR}/internal")
target_include_directories(${PROJECT_NAME}_reader INTERFACE "${READER_DIR}/interface")
target_include_directories(${PROJECT_NAME}_reader PUBLIC "${READER_DIR}/include")

target_include_directories(${PROJECT_NAME}_reader PUBLIC "${SOURCE_DIR}/char_stream/include")

target_include_directories(${PROJECT_NAME}_reader PRIVATE ${CODEC_DIR}/include)
target_link_libraries(${PROJECT_NAME}_reader PUBLIC ${CODEC_LIBRARY}) # 资源会浪费吗？

## scanner
set(SCANNER_DIR "${SOURCE_DIR}/scanner")
file(GLOB_RECURSE SCANNER_SOURCES "${SCANNER_DIR}/implement/*.cpp")
list(FILTER SCANNER_SOURCES EXCLUDE REGEX ".*old\\.cpp$")
add_library(${PROJECT_NAME}_scanner STATIC ${SCANNER_SOURCES}) # scanner_lib?

target_include_directories(${PROJECT_NAME}_scanner INTERFACE "${SCANNER_DIR}/interface")
target_include_directories(${PROJECT_NAME}_scanner INTERFACE "${SCANNER_DIR}/include")
target_include_directories(${PROJECT_NAME}_scanner PRIVATE "${SCANNER_DIR}/include/scanner")
target_include_directories(${PROJECT_NAME}_scanner PRIVATE "${SCANNER_DIR}/internal")

target_include_directories(${PROJECT_NAME}_scanner PUBLIC "${SOURCE_DIR}/char_stream/include")
target_include_directories(${PROJECT_NAME}_scanner PUBLIC "${SOURCE_DIR}/input_device/include")

target_include_directories(${PROJECT_NAME}_scanner PRIVATE ${CODEC_DIR}/include)
target_include_directories(${PROJECT_NAME}_scanner PRIVATE ${NUMBER_CONVERTER_DIR}/include)
target_link_libraries(${PROJECT_NAME}_scanner PRIVATE ${NUMBER_CONVERTER_LIBRARY})

target_include_directories(${PROJECT_NAME}_scanner PRIVATE ${RANGES_DIR}/include)
target_link_libraries(${PROJECT_NAME}_scanner PUBLIC ${RANGES_LIBRARY})

target_include_directories(${PROJECT_NAME}_scanner PRIVATE ${TRIE_DIR}/include)

target_link_libraries(${PROJECT_NAME}_scanner PRIVATE ${PROJECT_NAME}_tokens)

## parser
set(PARSER_DIR "${SOURCE_DIR}/parser")
file(GLOB_RECURSE PARSER_SOURCES "${PARSER_DIR}/implement/*.cpp")
list(FILTER PARSER_SOURCES EXCLUDE REGEX ".*old\\.cpp$")

add_library(${PROJECT_NAME}_parser STATIC ${PARSER_SOURCES})
target_include_directories(${PROJECT_NAME}_parser INTERFACE "${PARSER_DIR}/interface")
target_include_directories(${PROJECT_NAME}_parser PUBLIC "${PARSER_DIR}/include")
target_include_directories(${PROJECT_NAME}_parser PRIVATE "${PARSER_DIR}/internal")

target_include_directories(${PROJECT_NAME}_parser PRIVATE src/scanner/internal) #utils/position
target_include_directories(${PROJECT_NAME}_parser PRIVATE ${CODEC_DIR}/include)

target_link_libraries(${PROJECT_NAME}_parser PRIVATE ${PROJECT_NAME}_tokens)

## ast
set(AST_DIR "${SOURCE_DIR}/ast")
file(GLOB_RECURSE AST_SOURCES "${AST_DIR}/implement/*.cpp")
list(FILTER AST_SOURCES EXCLUDE REGEX ".*old\\.cpp$")

add_library(${PROJECT_NAME}_ast STATIC ${AST_SOURCES})
target_include_directories(${PROJECT_NAME}_ast PUBLIC "${AST_DIR}/include")
target_include_directories(${PROJECT_NAME}_ast PRIVATE "${AST_DIR}/internal")

target_include_directories(${PROJECT_NAME}_ast PUBLIC "src/runtime")
target_include_directories(${PROJECT_NAME}_ast PUBLIC "src/project")

target_link_libraries(${PROJECT_NAME}_ast PRIVATE ${PROJECT_NAME}_tokens)

target_include_directories(${PROJECT_NAME}_ast PRIVATE ${CODEC_DIR}/include)

## semantic (data model)
file(GLOB_RECURSE SEMANTIC_SOURCES "${SOURCE_DIR}/semantic/*.cpp")
list(FILTER SEMANTIC_SOURCES EXCLUDE REGEX ".*old\\.cpp$")
add_library(${PROJECT_NAME}_semantic STATIC ${SEMANTIC_SOURCES})
target_include_directories(${PROJECT_NAME}_semantic PUBLIC "${SOURCE_DIR}/semantic/include")

target_include_directories(${PROJECT_NAME}_semantic PRIVATE ${CODEC_DIR}/include) # or link library?

target_include_directories(${PROJECT_NAME}_semantic PUBLIC ${GMP_DIR}/include) #..
target_link_libraries(${PROJECT_NAME}_semantic PRIVATE ${GMP_LIBRARY}) #gmpxx?


## ui
file(GLOB_RECURSE UI_SOURCES "${SOURCE_DIR}/ui/*.cpp")
list(FILTER UI_SOURCES EXCLUDE REGEX ".*old\\.cpp$")

add_executable(${PROJECT_NAME} ${UI_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SOURCE_DIR}/ui/include")

target_link_libraries(${PROJECT_NAME}_ast PRIVATE ${PROJECT_NAME}_semantic)
target_link_libraries(${PROJECT_NAME}_parser PRIVATE ${PROJECT_NAME}_ast)
target_link_libraries(${PROJECT_NAME}_parser PRIVATE ${PROJECT_NAME}_semantic)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_semantic) #utils/call_method need
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_reader) #ui/main
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_scanner) #ui/main
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_parser)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_tokens) #ui/main
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_ast)

target_include_directories(${PROJECT_NAME} PRIVATE ${LOSH_DIR}/include) #ui
target_link_libraries(${PROJECT_NAME} ${LOSH_LIBRARY})

target_link_libraries(${PROJECT_NAME} ${GMPXX_LIBRARY} ${GMP_LIBRARY}) # ui temp?

install(
  TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_scanner ${PROJECT_NAME}_parser
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  # INCLUDES DESTINATION include
)
install(DIRECTORY src/scanner/include/ src/scanner/interface/ DESTINATION include/scanner)
install(DIRECTORY src/parser/include/ src/parser/interface/ DESTINATION include/parser)

add_custom_target(uninstall
  COMMAND xargs rm < install_manifest.txt
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Uninstalling...")