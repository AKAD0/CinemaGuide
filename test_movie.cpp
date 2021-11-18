#include <gtest/gtest.h>
#include "movie.cpp"

TEST(bad_comment, t1) {
    comment new_comment;
    new_comment.set_comment(1, 1, "Неудачный фильм");
    bool b_c = bad_comment(new_comment);
    EXPECT_TRUE(b_c);
}

TEST(bad_comment, t2) {
    comment new_comment;
    new_comment.set_comment(1, 1, "Дерьмо");
    bool b_c = bad_comment(new_comment);
    EXPECT_TRUE(b_c);
}

TEST(bad_comment, t3) {
    comment new_comment;
    new_comment.set_comment(1, 1, "Угарный фильм");
    bool b_c = bad_comment(new_comment);
    EXPECT_TRUE(b_c);
}

TEST(bad_comment, t4) {
    comment new_comment;
    new_comment.set_comment(1, 1, "Не понравился! Имеет много сюжетных дыр. Никому не советую!!");
    bool b_c = bad_comment(new_comment);
    EXPECT_TRUE(b_c);
}

TEST(bad_comment, t5) {
    comment new_comment;
    new_comment.set_comment(1, 1, "Фильм просто супер)) Я в восторге!!");
    bool b_c = bad_comment(new_comment);
    EXPECT_TRUE(b_c);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
