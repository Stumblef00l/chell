#include <gtest/gtest.h>
#include <wish.hpp>
#include <string.h>

TEST(TestBatchMode, TestBatchInit) {
    char batchFile[] = "test_batch_cmd.in";
    Wish wish = Wish(EXECUTION_MODES::BATCH, batchFile);
    ASSERT_EQ(wish.getMode(), EXECUTION_MODES::BATCH) << "Mode is not batch\n";
    ASSERT_EQ(strcmp(wish.getBatchFile(), "test_batch_cmd.in"), 0) << "Incorrect batch command file\n"; 
}

TEST(TestBatchMode, TestBatchNoFile) {
    char batchFile[] = "nofile.txt";
    Wish wish = Wish(EXECUTION_MODES::BATCH, batchFile);
    wish.run();
    ASSERT_EQ(wish.getError(), EXECUTION_ERROR::NOFILE) << "File does not exist was expected but file was found\n";
}

TEST(TestBatchMode, TestExecCount) {
    char batchFile[] = "test_batch_cmd.in";
    Wish wish = Wish(EXECUTION_MODES::BATCH, batchFile);
    wish.run();
    ASSERT_EQ(wish.getError(), EXECUTION_ERROR::EOEXEC);
    ASSERT_EQ(wish.getProcessedCount(), 2);
}
