#include <gtest/gtest.h>
#include <wish.hpp>
#include <string.h>

TEST(TestBatchMode, TestBatchInit) {
    char batchFile[] = "tests/TestBatchMode/test_batch_cmd.in";
    Wish wish = Wish(EXECUTION_MODES::BATCH, batchFile);
    ASSERT_EQ(wish.getMode(), EXECUTION_MODES::BATCH) << "Mode is not batch\n";
    ASSERT_EQ(strcmp(wish.getBatchFile(), "tests/TestBatchMode/test_batch_cmd.in"), 0) << "Incorrect batch command file\n"; 
    wish.run();
    ASSERT_EQ(wish.getError(), EXECUTION_ERROR::NOERR);
}
