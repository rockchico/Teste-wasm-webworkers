#include <stdio.h>
#include <iostream>
#include <string>

#include <emscripten.h>



extern "C" 
{

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
        int l = 10000000000 + len;
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