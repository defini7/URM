#include "urm/urm.h"

void test_diff()
{
    const TextBuffer code = read_file("examples/diff.urm");
    Rope rope = {0};

    rope_set(&rope, 0, 5);
    rope_set(&rope, 1, 2);

    urm_exec(&rope, &code);

    assert(*rope_get(&rope, 0) == 3, "test_diff failed");
}

void test_double()
{
    const TextBuffer code = read_file("examples/double.urm");
    Rope rope = {0};

    rope_set(&rope, 0, 5);

    urm_exec(&rope, &code);

    assert(*rope_get(&rope, 0) == 10, "test_double failed");
}

void test_equal1()
{
    const TextBuffer code = read_file("examples/equal.urm");
    Rope rope = {0};

    rope_set(&rope, 0, 5);
    rope_set(&rope, 1, 3);

    urm_exec(&rope, &code);

    assert(*rope_get(&rope, 0) == 0, "test_equal #1 failed");
}

void test_equal2()
{
    const TextBuffer code = read_file("examples/equal.urm");
    Rope rope = {0};

    rope_set(&rope, 0, 5);
    rope_set(&rope, 1, 5);

    urm_exec(&rope, &code);

    assert(*rope_get(&rope, 0) == 1, "test_equal #2 failed");
}

void test_max()
{
    const TextBuffer code = read_file("examples/max.urm");
    Rope rope = {0};

    rope_set(&rope, 0, 2);
    rope_set(&rope, 1, 7);

    urm_exec(&rope, &code);

    assert(*rope_get(&rope, 0) == 7, "test_max failed");
}

void test_mul()
{
    const TextBuffer code = read_file("examples/mul.urm");
    Rope rope = {0};

    rope_set(&rope, 0, 2);
    rope_set(&rope, 1, 7);

    urm_exec(&rope, &code);

    assert(*rope_get(&rope, 0) == 14, "test_mul failed");
}

void test_half()
{
    const TextBuffer code = read_file("examples/half.urm");
    Rope rope = {0};

    rope_set(&rope, 0, 6);

    urm_exec(&rope, &code);

    assert(*rope_get(&rope, 1) == 3, "test_half failed");
}

void test_sg()
{
    const TextBuffer code = read_file("examples/sg.urm");
    Rope rope = {0};

    rope_set(&rope, 0, 6);

    urm_exec(&rope, &code);

    assert(*rope_get(&rope, 1) == 0, "test_sg failed");
}

void test_sum()
{
    const TextBuffer code = read_file("examples/sum.urm");
    Rope rope = {0};

    rope_set(&rope, 0, 5);
    rope_set(&rope, 1, 2);

    urm_exec(&rope, &code);

    assert(*rope_get(&rope, 0) == 7, "test_sum failed");
}

int main()
{
    test_diff();
    test_double();
    test_equal1();
    test_equal2();
    test_half();
    test_max();
    test_mul();
    test_sg();
    test_sum();

    printf("Ok!");
}
