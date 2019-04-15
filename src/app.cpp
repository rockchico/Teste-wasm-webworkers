#include <stdio.h>
#include <iostream>
#include <string>
#include <emscripten.h>

#include <stdlib.h> // required for malloc definition


extern "C" 
{

    // Now it's "only" a matter of copying the data from JavaScript into wasm. For that, you need to expose two additional functions — one that allocates memory for the image inside wasm and one that frees it up again:

    EMSCRIPTEN_KEEPALIVE uint8_t* create_buffer(int width, int height) {
        return malloc(width * height * 4 * sizeof(uint8_t));
    }

    EMSCRIPTEN_KEEPALIVE void destroy_buffer(uint8_t* p) {
        free(p);
    }
    
    void EMSCRIPTEN_KEEPALIVE print_teste(int a, int b) { 

        printf("print: %s\n", "teste");

        printf("print: %d\n", a+b);

    }

    int EMSCRIPTEN_KEEPALIVE teste_soma(int a, int b) try { 

        return a * b;

    } catch (std::exception const& e) {
        printf("Exception thrown teste_soma: %s\n", e.what());
        return false;
    } catch (...) {
        printf("Unknown exception thrown teste_soma!\n");
        return false;
    }


    int EMSCRIPTEN_KEEPALIVE efWA(int len) try { 

        int i = 0; 
        int l = len;
        int r = 0;

        for (i = 0; i <= l; i++) {
            r = (r + l - i) - (r + l + i); // some random calculation here :p
        }
        
        
        return r;

    } catch (std::exception const& e) {
        printf("Exception thrown efWA: %s\n", e.what());
        return false;
    } catch (...) {
        printf("Unknown exception thrown efWA!\n");
        return false;
    }


}