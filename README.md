# URM (Unlimited Registers Machine)

# [How does it work?](https://www.deepnet42.com/post/2023/02/10/an-unlimited-register-machine/)

# Implementation details

1) Registers are 0 indexed
2) Lines are indexed starting from 1
3) Rope is self-expandable

# Syntax

```
<instruction> <arg_1> <arg_2> ... <arg_n>
```

# Example

```cpp
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
