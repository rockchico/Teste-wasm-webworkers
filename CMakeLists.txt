project (AppWasm C CXX) # nome do projeto
cmake_minimum_required(VERSION 3.0)

if (EMSCRIPTEN)
	
    add_executable (app_wasm src/app.cpp) # arquivo executável

    # após a compilação, copia o arquivo app_tcc_wasm.js para a pasta do projeto web
    add_custom_command(TARGET app_wasm POST_BUILD
                      COMMAND ${CMAKE_COMMAND} -E copy_if_different
                      ${CMAKE_CURRENT_BINARY_DIR}/app_wasm.js
                      /var/www/html/LinuxDev/Teste-wasm-webworkers/www/app_wasm.js)
                      
    # após a compilação, copia o arquivo app_tcc_wasm.js para a pasta do projeto web
    add_custom_command(TARGET app_wasm POST_BUILD
                      COMMAND ${CMAKE_COMMAND} -E copy_if_different
                      ${CMAKE_CURRENT_BINARY_DIR}/app_wasm.wasm
                      /var/www/html/LinuxDev/Teste-wasm-webworkers/www/app_wasm.wasm)

endif()

if(UNIX)
    
    # flags compilação Emscripten
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z --llvm-lto 1 --bind -s WASM=1 ")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=0 ")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ASSERTIONS=2 ")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s DISABLE_EXCEPTION_CATCHING=0 -s NO_FILESYSTEM=1 ")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_EXIT_RUNTIME=1 ")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --memory-init-file 0 -O3 ")

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXTRA_EXPORTED_RUNTIME_METHODS='[\"cwrap\", \"ccall\", \"allocate\", \"intArrayFromString\", \"ALLOC_NORMAL\", \"UTF8ToString\"]' ")

    
    

	
	if(DEFINED CMAKE_BUILD_TYPE)
		SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE})
	else()
	    SET(CMAKE_BUILD_TYPE Release)
    endif()

endif()



