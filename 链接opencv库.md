
# GCC 编译器参数 -l, -L, 和 -I 使用说明

## 一、基础知识

标准库函数通常位于 `libc.a`（静态库）或 `libc.so`（动态库）。这些库文件一般存放在 `/lib/` 或 `/usr/lib/` 目录下，或者在GCC默认搜索的其他目录中。

当使用GCC编译和链接程序时，默认会自动链接到上述的标准库。然而，对于非标准库或第三方库，则需要手动添加。

## 二、-l 参数（小写 L）

`-l` 参数允许用户手动添加链接库。例如，若要使用 `<math.h>` 中定义的函数如 `cos()`，则需通过 `-lm` 来链接数学库。

### 示例代码 (`main.c`)

```c
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main() {
    double param = 60.0, result;
    result = cos(param * PI / 180.0);
    printf("The cosine of %f degrees is %f.\n", param, result);
    return 0;
}
```

编译命令示例：
```bash
gcc main.c -o main.out -lm
```

## 三、-L 参数

该参数用于指定查找库文件的目录。除了标准目录外，如果想链接其他目录中的库，则需要使用 `-L` 指定路径。

### 示例
```bash
gcc main.c -o main.out -L /usr/lib -lm
```

可以使用多个 `-L` 选项，或在一个 `-L` 后面用冒号分隔多个路径。

## 四、-I 参数（大写 i）

`-I` 参数用来指定头文件的搜索目录。默认情况下，GCC知道去 `/usr/include` 目录查找头文件。但如果头文件不在该目录下，则需用 `-I` 指定新的搜索路径。

### 示例
```bash
gcc -o example1 example1.c -I /usr/local/include/freetype2 -lfreetype -lm
```

上述命令表示，在编译 `example1.c` 时，首先会在 `/usr/local/include/freetype2` 目录中查找头文件。
