## 简介

一整套的样例

PROJECT
├── scripts             # 脚本，包含构建和调试所需的配置文件
├── build               # 编译输出目录，存放生成的二进制文件和其他构建产物
├── CMakeLists.txt      # 工程配置文件，定义了构建过程和依赖关系
├── Platform            # 平台库，包含硬件抽象层和标准库
├── .vscode             # VSCode工程配置，包含调试和任务设置
│   ├── tasks.json       # 任务设置，包含编译、下载、烧录等任务
│   ├── launch.json      # 调试配置，包含调试器和调试参数
│   └── c_cpp_properties.json # 编译器配置，包含编译器路径、标准库路径、宏定义等
│
└── Application         # 应用代码，包含主程序和其他应用逻辑
    ├── CMakeLists.txt  # 样例目录
    ├── BoardDemo       # 裸跑样例
    └── BoardRTOSDemo   # FreeRTOS样例

样例的管理由cmake实现

在 tasks.json 中配置
```
...
{
    "label": "cmake",
    "type": "shell",
    "command": "cmake",
    "args": [
        "-G",
        "MinGW Makefiles",
        "..",
        "-DDEVICE_TYPE=STM32F407ZGTX",
        "-DBOOT=ON",
        "-DFREERTOS=ON",
        "-DRELEASE=ON",
        "-DBOARD_TYPE=BOARD_DEMO",  //裸跑样例
        // "-DBOARD_TYPE=BOARD_RTOS_DEMO", //FreeRTOS样例
    ],
    "dependsOn": [
        "clean",
    ]
},
...
```

