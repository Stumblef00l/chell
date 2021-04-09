#include <gtest/gtest.h>
#include <decoder.hpp>
#include <string.h>

TEST(TestDecoder, TestStandardDecode) {
    char lineArgs[] = "line input test\n";
    char** argv = Decoder::decode(lineArgs);
    int argc = 0;
    while(argv[argc] != NULL)
        argc++;
    ASSERT_EQ(argc, 3) << "argc does not match\n";
    ASSERT_EQ(strcmp(argv[0], "line"), 0) << "Parsed args do not match\n";
    ASSERT_EQ(strcmp(argv[1], "input"), 0) << "Parsed args do not match\n";
    ASSERT_EQ(strcmp(argv[2], "test"), 0) << "Parsed args do not match\n";
}