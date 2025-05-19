# Enari

## Anotations

Usar o comando abaixo para voltar a user o C++ com otimizações.

`g++ -O2 -std=c++17 main.cpp -o main`

```json
// To run the file in C++, you need to create one tasks.json, using this code:
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Compilar C++",
      "type": "shell",
      "command": "g++",
      "args": [
        "-Wall",
        "-Wextra",
        "-g",
        "${file}",
        "-o",
        "${fileDirname}/output.exe"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"],
      "detail": "Compilação padrão de C++"
    }
  ]
}
```