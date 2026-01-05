#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <bx/bx.h>
#include <bx/error.h>
#include <bx/allocator.h>
#include <bimg/bimg.h>
#include <bimg/decode.h>

__AFL_FUZZ_INIT();

bx::DefaultAllocator g_allocator;

int main(int argc, char** argv) {
    
    while (__AFL_LOOP(10000)) {
        size_t len = __AFL_FUZZ_TESTCASE_LEN;
        const uint8_t* buf = __AFL_FUZZ_TESTCASE_BUF;

        if (len < 16) continue;

        bx::Error err;
        bimg::ImageContainer* image = bimg::imageParse(&g_allocator, buf, (uint32_t)len, bimg::TextureFormat::Count, &err);

        if (image != NULL) {
            bimg::imageFree(image);
        }
    }

    return 0;
}
