# File System Study
Some code examples from 《文件系统技术内幕》

the config in c_cpp_properties.json:
```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "/usr/src/linux-headers-5.15.0-86-generic/arch/x86/include/generated",
                "/usr/src/linux-headers-5.15.0-86-generic/arch/x86/include",
                "/usr/src/linux-headers-5.15.0-86-generic/include",
                "${workspaceFolder}/**"
            ],
            "defines": [
                "__GNUC__",
                "__KERNEL__=1",
                "MODULE=1"
            ],
            "compilerPath": "/usr/bin/clang",
            "intelliSenseMode": "linux-clang-x64",
            "cStandard": "c17",
            "cppStandard": "c++17"
        }
    ],
    "version": 4
}
```

## Process
- my_simple_fs_mod.c --- done