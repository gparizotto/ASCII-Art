cmake_minimum_required(VERSION 3.0)
project(MeuProjeto)

# Encontre o pacote do OpenCV
find_package(OpenCV REQUIRED)

# Adicione a biblioteca X11
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

# Verifique se o argumento do arquivo foi fornecido
if (NOT FILE_TO_COMPILE)
    message(FATAL_ERROR "Você precisa fornecer o arquivo .cpp a ser compilado. Use -DFILE_TO_COMPILE=<nome_do_arquivo>")
endif()


# Verifique se o arquivo selecionado existe
if (NOT EXISTS ${CMAKE_SOURCE_DIR}/${FILE_TO_COMPILE})
    message(FATAL_ERROR "Arquivo selecionado não encontrado: ${FILE_TO_COMPILE}")
endif()

# Obtenha o nome do arquivo sem a extensão
get_filename_component(FILE_NAME ${FILE_TO_COMPILE} NAME_WE)

# Adicione o executável para o arquivo selecionado
add_executable(${FILE_NAME} ${FILE_TO_COMPILE})

# Vincule as bibliotecas do OpenCV ao executável
target_link_libraries(${FILE_NAME} PRIVATE ${OpenCV_LIBS} ${X11_LIBRARIES})

