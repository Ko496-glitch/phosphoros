Phosphoros
Phosphoros is the debugger component of the Hecate project.

Hecate
The Hecate project is a system-level toolchain composed of three parts:

Brimo (The Compiler) LLVM/Clang-based compiler

Phosphoros (The Debugger) Debugger for inspecting and controlling execution

Perses (The Operating System) Custom operating system (Yards)

Overview
The first version of Phosphoros is being implemented in C++.

The goal is to build a working debugger with:

process control
memory and register inspection
execution control
Once a stable version is complete, the design will be reworked and implemented in Rust, focusing on safety, concurrency, and long-term maintainability.

Structure
phosphoros/
├── kdb/
│   ├── include/
│   ├── src/
│   ├── tools/
│   └── test/
Status
Work in progress.

