# Cutland URM (Unlimited Registers Machine)

# [What it is all about](https://www.deepnet42.com/post/2023/02/10/an-unlimited-register-machine/)

# Implementation details

1) Registers are 0 indexed
2) Lines are indexed starting from 1
3) Rope is self-expandable

# Syntax

In Cutland's URM we would write
```c
J(1,2,3)
```

but here we would write

```c
J 1 2 3
```

# Example

```c
#include "urm/urm.h"

int main()
{
    const TextBuffer code = read_file("examples/sum.urm");
    Rope rope = {0};

    rope_set(&rope, 0, 5);
    rope_set(&rope, 1, 2);

    urm_exec(&rope, &code);

    assert(*rope_get(&rope, 0) == 7, "5 + 2 != 7");
}
```

# References

- "Computability: An Introduction to Recursive Function Theory" by Nigel Cutland
