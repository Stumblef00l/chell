#include <gtest/gtest.h>
#include <wish.hpp>
#include <string.h>
#include <config.h>

TEST(TestBatchMode, TestBatchInit) {
    std::string batchFile = PROJECT_SOURCE_DIR;
    batchFile += "/tests/test_batch_cmd.in";
    Wish wish = Wish(EXECUTION_MODES::BATCH, batchFile.c_str());
    ASSERT_EQ(wish.getMode(), EXECUTION_MODES::BATCH) << "Mode is not batch\n";
    ASSERT_EQ(strcmp(wish.getBatchFile(), batchFile.c_str()), 0) << "Incorrect batch command file\n"; 
}

TEST(TestBatchMode, TestBatchNoFile) {
    const char batchFile[] = "nofile.txt";
    Wish wish = Wish(EXECUTION_MODES::BATCH, batchFile);
    wish.run();
    ASSERT_EQ(wish.getError(), EXECUTION_ERROR::NOFILE) << "File does not exist was expected but file was found\n";
}

TEST(TestBatchMode, TestExecCount) {
    std::string batchFile = PROJECT_SOURCE_DIR;
    batchFile += "/tests/test_batch_cmd.in";
    Wish wish = Wish(EXECUTION_MODES::BATCH, batchFile.c_str());
    wish.run();
    ASSERT_EQ(wish.getError(), EXECUTION_ERROR::EOEXEC);
    ASSERT_EQ(wish.getProcessedCount(), 2);
}
