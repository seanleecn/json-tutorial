// 宏的名字必须是唯一的，通常习惯以 _H__ 作为后缀。
// 由于 leptjson 只有一个头文件，可以简单命名为 LEPTJSON_H__
#ifndef LEPTJSON_H__
#define LEPTJSON_H__

// JSON 中有 6 种数据类型，如果把 true 和 false 当作两个类型就是 7 种
// 我们为此声明一个枚举类型（enumeration type）
typedef enum {
    LEPT_NULL,
    LEPT_FALSE,
    LEPT_TRUE,
    LEPT_NUMBER,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
} lept_type;

// JSON的数据结构
// 目前只实现 null, true 和 false 的解析，因此该结构体只需要存储一个 lept_type
typedef struct {
    lept_type type;
} lept_value;

// C语言的结构体定义是也要写成 struct X x
// 为方便使用，上面的代码使用了 typedef

// 返回值的枚举值
enum {
    LEPT_PARSE_OK = 0,  // 无错误
    // 下面是错误返回值,分别是1,2,3
    LEPT_PARSE_EXPECT_VALUE,      // 若JSON只含有空白
    LEPT_PARSE_INVALID_VALUE,     // 若值不是null true false
    LEPT_PARSE_ROOT_NOT_SINGULAR  // 若JSON的呈现<值-空白-值>的结构时
};

// API函数: 解析JSON
// 传入json且不改动,输出v
int lept_parse(lept_value* v, const char* json);

// API函数: 访问返回结果的函数,获取其类型
lept_type lept_get_type(const lept_value* v);

#endif /* LEPTJSON_H__ */
