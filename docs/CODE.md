## makic.h

### struct type_s / type_t

Define un tipo o asume un tipo.

> e.g.: int(type_s) var1 = 0;
```c
typedef struct type_s {
    mctype_e type; // int, char, etc
    struct def_s *def; // def de un tipo
    struct type_s *next; // permite encadenar varios tipos
    struct type_s *aux_type; // retorna type o var en caso de ser función, puntero o variable
    int num_parms; // -1 = num of variable args. e.g.: en C es ...
    struct type_s *parm_types[MAX_PARMS] // only [NUM_PARMS] allocated, limit: 8
} type_t;
```

### struct def_s / def_t

    obtain def_t
    type -> int
    name -> var1
    ofs -> 4 (where is saved as example)
    scope -> NULL (bcs global var)
    initialized -> 1 or 0 (was initialized with "= 0")

> e.g.: int var1 = 21;

```c
typedef struct def_s {
    type_t *type; // obtains type of data defined from type_t
    const char *name; // name of var e.g.: main, my_function
    struct def_s *next; // obtains a array of definitions
    gofs_t ofs; // set in-memory location where the data is allocated
    struct def_s *scope; // scope of function or block where was defined.
                            // if is NULL, is a global var
    int initialized; // var is initialized on declaration e.g.: 1 or 0
} def_t;
```