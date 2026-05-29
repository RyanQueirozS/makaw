# Conventions

## Architecture

Check out [architecture.md](architecture.md).

## Modules

| Module Name | snake_case Prefix | PascalCase Prefix | ALL_CAPS  Prefix |
| ----------- | ----------------- | ----------------- | ---------------- |
| `makaw`     | `makaw_`          | `Makaw`           | `MAKAW_`         |
| `core`      | `mkw_core_`       | `MkwCore`         | `MKW_CORE`       |
| `platform`  | `mkw_platform`    | `MakawPlatform`   | `MKW_PLATFORM`   |
| `utils `    | `makaw_`          | `Makaw`           | `MAKAW_`         |

All modules can include from `utils` except `platform`. Dependencies must only
be at `platform` layer

## Submodules

These should follow the rules mentioned above, but append their (submodule) name.

makaw_**runtime**, core_**windowing**, platform_**gfx_gl**, just to name a few.

## General rules

1. Return early whenever possible, avoid the use of `else` statements
2. Avoid creating unnecessary empty lines.
3. Use types that have already been implemented
4. No jump statements
5. Log all possible errors
6. Assert whenever something is critical
7. Organize code through comments:
    ```
    /*========================================================
     * Section of code
     *========================================================*/
    ```
8. Use `const` whenever possible
9. Prefer `typedef`s to real types (not data structures) and public data
   structures

## Naming

1. Public declaration (defined in a header file) must have it's module prefix
as it's own prefix:
> `my_func` in the core module will be: `mkw_core_my_func`, same rule to
> submodules.

1. Non public declaration presented in a source (.c) do not need a prefix.

2. Non public functions (declared in a .c) that are only used once should be
   prefixed with a `_`.

3. For scoped declarations (inside funcs, structs, unions, etc), rules 1-3 do
   not apply.

4. Only use single variable names inside loops.

5. Common names present are:
    - `count`, (preferable over size)
    - `length`, (preferable over size)
    - `array`, (preferable when plural barely modifies the word, only adds an
      -s or -es)
    
    Example:
    ```
    item_size // could be mistaken by size in bytes, sizeof()
    item_count // definitely amount of items
    
    // Use count as something that will be incremented, and length as a readonly value
    
    items // bad, barely distinguishable from item
    item_array // great, it is definitely an array
    
    vertices // good, visually different from vertex
    vertex_array // good as well
    
    // Another reason for the array suffix is that some types or vars might already
    // be in plural, therefore it will be hard to guess which ones are arrays and
    // which are just in plural
    
    birds // might just be a var named birds or it might be an array of bird elements.
    ```

6. Prefer to give the context as early as possible through it's name or type:
    ```
    // Another example:
    int position_mouse;    // Awful
    int position_screen_x;
    int position_screen_y;
    
    // Better:
    int mouse_position;    // Position is at the and and it's main characteristic
    int x_screen_position; // is in it's beginning
    int y_screen_position;
    
    // Even better for larger sets:
    struct {
        int mouse;
        int screen_x, screen_y;
        ...
    } positions; // Now I know that every member in here will be related to a position,
                 // I just need to look at the member's name.
    ```
 
7. Other naming rules are present individually at the end of this document.

## Case style

snake_case: 

- all non constant variables,
- scoped constant variables (.c file and functions),
- function parameters,
- struct members,
- all functions

PascalCase:
- structs,
- typedefs,
- enums,
- unions,
- opaque types

ALL_CAPS:
- header guards
- enum constants,
- feature flags,
- platform constants,
- header defined constant values

> **_NOTE:_**: Some items follow strict naming rules, check the end of the file
> for those

## Files

File names and directories must be `snake_case`d

## Specific naming conditions

1. `Header guards` must contain the full path from the source code's root
   directory. my_dir/my_file.h `MY_DIR_MY_FILE_H`.

2. Pointer params that modify the data must be suffixed with `_out`.

3. Pointer params that read and modify the data must be suffixed with `_inout`.

4. Function style `macros` MUST use a _M at the end.

5. `Enums members` must include the name of it's enum type. Example: enum
   `FooBar` will have it's members start with `FOO_BAR`
