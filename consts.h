#ifndef CONSTS_H
#define CONSTS_H

#include <unordered_map>
#include <map>
#include <memory>
#include "QString"
#include "QList"
#include <cmath>
#include <vector>
#include "qfile.h"
#include "QApplication"

using std::vector;
using std::map;
using std::unordered_map;
using std::shared_ptr;
using std::make_shared;

enum CommandType {
    RUN, LOAD, CLEAR, HELP, QUIT, LIST
};

enum TokenType {
    // single-character token
    LEFT_PAREN, RIGHT_PAREN, PLUS, MINUS, STAR, SLASH,
    EQUAL, LESS, GREATER,

    // two-character token
    POWER,

    // literal
    IDENTIFIER, NUMBER,

    // keyword
    REM, LET, PRINT, INPUT, GOTO, IF, THEN, END,

    // comment
    COMMENT,

    // error
    ERROR
};

typedef unsigned long LineNum;

static QString HELP_MESSAGE = "=========== Basic Interpreter ===========\n"
                              "============== Made by Gzd ==============\n"
                              "1. 基本命令\n"
                              "   RUN:   运行保存在代码框中的程序\n"
                              "   LOAD:  从本地文件中读入.basic文件\n"
                              "   CLEAR: 清空所有文本框\n"
                              "   HELP:  显示帮助信息\n"
                              "   QUIT:  退出程序\n"
                              "\n"
                              "2. Basic语句\n"
                              "   REM: 注释\n"
                              "        用法: REM <comment>\n"
                              "   LET: 赋值语句\n"
                              "        用法: LET <variable> = <exp>\n"
                              "   PRINT: 输出语句\n"
                              "        用法: PRINT <expr>\n"
                              "   INPUT: 输入语句(在命令行中输入)\n"
                              "        用法: INPUT <variable>\n"
                              "   GOTO: 跳转语句\n"
                              "        用法: GOTO <line number>\n"
                              "   IF: 条件语句\n"
                              "        用法: IF <exp1> <op> <exp2> THEN <linenumber>\n"
                              "   END: 结束语句\n"
                              "        用法: END\n"
                              "\n"
                              "3. 命令行使用\n"
                              "   - 在命令行中先输入行号，然后输入程序\n"
                              "   - PRINT、INPUT、LET可以在命令行中不加行号地输入，但是如果从文件中输入，这三条语句必须带行号\n"
                              "   - 只输入行号不输入程序可以删除对应行上的语句(如果该语句已经存在)\n"
                              "   - 从文件中读入代码相当于将文件内容逐行输入命令行\n"
                              "更多细节请查看README";

#endif // CONSTS_H
