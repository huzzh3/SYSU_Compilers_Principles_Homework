# 编译原理：词法分析程序实验

18327034 胡泽钊 19 级软件工程

---

## 0 序言

* **若想要重编译此代码**，请确保自己的电脑中有 `gtk-3.0` 的运行环境，以保证 `#include <gtk/gtk.h>` 可以正常使用，建议使用 `vscode` 重编译此代码，且修改工程目录下的 `.vscode/c_cpp_properties.json` 中的 `includePath` 下的文件路径为自己的 `msys64` 路径。
* 具体的 `msys64` 安装和 `gtk-3.0` 的安装请参考 [vscode配置GTK开发环境 · IceSandwich](https://icesandwich.github.io/2020/03/21/vscode配置GTK开发环境/)

* 如若按照上文配置好环境以后，编译此程序只需要在含有 `makefile` 文件的目录下使用 `make run` 指令即可编译运行。
* **若只是单纯的需要运行此程序的话**，请直接执行 `bin/main.exe` 文件 或 在含有 `MakeFile` 的文件目录下使用 `make justRun` 指令。

---

## 1 实验说明

### 1.1 实验目的

* 扩充已有的样例语言TINY，为扩展TINY语言TINY＋构造词法分析程序，从而掌握词法分析的构造方法 。

---

### 1.2 实验内容

* 了解样例语言TINY及TINY编译器的实现。
* 了解扩展TINY语言TINY＋。
* 用C语言扩展TINY的词法分析。


---

### 1.3 实验要求

* 将TINY＋源程序翻译成对应的TOKEN序列。
* 该程序能检查一定的词法错误。

---

### 1.4 TINY 语言

#### 1.4.1 lexicon

+ Keywords:  **IF ELSE WRITE READ RETURN BEGIN END MAIN INT REAL**

+ Single-character separators：` ;` `,` `(`  `)`

+ Single-character operators：`+` `-` `*`  `/`

+ Multi-character operators：`:=` `==` `!=`

+ Identifier: An identifier consists of a letter followed by any number of letters or digits. The following are examples of identifiers: x, x2, xx2, x2x, End, END2. Note that **End** is an identifier while **END** is a keyword. The following are not identifiers:

  + `IF, WRITE, READ, ...` (keywords are not counted as identifiers)
  + `2x `(identifier can not start with a digit)
  + Strings in comments are not identifiers.

+ Number is a sequence of digits, or a sequence of digits followed by a dot, and followed by digits.  

  ```
  Number -> Digits | Digits '.' Digits
  Digits -> Digit | Digit Digits
  Digit  -> '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
  ```

+ Comments： string between `/**` and `**/`. Comments can be longer than one line. 

#### 1.4.2 Sample program

```
 /** this is a comment line in the sample program **/
 INT f2(INT x, INT y ) 
 BEGIN 
    INT z;
    z := x*x - y*y;
    RETURN z; 
 END 
 INT MAIN f1() 
 BEGIN
    INT x;
    READ(x, "A41.input");
    INT y;
    READ(y, "A42.input");
    INT z;
    z := f2(x,y) + f2(y,x);
    WRITE (z, "A4.otput"); 
 END
```

---

### 1.5 TINY＋

* 我们在 `TINY` 的词法基础上增加了以下词法：
  * Keywords： **WHILE** 、**DO**、**FOR**、**UPTO**、**DOWNTO**
  * Single-character operators：`%`（求余运算），`<`，`>`（比较运算符）

---

## 2 运行结果

### 2.1 程序使用说明

* 直接运行程序，结果如下：

![compilerhw1Run1](https://markdown-pictures-huzzh3.oss-cn-beijing.aliyuncs.com/img/softwareTesting/compilerhw1Run1.png)

* 点击 `Read TINY File` 按钮，即可打开选取文件页面，如下所示：

![compilerhw1ChooseFile](https://markdown-pictures-huzzh3.oss-cn-beijing.aliyuncs.com/img/softwareTesting/compilerhw1ChooseFile.png)

* 选择我在工程目录下 `test` 文件夹中提供的 `test1.tiny` 文件，结果如下所示：

![compilerhw1ShowTINYVIEW](https://markdown-pictures-huzzh3.oss-cn-beijing.aliyuncs.com/img/compilerHW/compilerhw1ShowTINYVIEW.png)

* 点击 `Lexical Analysis` 按钮，即可得到词法分析结果：

![compilerhw1ShowResView](https://markdown-pictures-huzzh3.oss-cn-beijing.aliyuncs.com/img/compilerHW/compilerhw1ShowResView.png)

* 其中 `test1.tiny` 文件是词法正确的 `tiny` 文件，由于词法分析的结果太长，截图无法截全，具体的结果可以参考如下：

```
(KEYWORD, INT)
(ID, f2)
(SEP, ()
(KEYWORD, INT)
(ID, x)
(SEP, ,)
(KEYWORD, INT)
(ID, y)
(SEP, ))
(KEYWORD, BEGIN)
(KEYWORD, INT)
(ID, z)
(SEP, ;)
(ID, z)
(OP, :=)
(NUM, 10)
(SEP, ;)
(KEYWORD, WHILE)
(SEP, ()
(ID, z)
(OP, >)
(NUM, 0)
(SEP, ))
(ID, z)
(OP, :=)
(ID, z)
(OP, %)
(NUM, 2)
(SEP, ;)
(KEYWORD, RETURN)
(ID, z)
(SEP, ;)
(KEYWORD, END)
(KEYWORD, INT)
(KEYWORD, MAIN)
(ID, f1)
(SEP, ()
(SEP, ))
(KEYWORD, BEGIN)
(KEYWORD, INT)
(ID, x)
(SEP, ;)
(KEYWORD, READ)
(SEP, ()
(ID, x)
(SEP, ,)
(STRING, A41.input)
(SEP, ))
(SEP, ;)
(KEYWORD, INT)
(ID, y)
(SEP, ;)
(KEYWORD, READ)
(SEP, ()
(ID, y)
(SEP, ,)
(STRING, A42.input)
(SEP, ))
(SEP, ;)
(KEYWORD, INT)
(ID, z)
(SEP, ;)
(ID, z)
(OP, :=)
(ID, f2)
(SEP, ()
(ID, x)
(SEP, ,)
(ID, y)
(SEP, ))
(OP, +)
(ID, f2)
(SEP, ()
(ID, y)
(SEP, ,)
(ID, x)
(SEP, ))
(SEP, ;)
(KEYWORD, FOR)
(ID, x)
(OP, :=)
(NUM, 10)
(SEP, ;)
(KEYWORD, DOWNTO)
(NUM, 5)
(KEYWORD, DO)
(ID, y)
(OP, :=)
(ID, x)
(SEP, ;)
(KEYWORD, WRITE)
(SEP, ()
(ID, z)
(SEP, ,)
(STRING, A4.output)
(SEP, ))
(SEP, ;)
(KEYWORD, END)

```

* 可以看到我们的词法分析结果是正确的。

---

### 2.2 错误检测

* 读入 `test2.tiny` 文件，在 `test2.tiny` 文件中，我将一处 `:=` 改成 `=` ，检查其是否能够查出错误，结果如下：

![compilerhw1Error1](https://markdown-pictures-huzzh3.oss-cn-beijing.aliyuncs.com/img/compilerHW/compilerhw1Error1.png)

* 可以看到，程序检查出了一处错误，显示为 `error with '='`，和我们设置的一致。

* 我们读入 `test3.tiny` 文件，我们在原来正确的 `test1.tiny` 文件的末尾加入了 `@;` 的错误命令，分析结果如下所示：

![compilerhw1Error2](https://markdown-pictures-huzzh3.oss-cn-beijing.aliyuncs.com/img/compilerHW/compilerhw1Error2.png)

* 可以看到分析结果末尾查出了一处错误 `error with '@'`，可以看出我们的词法分析器是有一定的错误检查能力的。

---

## 3 程序说明

* 我们的词法分析程序其实运行逻辑十分简单，由于我们最终要产生 `token` 序列，我们定义的 `token` 的数据结构如下：

```c
// Token (Token type and str) 
typedef struct token {
    char *str;
    TokenType tokenType;
} token;
```

* 其中 `str` 是该 `token` 包含的内容，`TokenType` 是其类型。

* 根据我们定义的 `TINY+` 的词法，我们能够给出以下 `TokenType` ：

```c
// Token type
typedef enum {
    // Keywords
    IF, ELSE, WRITE, READ, RETURN, BEGIN, END, MAIN, INT, REAL, WHILE, DO, FOR, UPTO, DOWNTO,

    // Single-character separators
    SEMICOLON, COMMA, LEFT_PARENTHESIS, RIGHT_PARENTHESIS,

    // Single-character operators
    PLUS, MINUS, TIME, DIVIDE, MODULO, GREATER_THAN, LESS_THAN,

    // Multi-character operators
    ASSIGN, EQUAL, UNEQUAL,

    // Identifier, Number and String
    IDENTIFIER, NUMBER, STRING,

    // Other
    ERROR, ENDFILE
} TokenType;
```

* 至此，关于 `token` 的准备工作就做完了，接下来，由于我们要使用 `DFA` 来构造词法分析器，对应的，我们需要 `DFA` 状态，我们定义的 `DFA` 状态如下：

```c
// DFA status
typedef enum {
         START_STATUS,
        ASSIGN_STATUS,
         EQUAL_STATUS,
       UNEQUAL_STATUS,
       COMMENT_STATUS,
        NUMBER_STATUS,
          REAL_STATUS,
        STRING_STATUS,
    IDENTIFIER_STATUS,
        FINISH_STATUS,
} DFAStatus;
```

* 由于 `!=` 、`==` 、`:=` 是唯三双目运算符，所以我们要为它们分别单独设置一个 `DFA STATUS`，而其他的运算符都是单目运算符，所以通过 `FINISH_STATUS` 就可以完成状态的转换。

* 至此 `DFA` 的准备工作也完成了，接下来我们主要通过 `lexicalAnalysis.c` 文件中的 `getToken` 函数来实现词法分析，具体逻辑如下：

1. 首先设置 `currentStatus` 为 `START_STATUS` ，即设置 `DFA` 为初始状态。
1. 根据现在扫描的字符 `currentCharacter` 的类型来进行状态转移，如，`currentCharacter` 字符是数字，则转移状态为 `NUMBER_STATUS`，如下所示（其他的情况类似）：

```c
if (isdigit(currentCharacter)) {
	currentStatus = NUMBER_STATUS;
}
```

3. 之后设置其他状态的状态转移函数，如 `NUMBER_STATUS`，如下所示：

```c
case NUMBER_STATUS:
    if (!isdigit(currentCharacter)) {
        if (currentCharacter == '.') {
        	currentStatus = REAL_STATUS;
        }
        else {
            currentBufferIndex--;
            needToBeSaved = FALSE;
            currentStatus = FINISH_STATUS;
            currentTokenType  = NUMBER;
        }
    }
	break;
```

* 在这里，如果已经转移到了 `NUMBER_STATUS` 了以后，如果当前字符不是数字，则有以下两种情况：

  * 当前字符是 `.` ，就说明现在扫描的数据可能是 `REAL` 类型的数据，那么就转移状态到 `REAL_STATUS`。
  * 当前字符不是 `.` ，就说明 `NUMBER` 的扫描已经结束，我们将扫描指针会退，并设置状态为完成状态，即 `FINISH_STATUS`。

* 如果当前字符是数字的话，则状态不会变化，会继续扫描。

* 当处于完成状态了以后，那么就会调用函数，输出 `token` 如下所示：

```c
char *tokenInString = getTokenInStringFromTokenTypeAndString(currentTokenType, tokenString);
```

* 上面只介绍了 `NUMBER` 的情况，其他的情况与此类似。

---

