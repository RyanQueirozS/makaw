# Architecture

## File format

Project follows this dir format, where each dir can be considered a **module**:

- makaw/ 
- core/
- platform/
- utils/
- scripts/

Where:

- `makaw` is the 'api' **module**, where most user access information,
  abstracting from core.
- `core` abstracts platform specific code, it's also where most of the
  library's logic is.
- `platform` contains platform specific code, this ranges from OS, libs, apis
  and any other different form of 'low level' code.
- `utils` contains utilities, this is ONLY used in `core` and `makaw`
  **modules**. Platform uses plain C, and it's own helper functions, and data
  structures.
- `scripts` hold scripts used by `core`.

### Files

Files must be `lower_case`, and either a `.c` or `.h`.

## Modules

Each **module** must prefix each global or externally accessible piece of code
with it's given name (except `scripts`):

- `makaw`'s prefis is: `makaw_` or `Makaw`
- `core`'s prefix is: `mkw_core_` or `MkwCore`
- `platform`'s prefix is: `mkw_platform` or `MkwPlatform`
- `utils`' is: `makaw_` or `Makaw`, same as `makaw`.

### File Hierarchy

Each File and module MUST only include files from the same
**[submodule](#submodules)** or ONE submodule lower. Therefore, a lower level
abstraction CANNOT include code from a highly abstracted piece of code: 

````
├── bar.c // can include files on fizz and buzz, but not on fizz_subdir.
├── fizz/
│   ├── fizz_file1.c // These three are all on the same level and one CAN include the other's
│   ├── fizz_file2.c // header file (same submodule). Can include files under fizz_subdir 
│   ├── fizz_file3.c // (1 down). They cannot include bar (1 up) nor buzz (same level).
│   │
│   └── fizz_subdir/
│       └── fiz_subdir_file.c // Can not include anyone but it's own header file
│
└── buzz/
    └── buzz_file.c  // Cannot include fizz (same level) nor bar (1 up).
````

This rule applies also to different `modules` where each might have a submodule
with the same name, the hierarchy rules on that submodule will be treated as if
it were a part of the same `module` 

**Module `core_gfx` will be at the same level in terms of file hierarchy (even
though they do different things and are on completely different levels of
abstraction) as `platform_gfx`. BUT `platform` WILL NEVER include
`core`.**


### Submodules:

Inside each **module** there are '**submodules**', these help to subdivide and
group logic lexically. 

These submodules MUST be subdivided into separate directories, so a `gfx`
submodule will contain it's own `gfx` dir.

Different modules might share a common submodule name like the `gfx`
**submodule** in `core` and `platform`, where graphics related code is written.
Even though it is used in two **modules**, the rules of those **modules**
(`core` and `platform`) stand out and guide how `gfx` should be written in each
case. In `core`, gfx handles renderer related code in an overall higher level
abstraction; and in `platform`, it handles specific rendering apis like OpenGL
or Vulkan.

These **submodules** should APPEND to the already set prefix of each
**module**, example: 
- module `core`, submodule `gfx` => `mkw_core_gfx_<name>`
- module `platform`, submodule `gfx` => `mkw_platform_gfx_<name>`
