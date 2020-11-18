#include "leptjson.h"
#include <assert.h> /* assert() */
#include <stdlib.h> /* NULL */

#define EXPECT(c, ch)             \
    do {                          \
        assert(*c->json == (ch)); \
        c->json++;                \
    } while (0)

// 为了减少参数,把所有要传递的数据打包到结构体中
// 当前只存储 JSON 字符的位置
// 之后要加入更多的东西
typedef struct {
    const char* json;
} lept_context;

/* 处理whilespace部分 */
static void lept_parse_whitespace(lept_context* c) {
    const char* p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

/* 解析null值 */
static int lept_parse_null(lept_context* c, lept_value* v) {
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}

/* 解析true值 */
static int lept_parse_true(lept_context* c, lept_value* v) {
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_TRUE;
    return LEPT_PARSE_OK;
}

/* 解析false值 */
static int lept_parse_false(lept_context* c, lept_value* v) {
    EXPECT(c, 'f');
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 4;
    v->type = LEPT_FALSE;
    return LEPT_PARSE_OK;
}

/* 解析值的部分,要处理null,true,false */
#ifndef SOLUTION
/* 作业3: 实现true/false解析 */
static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
        case 'n':
            return lept_parse_null(c, v);
        case '\0':
            return LEPT_PARSE_EXPECT_VALUE;  // 枚举值1
        default:
            return LEPT_PARSE_INVALID_VALUE;  // 枚举值2
    }
}
#else

static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
        case 't':
            return lept_parse_true(c, v);
        case 'f':
            return lept_parse_false(c, v);
        case 'n':
            return lept_parse_null(c, v);
        case '\0':
            return LEPT_PARSE_EXPECT_VALUE;  // 枚举值1
        default:
            return LEPT_PARSE_INVALID_VALUE;  // 枚举值2
    }
}
#endif

/* 实现解析器 */
// JSON 文本由 3 部分组成，首先是空白（whitespace），接着是一个值，最后是空白。
#ifndef SOLUTION
int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    return lept_parse_value(&c, v);
}
#else

/* 作业1: 由于原函数只处理了JSON中<空白-值>两部分,下面加上检查值后面的空白 */
int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    int ret;
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    if ((ret = lept_parse_value(&c, v)) == LEPT_PARSE_OK) {
        lept_parse_whitespace(&c);
        if (*c.json != '\0')
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
    }
    return ret;
}
#endif

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}
