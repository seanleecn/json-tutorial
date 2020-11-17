#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leptjson.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

// 如果宏里有多过一个语句，就需要用 do { /*...*/ } while(0) 包裹成单个语句
// 否则预处理之后(文本替换)后, 宏定义中的内容会分成多个语句
#define EXPECT_EQ_BASE(equality, expect, actual, format)                      \
                                                                              \
    do {                                                                      \
        test_count++;                                                         \
        if (equality)                                                         \
            test_pass++;                                                      \
        else {                                                                \
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", \
                    __FILE__, __LINE__, expect, actual);                      \
            main_ret = 1;                                                     \
        }                                                                     \
    } while (0)

// 测试宏: 如果 expect != actual（预期值不等于实际值），便会输出错误信息
#define EXPECT_EQ_INT(expect, actual) \
    EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

// static表示是一个全局的静态函数,该函数不能被别的文件调用的
static void test_parse_null() {
    lept_value v;
    v.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "null"));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_expect_value() {
    lept_value v;

    v.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_EXPECT_VALUE, lept_parse(&v, ""));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));

    v.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_EXPECT_VALUE, lept_parse(&v, " "));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_invalid_value() {
    lept_value v;
    v.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, lept_parse(&v, "nul"));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));

    v.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, lept_parse(&v, "?"));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_root_not_singular() {
    lept_value v;
    v.type = LEPT_FALSE;
    /* 作业1: 修正 LEPT_PARSE_ROOT_NOT_SINGULAR */
    // 从报错信息可以找到报错的行数是下面这一行,即输入"null x"的时候会
    EXPECT_EQ_INT(LEPT_PARSE_ROOT_NOT_SINGULAR, lept_parse(&v, "null x"));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse() {
    // 在下面四个函数中,一共调用了12次EXPECT_EQ_INT,也就是说进行了12次测试
    test_parse_null();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
}

int main() {
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count,
           test_pass * 100.0 / test_count);
    return main_ret;
}
