/* Date: 2023-2-17 20:48
*  Author: qiang
*  Decription: output debug info with color
*
*  print color format:
*     "\033[[function-fomat] background-color;font-color  messgae \033[0m"
*
*  background-color        font-color                  
*     40: black(黑)            30: black(黑)
*     41: red(红)              31: red(红)
*     42: green(绿)            32: green(绿)
*     43: yellow(黄)           33: yellow(黄)
*     44: blue(蓝)             34: blue(蓝)
*     45: purple(紫)           35: purple(紫)
*     46: dark green(深绿)     36: dark green(深绿)
*     47: white(白色)          37: white(白色)
*
*  function-fomat:
*    0: close all attribute
*    5: flashing
*
*  complie:
*      g++ debug_tool.cc -o debug_tool
*/

#include <stdio.h>
#include <iostream>

#define debug_error(format, ...) { \
     printf("\033[0;31m[%s:%s:%d] "format"\033[0m\n",  __FILE__, __FUNCTION__, __LINE__ , __VA_ARGS__ );\
}

#define debug_info(format, ...) { \
     printf("\033[0;32m[%s:%s:%d] "format"\033[0m\n", __FILE__, __FUNCTION__, __LINE__ , __VA_ARGS__ );\
}

#define debug_info_1(...) { \
    std::cout << "\033[0;32m" << "["<< __FILE__<<":"<< __FUNCTION__<< ":" <<__LINE__<< "] " \
              << __VA_ARGS__ << "\033[0m"<<std::endl; \
}

int main(int argc, char *argv[])
{
    printf("\033[5;40;31m ==== hello world ====\033[0m\n");
    printf("\033[5;31m ==== hello world ====\033[0m\n");
    debug_info("%s, %d", "hello world", 100);
    debug_info("%s, %d", "hello world", 100);
    debug_info_1("hello world"<< std::hex << ", 0x" << 100);
    return 0;
}


