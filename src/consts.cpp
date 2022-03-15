#include "consts.h"

const QString PRINTF_PLACEHOLDER = "{}";
const QString SPACE = "    ";
const QString HELP_MESSAGE = "=========== Basic Interpreter ===========\n"
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
                             "   INPUT: 输入整数(在命令行中输入)\n"
                             "        用法: INPUT <variable>\n"
                             "   INPUTS: 输入字符串(在命令行中输入)\n"
                             "        用法: INPUTS <variable>\n"
                             "   GOTO: 跳转语句\n"
                             "        用法: GOTO <line number>\n"
                             "   IF: 条件语句\n"
                             "        用法: IF <exp1> <op> <exp2> THEN <linenumber>\n"
                             "   PRINTF: 格式化输出语句\n"
                             "        用法: PRINTF <format>, <param1>, <param2>...\n"
                             "              变量的占位符用\"{}\"表示，中间不能有空格"
                             "   END: 结束语句\n"
                             "        用法: END\n"
                             "\n"
                             "3. 命令行使用\n"
                             "   - 在命令行中先输入行号，然后输入程序\n"
                             "   - PRINT、INPUT、INPUTS、LET、PRINTF可以在命令行中不加行号地输入，但是如果从文件中输入，这三条语句必须带行号\n"
                             "   - 只输入行号不输入程序可以删除对应行上的语句(如果该语句已经存在)\n"
                             "   - 从文件中读入代码相当于将文件内容逐行输入命令行\n"
                             "更多细节请查看README";

const QColor RED = QColor(255, 100, 100);
const QColor GREEN = QColor(100, 255, 100);

const unordered_map<QString, CommandType> COMMANDS {
    { "RUN", CommandType::RUN },
    { "LOAD", CommandType::LOAD },
    { "CLEAR", CommandType::CLEAR },
    { "HELP", CommandType::HELP },
    { "SAVE", CommandType::SAVE },
    { "DEBUG", CommandType::DEBUG },
    { "QUIT", CommandType::QUIT },
    { "LIST", CommandType::LIST },
};
