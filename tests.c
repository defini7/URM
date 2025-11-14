#include "urm/urm.h"

void test_diff()
{
    Rope rope = {0};

    rope_set(&rope, 0, 5);
    rope_set(&rope, 1, 2);

    urm_do_file("examples/diff.urm", &rope, 10000);

    assert(*rope_get(&rope, 0) == 3, "test_diff failed");
}

void test_double()
{
    Rope rope = {0};

    rope_set(&rope, 0, 5);

    urm_do_file("examples/double.urm", &rope, 10000);

    assert(*rope_get(&rope, 0) == 10, "test_double failed");
}

void test_equal1()
{
    Rope rope = {0};

    rope_set(&rope, 0, 5);
    rope_set(&rope, 1, 3);

    urm_do_file("examples/equal.urm", &rope, 10000);

    assert(*rope_get(&rope, 0) == 0, "test_equal #1 failed");
}

void test_equal2()
{
    Rope rope = {0};

    rope_set(&rope, 0, 5);
    rope_set(&rope, 1, 5);

    urm_do_file("examples/equal.urm", &rope, 10000);

    assert(*rope_get(&rope, 0) == 1, "test_equal #2 failed");
}

void test_max()
{
    Rope rope = {0};

    rope_set(&rope, 0, 2);
    rope_set(&rope, 1, 7);

    urm_do_file("examples/max.urm", &rope, 10000);

    assert(*rope_get(&rope, 0) == 7, "test_max failed");
}

void test_mul()
{
    Rope rope = {0};

    rope_set(&rope, 0, 2);
    rope_set(&rope, 1, 7);

    urm_do_file("examples/mul.urm", &rope, 10000);

    assert(*rope_get(&rope, 0) == 14, "test_mul failed");
}

void test_half()
{
    Rope rope = {0};

    rope_set(&rope, 0, 6);

    urm_do_file("examples/half.urm", &rope, 10000);

    assert(*rope_get(&rope, 1) == 3, "test_half failed");
}

void test_sg()
{
    Rope rope = {0};

    rope_set(&rope, 0, 6);

    urm_do_file("examples/sg.urm", &rope, 10000);

    assert(*rope_get(&rope, 1) == 0, "test_sg failed");
}

void test_sum()
{
    Rope rope = {0};

    rope_set(&rope, 0, 5);
    rope_set(&rope, 1, 2);

    urm_do_file("examples/sum.urm", &rope, 10000);

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
