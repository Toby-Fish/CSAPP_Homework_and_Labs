---
title: CSAPP-Homework
date: 2021-07-25 17:08:28
categories: 学习
comments: true
mathjax: true
---

各章节作业答案及简要解析

<!--more-->

# Chapter2

## 2.55

```
小端机

版本	Windows 10 家庭中文版
版本号	20H2
安装日期	‎2021/‎3/‎18
操作系统内部版本	19042.1110
序列号	PF1CBRHP
体验	Windows Feature Experience Pack 120.2212.3530.0
```

## 2.57

```c
typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
	size_t i;
	for (i = 0; i < len; i++)
		printf(" %.2x", start[i]);
	printf("\n");
}

void show_short(short x) {
	show_bytes((byte_pointer)&x, sizeof(short));
}

void show_int(int x) {
	show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x) {
	show_bytes((byte_pointer)&x, sizeof(float));
}

void show_long(long x) {
	show_bytes((byte_pointer)&x, sizeof(long));
}

void show_double(double x) {
	show_bytes((byte_pointer)&x, sizeof(double));
}
```

## 2.58

```c
int is_little_endian() {
	short s = 1;
	byte_pointer p = (byte_pointer)&s;
	return *p;
}
```

## 2.59

```c
int Problem_2_59_(int x, int y) {
	return (x & 0xFF) | (y & (~0xFF));
}
```

## 2.60

```c
unsigned replace_byte(unsigned x, int i, unsigned char b)
{
	unsigned mask = 0xFF << (i * 8);
	x = x & (~mask);
	return x | (b << (i * 8));
}
```

## 2.61

```c
int Problem_2_61_(int x) {
	int w = sizeof(int) << 3;
	return (x == -1) || (x == 0) || ((x & 0xFF) == 0xFF) || (!((x >> (w - 8)) & 0xFF));
}
```

## 2.62

```c
int int_shifts_are_arithmetic() {
	int x = -1;
	return (x >> 1) == x;
}
```

## 2.63

```c
unsigned srl(unsigned x, int k) {
	/* Perform shift arithmetically */
	unsigned xsra = (int)x >> k;
	int w = sizeof(int) << 3;
	int mask = (1 << (w - k)) - 1;
	return mask & xsra;
}

int sra(int x, int k) {
	/* Perform shift logically */
	int xsrl = (unsigned)x >> k;
	int w = sizeof(int) << 3;
	int z = 1 << (w - k - 1);
	int mask = z - 1;
	int right = mask & xsrl;
	int left = (~mask) & ((~(z & xsrl)) + z);
	return right | left;
}
```

## 2.64

```c
/* Return 1 when any odd bit of x euqals 1; 0 otherwise.
 * Assume w = 32
 */
int any_odd_one(unsigned x) {
	return !!(x & 0xAAAAAAAA);
}
```

## 2.65

```c
/* Return 1 when x contains an odd number of 1s; 0 otherwise.
 * Assume w = 32
 */
int odd_ones(unsigned x) {
	x = (x >> 16) ^ x;
	x = (x >> 8) ^ x;
	x = (x >> 4) ^ x;
	x = (x >> 2) ^ x;
	x = (x >> 1) ^ x;
	return x & 1;
}
```

## 2.66

```c
/* Generate mask indicating leftmost 1 in x.  Assume w = 32
 * For example, 0xFF00 --> 0x8000, and 0x6600 --> 0x4000
 * If x = 0, then return 0.
 */
int leftmost_ones(unsigned x) {
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	return x ^ (x >> 1);
}
```

## 2.67

```c
A. 移位应小于32位
/* Work successfully on 32-bit machine */
int  int_size_is_32_B() {
	int x = 1 << 31;
	return !(x << 1);
}

/* Work successfully on 16-bit machine */
int  int_size_is_32_C() {
	int x = 1 << 15;
	int y = x << 15;
	return (x << 1) && !(y << 2);
}
```

## 2.68

```c
/* 
 * Mask with least signficant n bits set to 1
 * Examples: n = 6 --> 0x3F, n == 17 --> 0x1FFFF
 * Assume 1 <= n <= w
 */
int lower_one_mask(int n) {
	return (2 << (n - 1)) - 1;
}
```

## 2.69

```c
/*
 * Do ratating left shift.  Assume 0 <= n < w
 * Examples when x = 0x12345678 and w = 32
 *	n = 4 -> 0x23456781, n = 20 -> 0x67812345
 */
unsigned rotate_left(unsigned x, int n) {
	/* Special treatment for the case of n = 0 */
	unsigned w = sizeof(unsigned) << 3;
	unsigned not_shift_out = ((1 << (w - n + 1)) - 1) & x;
	unsigned shift_out = ((((INT_MIN) >> n) << 1) & x) >> (w - n);
	unsigned rotated = (not_shift_out << n) | shift_out;
	/* If n != 0, rotated is the right answer, otherwise rotated is 0 */
	n = (n << 16) | n;
	n = (n << 8) | n;
	n = (n << 4) | n;
	n = (n << 2) | n;
	n = (n << 1) | n;
	n = n >> 31;
	/* n ? rotated : x */
	return (n & rotated) + ((~n) & x);
}
```

## 2.70

```c
/*
 * Return 1 when x can be represented as an n-bit, 2's-complement
 * number; 0 otherwise
 * Assume 1 <= n <= w
 */
int fits_bits(int x, int n) {
	/*
	 * If x is a positive number,
	 * ensure that x is shifted to 0 and 
	 * the highest bit of the new n-bit number is 0 
	 * 
	 * * If x is a negative number,
	 * ensure that x is shifted to -1 and 
	 * the highest bit of the new n-bit number is 1 
	 */
	int test_bit = (1 << (n - 1)) & x;
	x >>= n;
	return (!x && !test_bit) || (!(x + 1) && test_bit);
}
```

## 2.71

```c
A. 未实现符号拓展，高位总为0
/* Declaration of data type where 4 bytes are picked
 * into an unsigned
 */
typedef unsigned packed_t;

/* Extract byte from word.  Return as signed integer */
int xbyte(packed_t word, int bytenum) {
	return ((int)(word << ((3 - bytenum) << 3))) >> 24;
}

```

## 2.72

```c
A. 表达式隐式转换为无符号数结果，故总大于等于0
/* Copy integer into buffer if space is avaiable */
void copy_int(int val, void* buf, int maxbytes) {
	if (maxbytes > 0 && (maxbytes >= sizeof(val)))
		memcpy(buf, (void*)&val, sizeof(val));
}
```

## 2.73

```c
/* Addtion that saturates to TMin or Tmax */
int saturating_add(int x, int y) {
	int w = sizeof(int) << 3;
	int z = x + y;
	int _sign_x_ = x >> (w - 1);
	int _sign_y_ = y >> (w - 1);
	int _sign_z_ = z >> (w - 1);
	int _sign_xor_ = (x ^ y) >> (w - 1);
	/* 
	 * If x,y with different signs, addition does not overflow,
	 * ans = x + y. Otherwise ans is zero.
	 */
	int _ans_both_positive_ = (~_sign_x_) & (~_sign_y_) & _sign_z_ & INT_MAX;
	int _ans_both_negative_ = _sign_x_ & _sign_y_ & (~_sign_z_) & (INT_MIN);
	int _ans_xor_ = _sign_xor_ & (x + y);
	return _ans_both_positive_ + _ans_both_negative_ + _ans_xor_;
}
```

## 2.74

```c
/* Determine whether arguments can be substracted without overflow */
int tsub_ok(int x, int y) {
	int w = sizeof(int) << 3;
	int z = x - y;
	int _sign_x_ = x >> (w - 1);
	int _sign_y_ = y >> (w - 1);
	int _sign_z_ = z >> (w - 1);

	/*
	 * if x >= 0, y >= 0, x - y never overflow
	 * if x >= 0, y <  0, x - y may overflow, when overflow, _sign_z_ is all 1s
	 * if x <  0, y >= 0, x - y may overflow, when overflow, _sign_z_ is 0
	 * if x <  0, y <  0, x - y never overflow
	 */
	int _ans_xpyn_overflow_ = (~_sign_x_) & _sign_y_ & _sign_z_;
	int _ans_xnyp_overflow_ = _sign_x_ & (~_sign_y_) & (~_sign_z_);
	return !(_ans_xpyn_overflow_ || _ans_xnyp_overflow_);
}
```

## 2.75

```c
int signed_high_prod(int x, int y) {
	int w = sizeof(int) << 3;
	long tmp_x = (long)x;
	long tmp_y = (long)y;
	return (int)((tmp_x * tmp_y) >> w);
}
unsigned unsigned_high_prod(unsigned x, unsigned y) {
	int w = sizeof(int) << 3;
	unsigned x_sign = ((int)x) >> (w - 1);
	unsigned y_sign = ((int)y) >> (w - 1);
	unsigned ans = signed_high_prod(x, y) + (x_sign & y) + (y_sign & x);
	return ans;
}
```

## 2.76

```c
void* Calloc(size_t nmemb, size_t size) {
	if (nmemb == 0 || size == 0) return NULL;
	size_t total = nmemb * size;
	if (total / nmemb == size) {
		void* p = malloc(total);
		memset(p, 0, nmemb);
		return p;
	}
	return NULL;
}
```

## 2.77

```c
int Problem_2_77_A(int x) {
	return (x << 4) + x;
}
int Problem_2_77_B(int x) {
	return -(x << 3) + x;
}
int Problem_2_77_C(int x) {
	return (x << 6) - (x << 2);
}
int Problem_2_77_D(int x) {
	return -(x << 7) + (x << 4);
}
```

## 2.78

```c
/* Divide by power of 2. Assume 0 <= k < w - 1 */
int divide_power2(int x, int k) {
	int sign = x >> 31;
	int x_is_non_negative = x >> k;
	int x_is_negative = (x + ((1 << k) - 1)) >> k;
	return ((~sign) & x_is_non_negative) + (sign & x_is_negative);
}
```

## 2.79

```c
int mul3div4(int x) {
	return ((x << 1) + x) >> 2;
}
```

## 2.80

```c
int threefourths(int x) {
	/*
	 * calculate 3/4x, no overflow, round to zero
	 *
	 * no overflow means divide 4 first, then multiple 3, diffrent from 2.79 here
	 *
	 * rounding to zero is a little complicated.
	 * every int x, equals f(first 30 bit number) plus l(last 2 bit number)
	 *
	 *   f = x & ~0x3
	 *   l = x & 0x3
	 *   x = f + l
	 *   threeforths(x) = f/4*3 + l*3/4
	 *
	 * f doesn't care about round at all, we just care about rounding from l*3/4
	 *
	 *   lm3 = (l << 1) + l
	 *
	 * when x > 0, rounding to zero is easy
	 *
	 *   lm3d4 = lm3 >> 2
	 *
	 * when x < 0, rounding to zero acts like divide_power2 in 2.78
	 *
	 *   bias = 0x3    // (1 << 2) - 1
	 *   lm3d4 = (lm3 + bias) >> 2
	 */
	int is_negative = x & INT_MIN;
	/* Split x into high 30 digits and low two digits */
	int f = x & (~0b11);
	int l = x & (0b11);

	int fd4 = f >> 2;
	int fd4m3 = (fd4 << 1) + fd4;

	int lm3 = (l << 1) + l;
	int bias = (1 << 2) - 1;
	(is_negative && (lm3 += bias));
	int lm3d4 = lm3 >> 2;
	
	return fd4m3 + lm3d4;
}
```

## 2.81

```c
int Problem_2_81_A(int k) {
	int odd = k & 1;
	int ans = -1 << (k >> 1);
	return ans << ((k >> 1) + odd);
}

int Problem_2_81_B(int j, int k) {
	int w = sizeof(int) << 3;
	int exp = w - k;
	int odd_left_part = exp & 1;
	int odd_right_part = j & 1;
	unsigned ans = ~0;
	ans = (ans >> (exp >> 1)) >> ((exp >> 1) + odd_left_part);
	return (ans << (j >> 1)) << ((j >> 1) + odd_right_part);
}
```

## 2.82

```c
 * Problem_2_82
 * A. False (x = TMin, y = 0)
 * B. True
 * C. True
 * D. True
 * E. True
```

## 2.83

```c
 * Problem_2_83
 * Let x be the value of the infinite sequence,
 * then x * (2 ^ k) = Y + x.
 * So x = Y / ((2 ^ k) - 1)
 * 
 * B(a):5/7
 * B(b):6/15
 * B(c):19/63
```

## 2.84

```c
unsigned f2u(float f) {
	byte_pointer bp = (byte_pointer)&f;
	return (unsigned)(bp[0] + (bp[1] << 8) + (bp[2] << 16) + (bp[3] << 24));
}
int float_le(float x, float y) {
	unsigned ux = f2u(x);
	unsigned uy = f2u(y);

	/* Get the sign bits */
	unsigned sx = ux >> 31;
	unsigned sy = uy >> 31;

	/* Give an expression using only ux, uy, sx and sy */
	return (sx && !sy) || (sx && sy && (ux >= uy)) || (!sx && !sy && (ux <= uy));
}
```

## 2.85

```c
 * Problem_2_85
 * bias = (2 ^ (k - 1)) - 1;
 * 
 * A. 7.0 = ((bias + 2) << n) | (0b11 << (n - 2))
 * B. Greatest odd integer = ((bias + n) << n) | ((1 << n) - 1)
 * C. reciprocal of the minimum normalized number = ((2 ^ k) - 3) << n
```

## 2.90

```c
float u2f(unsigned u) {
	float f;
	byte_pointer up = (byte_pointer)&u;
	byte_pointer fp = (byte_pointer)&f;
	for (size_t i = 0;i < sizeof(unsigned);i++) {
		fp[i] = up[i];
	}
	return f;
}
float fpwr2(int x) {
	/* Result exponent and fraction */
	unsigned exp, frac;
	unsigned u;

	if (x < -149) {
		/* Too small.  Return 0.0 */
		exp = 0;
		frac = 0;
	}
	else if (x < -126) {
		/* Denormalized result */
		exp = 0;
		frac = 1 << (149 + x);
	}
	else if (x < 128) {
		/* Normalized result */
		exp = x + 127;
		frac = 0;
	}
	else {
		/* Too big.  Return Infinity*/
		exp = 0xFF;
		frac = 0;
	}

	/* Pack exp and frac into 32 bits */
	u = exp << 23 | frac;
	/* Return as float */
	return u2f(u);
}
```

## 2.92

```c
/* Compute -f.  If f is NaN, then return f. */
float_bits float_negate(float_bits f) {
	/* Decompose bit representation into parts */
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if (exp == 0xFF && frac) return f;
	return ((~sign) << 31) | (exp << 23) | frac;
}
```

## 2.93

```c
/* Compute |f|.  If f is NaN, then return f. */
float_bits float_absval(float_bits f) {
	/* Decompose bit representation into parts */
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if (exp == 0xFF && frac) return f;
	return (exp << 23) | frac;
}
```

## 2.94

```c
/* Compute 2*f.  If f is NaN, then return f. */
float_bits float_twice(float_bits f) {
	/* Decompose bit representation into parts */
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if (exp == 0xFF) return f;
	if (exp == 0) return (sign << 31) | (frac << 1);
	if (exp == 0xFE) return (sign << 31) | (0xFF << 23);
	return (sign << 31) | ((exp + 1) << 23) | frac;
}
```

## 2.95

```c
/* Compute 0.5*f.  If f is NaN, then return f. */
float_bits float_half(float_bits f) {
	/* Decompose bit representation into parts */
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if (exp == 0xFF) return f;
	if (exp == 0) return (sign << 31) | (frac >> 1);
	if (exp == 1) return (sign << 31) | (frac >> 1) | (1 << 22);
	return (sign << 31) | ((exp - 1) << 23) | frac;
}
```

## 2.96

```c
/*
 * Compute (int) f.
 * If conversion causes overflow of f is NaN, return 0x80000000
 */
int float_f2i(float_bits f) {
	/* Decompose bit representation into parts */
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	unsigned bias = (1 << 7) - 1;
	unsigned absval = 0x80000000;
	if (exp > bias + 30) {
		/* Too big.  Return 0x80000000 */
		return absval;
	}
	else if (exp >= bias + 23) {
		absval = ((1 << 23) | frac) << (exp - bias - 23);
	}
	else if (exp >= bias) {
		absval = ((1 << 23) | frac) >> (bias + 23 - exp);
	}
	else {
		/* f < 1 */
		return 0;
	}
	sign && (absval = (~absval) + 1);
	return absval;
}
```

## 2.97

```c
/* Compute (float) i */
float_bits float_i2f(int i) {
	unsigned sign = (i >> 31) & 1;
	unsigned bias = (1 << 7) - 1;

	unsigned absval = i;
	sign && (absval = (~absval) + 1);

	unsigned power = 0;
	unsigned tmpval = absval;
	(tmpval >> 16) && (power += 16) && (tmpval >>= 16);
	(tmpval >> 8) && (power += 8) && (tmpval >>= 8);
	(tmpval >> 4) && (power += 4) && (tmpval >>= 4);
	(tmpval >> 2) && (power += 2) && (tmpval >>= 2);
	(tmpval >> 1) && (power += 1) && (tmpval >>= 1);

	unsigned E = power + bias;
	unsigned frac = absval - (1 << power);
	if (power >= 23) {
		frac >>= power - 23;
	}
	else frac >>= 22 - power;
	
	return (sign << 31) | (E << 23) | frac;
}
```

# Chapter3

## 3.58

```c
long decode2(long x, long y, long z) {
	y = y - z;
	x = x * y;
	return (y & 1) ? ~x : x;
}
```

## 3.59

```c
typedef __int128 int128_t;
void store_prod(int128_t *dest, int64_t x, int64_t y) {
	*dest = x * (int128_t) y;
}

	X = Xhigh * 2^64 + Xlow
	Y = Yhigh * 2^64 + Ylow
	X * Y = (Xhigh * Yhigh * 2^128 + 2^64 * (Xhigh * Ylow + Yhigh * Xlow) + Xlow * Ylow) mod 2^128
	X * Y = 2^64 * (Xhigh * Ylow + Yhigh * Xlow) + Xlow * Ylow

store_prod:
	movq  %rdx, %rax		;%rax = Ylow
	cqto					;sign extend. %rdx = Yhigh, %rax = Ylow
	movq  %rsi, %rcx		;%rcx = Xlow
	sarq  %63 , %rcx		;%rcx = Xhigh 
	imulq %rax, %rcx		;%rcx = Xhigh * Ylow
	imulq %rsi, %rdx		;%rdx = Yhigh * Xlow
	addq  %rdx, %rcx		;%rcx = Xhigh * Ylow + Yhigh * Xlow
	mulq  %rsi				;[%rdx : %rax] = x * y
	addq  %rcx, %rdx		;%rdx += Xhigh * Ylow + Yhigh * Xlow
	movq  %rax, (%rdi)		
	movq  %rdx, 8(%rdi)
	ret
```

## 3.60

```c
long loop(long x, int n) {
	long result = 0;
	long mask;
	for (mask = 1; mask != 0; mask = mask << n) {
		result |= x & mask;
	}
	return result;
}
```

## 3.61

```c
long cread_alt(long* xp) {
	if (xp == NULL)
		goto FALSE;
	return *xp;
FALSE:
	return 0;
}
```

## 3.62

```c
/* Enumerated type creates set of constants numbered 0 and upward */
typedef enum { MODE_A, MODE_B, MODE_C, MODE_D, MODE_E } mode_t;
long switch3(long* p1, long* p2, mode_t action) {
	long result = 0;
	switch (action) {
	case MODE_A:
		result = *p2;
		*p2 = *p1;
		break;
	case MODE_B:
		result = *p1 + *p2;
		*p1 = result;
		break;
	case MODE_C:
		*p1 = 59;
		result = *p2;
		break;
	case MODE_D:
		*p1 = *p2;
		result = 27;
		break;
	case MODE_E:
		result = 27;
		break;
	default:
		result = 12;
	}
	return result;
}
```

## 3.63

```c
long switch_prob(long x, long n) {
	long result = x;
	n -= 0x3c;
	switch (n) {
	case 0:
	case 2:
		result *= 8;
		break;
	case 3:
		result >>= 3;
		break;
	case 4:
		result *= 15;
	case 5:
		x = result * result;
	default:
		result = x + 0x4b;
	}
	return result;
}
```

## 3.64

```c
#define R 7
#define S 5
#define T 13
long A[R][S][T];
long store_ele(long i, long j, long k, long* dest) {
	*dest = A[i][j][k];
	return sizeof(A);
}
/*
 *	A. 
 *  long A[R][S][T];
 *	&A[i][j][k] = X + L(i * S * T + j * T + k)
 *  
 *	B. R = 7, S = 5, T = 13
 */
```

## 3.65

```c
#define M 15
void transpose(long A[M][M]) {
	long i, j;
	for (i = 0; i < M; i++ )
		for (j = 0; j < i; j++) {
			long t = A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = t;
		}
}
/*
 *	A.%rdx
 *	B.%rax
 *	C.M = 15
 */
```

## 3.66

```c
#define NR(n) (3 * (n))
#define NC(n) (4 * (n) + 1)
long sum_col(long n, long A[NR(n)][NC(n)], long j) {
	long i;
	long result = 0;
	for (i = 0; i < NR(n); i++)
		result += A[i][j];
	return result;
}
```

## 3.67

```c
	A. (%rsp) = x
	  8(%rsp) = y
	 16(%rsp) = &z
	 24(%rsp) = z
	B.  %rsp + 64
	C.  %rsp + bias
	D.  %rdi + bias
	E.  %rsp + 64 -> y
		%rsp + 72 -> x
		%rsp + 80 -> z
	F. 结构体传递参数或作为返回值均为其首地址值
```

## 3.68

```c
setVal:
	movslq	8(%rsi), %rax	;5 <= B <= 8
	addq	32(%rsi), %rax	;7 <= A <= 10

	movq	%rax, 184(%rdi)	;180 <= 4 * A * B <= 184
	ret

	A = 9, B = 5
```

## 3.69

```c
	A. CNT = 7
	B. 
	typedef struct {
		long idx;
		long x[4];
	} a_struct;
```

## 3.70

```c
	A.e1.p		0
	  e1.y		8
	  e2.x		0
	  e2.next	8
	B.16
	C.
	void proc(union ele* up) {
		up->e2.x = *(up->e2.next->e1.p) - up->e2.next->e1.y;
	}
```

## 3.71

```c
#define BUF_SIZE 4
void good_echo(void) {
	char buf[BUF_SIZE];
	while (1) {
		char* p = fgets(buf, BUF_SIZE, stdin);
		if (ferror(stdin) || p == NULL)
			break;
		fputs(buf, stdout);
	}
}
```

## 3.72

```c
	A. s2 = s1 - (8 * n + 16) ;n为偶数
	   s2 = s1 - (8 * n + 24) ;n为奇数
	B.  p = (s2 + 15) & 0xFFFFFFF0
	C. 使e1最小: n为奇数, s1 mod 16 = 0
	   使e1最大: n为偶数, s1 mod 16 = 1
	D. s2 保留s1的偏移量为最接近的16的倍数		p 16对齐
```

## 3.73

```c
typedef enum {NEG, ZERO, POS, OTHER} range_t;

find_range:
	movl		$0, %eax				;set %rax = 0
	vxorps		%xmm1, %xmm1, %xmm1		;set %xmm1 = 0
	vucomiss	%xmm1, %xmm0			;Compare x:0
	jp			.L5						;If NaN
	jz			.L6						;If x = 0
	jc			.L7						;If x < 0
	addl		$2, %eax				;x > 0
	rep; ret
.L5:
	addl		$2, %eax
.L6:
	addl		$1, $eax
.L7:
	rep; ret
```

## 3.74

```c
typedef enum {NEG, ZERO, POS, OTHER} range_t;

find_range:
	movl		$2, %eax				;Assume x is POS	
	vxorps		%xmm1, %xmm1, %xmm1		;set %xmm1 = 0
	vucomiss	%xmm1, %xmm0			;Compare x:0
	movq		$0, %rdx
	cmovs		%rdx, %rax				;If CF = 1, %rax = 0, x may be NEG or NaN
	movq		$1, %rdx
	cmove		%rdx, %rax				;If ZF = 1, %rax = 1, x may be ZERO or NaN
	movq		%3, %rdx
	cmovp		%rdx, %rax				;If PF = 1, %rax = 3, x must be NaN
	rep; ret
```

## 3.75

```c
	A.每个复数类型参数使用两个xmm寄存器分别存储实部和虚部数值, 下标小的存实部
	B.若只单独返回实部或单独返回虚部, 将待返回值放于%xmm0寄存器中
	  若需返回整个复数,将实部放于%xmm0寄存器中,虚部放于%xmm1寄存器中
```

# Chapter4

## 4.45

```assembly
	A. 	不正确
		正确的pushq应该是先存REG再减%rsp值
	   	若按本题所述，pushq %rsp存储的是%rsp - 8的值，而不是原值
	B. 	movq %rsp, %rbp
	   	subq $8, %rbp
	   	movq REG, (%rbp)
	   	subq $8, %rsp
```

## 4.46

```assembly
	A. 	不正确
		若按本题所述，popq %rsp执行后%rsp中值为%rsp + 8，而不是原值
	B.	movq %rsp, %rbp
		addq $8, %rsp
		movq (%rbp), REG
```

## 4.47

```c
A.
/* Bubble sort: Pointer version */
void bubble_p(long* data, long count) {
    long i, last;
    for (last = count - 1; last > 0; last--) {
        for (i = 0; i < last; i++) {
            if (*(data + i + 1) < *(data + i)) {
                /* Swap adjacent elements */
                long t = *(data + i + 1);
                *(data + i + 1) = *(data + i);
                *(data + i) = t;
            }
        }
    }
}
```

```assembly
B.
# void bubble_p(long* data, long count)
# data in %rdi, count in %rsi
bubble_p:
	irmovq $1, %r8
	rrmovq %rsi, %r9		;%r9: last
loop1:
	subq %r8, %r9
	andq %r9, %r9
	je done
	irmovq $0, %rax			;%rax: i 
loop2:
	rrmovq %rax, %r11
	subq %r9, %r11			;%r11 = i - last
	je next
	rrmovq %rax, %r11		;%r11 = i
	addq %r8, %r11			;%r11 = i + 1
	addq %r11, %r11
	addq %r11, %r11
	addq %r11, %r11			;%r11 = 8 * (i + 1)
	addq %rdi, %r11			;%r11 = &*(data +i + 1)
	mrmovq (%r11), %rbx		;%rbx = *(data + i + 1)
	
	rrmovq %rax, %r12		;%r12 = i
	addq %r12, %r12
	addq %r12, %r12
	addq %r12, %r12			;%r12 = 8 * i
	addq %rdi, %r12			;%r12 = &*(data +i)
	mrmovq (%r12), %rcx		;%rcx = *(data + i)
	
	rrmovq %rbx, %r13
	subq %rcx, %r13			;%r13 = *(data + i + 1) - *(data + i)
	jge	no_need
	rmmovq %rbx, (%r12)
	rmmovq %rcx, (%r11)
no_need:
	addq %r8, %rax
	jmp loop2
next:
	jmp loop1
done:
	ret
```

## 4.48

```assembly
	rrmovq %rax, %r11		;%r11 = i
	addq %r8, %r11			;%r11 = i + 1
	addq %r11, %r11
	addq %r11, %r11
	addq %r11, %r11			;%r11 = 8 * (i + 1)
	addq %rdi, %r11			;%r11 = &*(data +i + 1)
	mrmovq (%r11), %rbx		;%rbx = *(data + i + 1)
	
	rrmovq %rax, %r12		;%r12 = i
	addq %r12, %r12
	addq %r12, %r12
	addq %r12, %r12			;%r12 = 8 * i
	addq %rdi, %r12			;%r12 = &*(data +i)
	mrmovq (%r12), %rcx		;%rcx = *(data + i)
	
	rrmovq %rbx, %r13
	subq %rcx, %r13			;%r13 = *(data + i + 1) - *(data + i)
	cmovl %rbx, %r13
	cmovl %rcx, %rbx
	cmovl %r13, %rcx
	mrmovq (%r11), %rbx
	mrmovq (%r12), %rcx
```

## 4.49

```assembly
	rrmovq %rax, %r11		;%r11 = i
	addq %r8, %r11			;%r11 = i + 1
	addq %r11, %r11
	addq %r11, %r11
	addq %r11, %r11			;%r11 = 8 * (i + 1)
	addq %rdi, %r11			;%r11 = &*(data +i + 1)
	mrmovq (%r11), %rbx		;%rbx = *(data + i + 1)
	
	rrmovq %rax, %r12		;%r12 = i
	addq %r12, %r12
	addq %r12, %r12
	addq %r12, %r12			;%r12 = 8 * i
	addq %rdi, %r12			;%r12 = &*(data +i)
	mrmovq (%r12), %rcx		;%rcx = *(data + i)
	
	rrmovq %rbx, %r13
	subq %rcx, %r13			;%r13 = *(data + i + 1) - *(data + i)
	rmmovq %rcx, (%r11)		;now, *(data + i + 1) = *(data + i)
	rrmovq %r11, %r13		;%r13 = &*(data + i + 1)
	cmovl %r12, %r13		;if (initial data[i + 1] < initial data[i]), %r13 = &*(data + i)
	rmmovq %rbx, (%r13)		;(%r13) = initial data[i + 1]
```

## 4.50

```assembly
;long switchv(long idx)
;idx in %rdi
switchv:
	irmovq $5, %r8
	subq %r8, %rdi
	jg default
	addq %rdi, %rdi
	addq %rdi, %rdi
	addq %rdi, %rdi
	irmovq table, %r8
	addq %r8, %rdi
	pushq %rdi
	ret
case_0:
	irmovq $0xaaa, %rax
	jmp done
case_2_5:
	irmovq $0xbbb, %rax
	jmp done
case_3:
	irmovq $0xccc, %rax
	jmp done
default:
	irmovq $0xddd, %rax
done:
	ret
	
	.align 8
table:
	.quad	case_0
	.quad	default
	.quad	case_2_5
	.quad	case_3
	.quad	default
	.quad	case_2_5
```

## 4.51

| 阶段   | iaddq V, rB                                                  |
| ------ | ------------------------------------------------------------ |
| 取指   | icode:ifun <-- M1[PC]<br />rA:rB <-- M1[PC + 1]<br />valC <-- M8[PC + 2]<br />valP <-- PC + 10 |
| 译码   | valB <-- R[rB]                                               |
| 执行   | valE <-- valB + valC<br />Set CC                             |
| 访存   |                                                              |
| 写回   | R[rB] <-- valE                                               |
| 更新PC | PC <-- valP                                                  |

## 4.53

没有pipe-stall.hcl文件，经查证本题所用文件应为pipe-nobypass.hcl

## 4.57

```
A. 加载/转发使用冒险	 M_icode in { IMRMOVQ, IPOPQ } && E_icode in { IPUSHQ } && M_dstM == E_valA
```

## 4.58

放弃

## 4.59

```
4.49的版本好
首先，4.47猜用跳转指令实现功能，大量的分支预测错误大幅降低效率
而4.49相比于4.48只使用一次条件传送，效率更高
```

# Chapter5

## 5.14

```c
/* 6 x 1 loop unrolling */
void inner5(vec_ptr u, vec_ptr v, data_t* dest) {
    long i;
    long length = vec_length(u);
    data_t* updata = get_vec_start(u);
    data_t* vdata = get_vec_start(v);
    data_t sum = (data_t) 0;
    
    if (length >= 6) {
        /* Combine 6 elements at a time */
        for (i = 0; i < length; i += 6) {
        sum += udata[i] * vdata[i]; 
        sum += udata[i + 1] * vdata[i + 1]; 
        sum += udata[i + 2] * vdata[i + 2]; 
        sum += udata[i + 3] * vdata[i + 3]; 
        sum += udata[i + 4] * vdata[i + 4]; 
        sum += udata[i + 5] * vdata[i + 5]; 
    	}
    }
    
    
    /* Finish any remaining elements */
    for (; i < length; i++)
        sum += updata[i] * vdata[i];
    *dest = sum;
}
```

## 5.15

```c
/* 6 x 6 loop unrolling */
void inner6(vec_ptr u, vec_ptr v, data_t* dest) {
    long i;
    long length = vec_length(u);
    data_t* updata = get_vec_start(u);
    data_t* vdata = get_vec_start(v);
    data_t sum1 = (data_t) 0;
    data_t sum2 = (data_t) 0;
    data_t sum3 = (data_t) 0;
    data_t sum4 = (data_t) 0;
    data_t sum5 = (data_t) 0;
    data_t sum6 = (data_t) 0;
    
    if (length >= 6) {
        /* Combine 6 elements at a time */
        for (i = 0; i < length; i += 6) {
        sum1 += udata[i] * vdata[i]; 
        sum2 += udata[i + 1] * vdata[i + 1]; 
        sum3 += udata[i + 2] * vdata[i + 2]; 
        sum4 += udata[i + 3] * vdata[i + 3]; 
        sum5 += udata[i + 4] * vdata[i + 4]; 
        sum6 += udata[i + 5] * vdata[i + 5]; 
    	}
    }
    
    
    /* Finish any remaining elements */
    for (; i < length; i++)
        sum1 += updata[i] * vdata[i];
    *dest = sum1 + sum2 + sum3 +sum4 +sum5 +sum6;
}
```

## 5.16

```c
/* 6 x 1a loop unrolling */
void inner5(vec_ptr u, vec_ptr v, data_t* dest) {
    long i;
    long length = vec_length(u);
    data_t* updata = get_vec_start(u);
    data_t* vdata = get_vec_start(v);
    data_t sum = (data_t) 0;
    
    if (length >= 6) {
        /* Combine 6 elements at a time */
        for (i = 0; i < length; i += 6) {
        sum += udata[i] * vdata[i] + udata[i + 1] * vdata[i + 1] +
			   udata[i + 2] * vdata[i + 2] + udata[i + 3] * vdata[i + 3] +
               udata[i + 4] * vdata[i + 4] + udata[i + 5] * vdata[i + 5];
    	}
    }
    
    
    /* Finish any remaining elements */
    for (; i < length; i++)
        sum += updata[i] * vdata[i];
    *dest = sum;
}
```

## 5.17

```c
void* optimized_memset(void* s, int c, size_t n) {
    size_t cnt = 0;
    unsigned long i, j, longc, K = sizeof(unsigned long);
    unsigned char* schar = s;
    unsigned char charc = (unsigned char)c;
    for (i = 8, j = K << 3, longc = charc; i < j; i *= 2) {
        longc = (longc << i) | longc;
    }
    while ((unsigned long)s % K != 0 && cnt < n) {
        *schar++ = charc;
        cnt++;
    }
    unsigned long* p = (unsigned long*)s;
    if (n >= cnt + K)
    {
        for (; cnt < n; cnt += K) {
            *p++ = longc;
        }
    }
    schar = (unsigned char*)p;
    while (cnt < n) {
        *schar++ = charc;
        cnt++;
    }
    return s;
}
```

## 5.18

```c
double polyh(double a[], double x, long degree) {
    long i;
    double acc1 = a[0], acc2 = 0, acc3 = 0, acc4 = 0, result;
    double xpwr = x, xpwr_1, xpwr_2, xpwr_3;
    double xp1 = x;
    double xp2 = x * x;
    double xp3 = x * x * x;
    double xp4 = x * x * x * x;

    for (i = 4; i <= degree; i += 4) {
        xpwr_1 = xpwr * xp1;
        xpwr_2 = xpwr * xp2;
        xpwr_3 = xpwr * xp3;
        acc1 += a[i - 3] * xpwr;       
        acc2 += a[i - 2] * xpwr_1;
        acc3 += a[i - 1] * xpwr_2;
        acc4 += a[i] * xpwr_3;
        xpwr *= xp4;
    }
    i -= 3;
    while (i <= degree) {
        acc1 += a[i++] * xpwr;
        xpwr *= x;
    }
    result = acc1 + acc2 + acc3 + acc4;
    return result;
}
```

## 5.19

```c
void psum1(float a[], float p[], long n) {
    long i;
    float acc0 = a[0], acc1 = a[0];
    p[0] = a[0];
    for (i = 2; i < n; i += 2) {
        acc0 += a[i - 1];
        acc1 += a[i - 1] + a[i];
        p[i- 1] = acc0;
        p[i] = acc1;
        acc0 += a[i];
    }
    i--;
    while (i < n) {
        p[i] = p[i - 1] + a[i++];
    }
}
```

# Chapter6

## 6.22

```
圆洞周长：2 * pi * x * r
磁道数正比于: 1 - x
容量： 2 * pi * x * r * (1 - x) = 2 * pi * x * r - 2 * pi * (x^2) * r
当x = 0.5时磁盘容量最大
```

## 6.23

$T_{avg seek} = 4ms$

$T_{avg rotation} = \frac{1}{2} * \frac{60s}{15000} * \frac{1000ms}{1s} = 2ms$

$T_{avg transfer} = \frac{1}{15000} * \frac{1}{800} * \frac{60s}{1min} * \frac{1000ms}{1s} = 0.005ms$

$T_{access} = T_{avg seek} + T_{avg rotation} + T_{avg transfer} = 6.005ms$

## 6.24

$T_{avg seek} = 4ms$

$T_{avg rotation} = \frac{1}{2} * \frac{60s}{15000} * \frac{1000ms}{1s} = 2ms$

2MB大小的文件，一个逻辑块存放512字节，需要4096个逻辑块

最好情况：$T = T_{avg seek} + T_{avg rotation} + \frac{4096}{1000} * T_{max ratation} = 22.384ms$

最坏情况：$T =  (T_{avg seek} + T_{avg rotation}) * 4096 * \frac{1s}{1000ms} = 24.576s$

## 6.25

| 高速缓存 |  m   |  C   |  B   |  E   |  S   |  t   |  s   |  b   |
| :------: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|    1.    |  32  | 1024 |  4   |  4   |  64  |  24  |  6   |  2   |
|    2.    |  32  | 1024 |  4   | 256  |  2   |  29  |  1   |  2   |
|    3.    |  32  | 1024 |  8   |  1   | 128  |  22  |  7   |  3   |
|    4.    |  32  | 1024 |  8   | 128  |  1   |  29  |  0   |  3   |
|    5.    |  32  | 1024 |  32  |  1   |  32  |  22  |  5   |  5   |
|    6.    |  32  | 1024 |  32  |  4   |  8   |  24  |  3   |  5   |

## 6.26

| 高速缓存 |  m   |  C   |  B   |  E   |  S   |  t   |  s   |  b   |
| :------: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|    1.    |  32  | 2048 |  8   |  1   | 256  |  21  |  8   |  3   |
|    2.    |  32  | 2048 |  4   |  8   | 128  |  23  |  7   |  2   |
|    3.    |  32  | 1024 |  2   |  8   |  64  |  25  |  6   |  1   |
|    4.    |  32  | 1024 |  32  |  2   |  16  |  23  |  4   |  5   |

## 6.27

```
A. 0x8a4 ~ 0x8a7, 0xe04 ~ 0xe07
B. 0x1238 ~ 0x123b
```

## 6.28

```
A. NONE
B. 0x18f0 ~ 0x18f3
C. 0xb0 ~ 0xb3
D. 0x1bdc ~ 0x1bdf
```

## 6.29

|  CT  |  CT  |  CT  |  CT  |  CT  |  CT  |  CT  |  CT  |  CI  |  CI  |  CO  |  CO  |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |

| 操作 | 地址  | 命中？ | 读出的值 |
| :--: | :---: | :----: | :------: |
|  读  | 0x834 |  miss  |   0xFE   |
|  写  | 0x836 |  hit   |   ----   |
|  读  | 0xFFD |  hit   |   0xC0   |

## 6.30

$C = B * E * S = 128$

|  CT  |  CT  |  CT  |  CT  |  CT  |  CT  |  CT  |  CT  |  CI  |  CI  |  CI  |  CO  |  CO  |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |

## 6.31

|  0   |  0   |  1   |  1   |  1   |  0   |  0   |  0   |  1   |  1   |  0   |  1   |  0   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |

|        参数        |  值  |
| :----------------: | :--: |
|         CO         | 0x2  |
|         CI         | 0x6  |
|         CT         | 0x38 |
|       命中？       | hit  |
| 返回的高速缓存字节 | 0xEB |

## 6.32

|  1   |  0   |  1   |  1   |  0   |  1   |  1   |  1   |  0   |  1   |  0   |  0   |  0   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |



|        参数        |  值  |
| :----------------: | :--: |
|         CO         | 0x0  |
|         CI         | 0x2  |
|         CT         | 0xB7 |
|       命中？       | miss |
| 返回的高速缓存字节 | ---- |

## 6.33

```
 0x1788 ~ 0x178b, 0x16c8 ~ 0x16cb
```

## 6.34

dst数组

|      | col0 | col1 | col2 | col3 |
| :--: | :--: | :--: | :--: | :--: |
| row0 |  m   |  m   |  m   |  m   |
| row1 |  m   |  m   |  m   |  m   |
| row2 |  m   |  m   |  m   |  m   |
| row3 |  m   |  m   |  m   |  m   |

src数组

|      | col0 | col1 | col2 | col3 |
| :--: | :--: | :--: | :--: | :--: |
| row0 |  m   |  m   |  h   |  m   |
| row1 |  m   |  h   |  m   |  h   |
| row2 |  m   |  m   |  h   |  m   |
| row3 |  m   |  m   |  h   |  m   |

## 6.35

dst数组

|      | col0 | col1 | col2 | col3 |
| :--: | :--: | :--: | :--: | :--: |
| row0 |  m   |  h   |  h   |  h   |
| row1 |  m   |  h   |  h   |  h   |
| row2 |  m   |  h   |  h   |  h   |
| row3 |  m   |  h   |  h   |  h   |

src数组

|      | col0 | col1 | col2 | col3 |
| :--: | :--: | :--: | :--: | :--: |
| row0 |  m   |  h   |  h   |  h   |
| row1 |  m   |  h   |  h   |  h   |
| row2 |  m   |  h   |  h   |  h   |
| row3 |  m   |  h   |  h   |  h   |

## 6.36

```
A. 100%
B. 25%
C. 25%
D. 不能，所有的未命中都是冷缓存导致的
E. 能，如果块更大，能减少部分未命中次数
```

## 6.37

| 函数 | N=64 | N=60 |
| :--: | :--: | :--: |
| sumA | 25%  | 25%  |
| sumB | 100% | 25%  |
| sumC | 50%  | 25%  |

## 6.38

```
A. 1024
B. 128
C. 12.5%
```

## 6.39

```
A. 1024
B. 256
C. 25%
```

## 6.40

```
A. 1024
B. 256
C. 25%
```

## 6.41

25%

## 6.42

25%

## 6.43

100%

## 6.44

{% asset_img mountain.png %}

## 6.45

```c
void transpose(int* dst, int* src, int dim) {
    int i, j, acc0, acc1, acc2, acc3, m, n;
    for (i = 0; i < dim; i++) {
        m = i * dim;
        for (j = 3; j < dim; j += 4) {
            n = j * dim;
            acc0 = src[m + j - 3];
            acc1 = src[m + j - 2];
            acc2 = src[m + j - 1];
            acc3 = src[m + j];
            dst[n - dim - dim - dim + i - 3] = acc0;
            dst[n - dim - dim + i - 2] = acc1;
            dst[n - dim + i - 1] = acc2;
            dst[n + i] = acc3;
        }
        j -= 3;
        for (; j < dim; j++)
            dst[j * dim + i] = src[m + j];
    }
}
```

## 6.46

```c
void col_convert(int* G, int dim) {
    int i, j, k, acc0, acc1, acc2, acc3;
    
    for (i = 1; i < dim; i++) {
        k = i * dim;
        for (j = 3; j < i; j += 4) {
            acc0 = G[k + j - 3];
            acc1 = G[k + j - 2];
            acc2 = G[k + j - 1];
            acc3 = G[k + j];
            G[(j - 3) * dim + i] |= acc0;
            G[(j - 2) * dim + i] |= acc1;
            G[(j - 1) * dim + i] |= acc2;
            G[j * dim + i] |= acc3;
        }
        j -= 3;
        for (; j < i; j++)
            G[j * dim + i] |= G[k + j];
    }
    
    
    for (i = 0; i < dim; i++) {
        k = i * dim;
        for (j = i + 4; j < dim; j += 4) {
			G[k + j - 3] = G[(j - 3) * dim + i];
            G[k + j - 2] = G[(j - 2) * dim + i];
            G[k + j - 1] = G[(j - 1) * dim + i];
            G[k + j - 0] = G[(j - 0) * dim + i];
        }
        j -= 3;
        for (; j < dim; j++)
            G[k + j] = G[j * dim + i];
    }
}
```

# Chapter7

## 7.6

| 符号  | .symtabl条目 | 符号类型 | 在哪个模块种定义 |  节   |
| :---: | :----------: | :------: | :--------------: | :---: |
|  buf  |      是      |   外部   |       m.o        | .data |
| bufp0 |      是      |   全局   |      swap.o      | .data |
| bufp1 |      是      |   局部   |      swap.o      | .bss  |
| incr  |      是      |   局部   |      swap.o      | .text |
| count |      是      |   局部   |      swap.o      | .bss  |
| swap  |      是      |   全局   |      swap.o      | .text |
| temp  |      否      |   ----   |       ----       | ----  |

## 7.7

```c
/* foo5.c */
#include<stdio.h>
void f(void);

int y = 15212;
int x = 15213;

int main()
{
    f();
    printf("x = 0x%x y = 0x%x \n", x, y);
    return 0;
}

/* bar5.c */
double x;

void f()
{
    x = 996948845.0;
}
```

## 7.8

```
A. a.REF(main.1)->DEF(main.1)
   b.REF(main.2)->DEF(main.1)

B. a.REF(x.1)->DEF(未知)
   b.REF(x.2)->DEF(未知)
   
C. a.REF(x.1)->DEF(错误)
   b.REF(x.2)->DEF(错误)
```

## 7.9

两个模块都定义有main,foo模块中的main是一个函数，为强符号；bar中的main是未定义的全局变量，为弱符号，链接器将选择foo模块中的main

## 7.10

```
A.	gcc p.o libx.a
B.	gcc p.o libx.a liby.a libx.a
C.	gcc p.o libx.a liby.a libx.a libz.a
```

## 7.11

该段中剩下的8个字节对应于运行时将被初始化为0的.bss数据

## 7.12

```
 A. ADDR(s) = ADDR(.text) = 0x4004e0
    ADDR(r.symbol) = ADDR(swap) = 0x4004f8
        refaddr = ADDR(s) + r.offset
                = 0x4004e0 + 0xa
                = 0x4004ea
        *refptr = (unsigned) (ADDR(r.symbol) + r.addend - refaddr)
                = (unsigned) (0x4004f8 - 0x4 - 0x0x4004ea)
                = (unsigned) 0xa
 
 B. ADDR(s) = ADDR(.text) = 0x4004d0
    ADDR(r.symbol) = ADDR(swap) = 0x400500
        refaddr = ADDR(s) + r.offset
                = 0x4004d0 + 0xa
                = 0x4004da
        *refptr = (unsigned) (ADDR(r.symbol) + r.addend - refaddr)
                = (unsigned) (0x400500 - 0x4 - 0x0x4004da)
                = (unsigned) 0x22 
```

# Chapter8

## 8.9

| 进程对 | 并发地？ |
| :----: | :------: |
|   AB   |    否    |
|   AC   |    是    |
|   AD   |    是    |
|   BC   |    是    |
|   BD   |    是    |
|   CD   |    是    |

## 8.10

```
A. fork
B. execve, longjmp
C. setjmp
```

## 8.11

4个

## 8.12

8个

## 8.13

```
x=2
x=4
x=3
```

## 8.14

3个

## 8.15

5个

## 8.16

2

## 8.17

```
case 1:
Hello
1
Bye
0
2
Bye

case 2:
Hello
1
0
Bye
2
Bye

case 3:
Hello
0
1
Bye
2
Bye
```

## 8.18

可能的输出：A,C,E

## 8.19

2的n次方

## 8.20

我所使用的是shell程序为bash而非csh，因此

```
linux> setenv COLUMNS 40
linux> unsetenv COLUMNS
```

应改为

```
linux> export COLUMNS=40
linux> unset COLUMNS
```

```c
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char* argvp[], char* envp[]) {
    char* p = getenv("COLUMNS");
    if (p == NULL)
        setenv("COLUMNS", "80", 1);
    execve("/bin/ls", argv, envp);
}
```

实际上我写这个并没能实现按COLUMNS的值不同而显示不同的功能，但暂时不知道怎么改，先就这样

## 8.21

```
abc
bac
```

## 8.22

```c
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int mysystem(char* command) {
        pid_t pid;
        int status;
        if (pid = fork() == 0) {
                execl("/bin/sh", "sh", "-c", command, (char*)0);
        }
        while(waitpid(pid, &status, WUNTRACED) == pid) {
                if (WIFEXITED(status)) {
                        return WEXITSTATUS(status);
                }
                else if (WIFSIGNALED(status)) {
                        fprintf(stderr, "command terminated by signal number %d.\n", WTERMSIG(status));
                        return WTERMSIG(status);
                }
        }       
}
```

## 8.23

未经处理的信号是不排队的。在子进程发送第一个SIGUSR2信号号给父进程时，count++，在sleep(1)时，后续四个信号均已发出，而父进程的pending位向量只会保留一个SIGUSR2信号，因此即使发送了5个信号，count值也为2

## 8.24

```c
#include "csapp.h"
#define N 2
int main()
{
    int status, i;
    pid_t pid;
    
    /* Parent creates N children */
    for (i = 0; i < N; i++)
        if ((pid = Fork()) == 0) /* Child */
            exit(100 + i);
    
    /* Parent reaps N children in no particular order */
    while ((pid = waitpid(-1, &status, 0) > 0)) {
        if (WIFEXITED(status))
            printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
        else if (WIFSIGNALED(status)) {
            char* sigErr = strsignal(WTERMSIG(status))
            psignal(WTERMSIG(status), sigErr);
        }
    }
}
```

## 8.25

```c
#include"csapp.h"

void sigalrm_handler(int sig) {
        if (alarm(0) == 0)
                _exit(0);
}

char* tfgets(char* str, int n, FILE* stream) {
        signal(SIGALRM, sigalrm_handler);
        alarm(5);
        fgets(str, n, stream);
        return str;
}
```

## 8.26

不做，完成Shell Lab代替之

## Chapter9

## 9.11

虚拟地址格式

|  13  |  12  |  11  |  10  |  9   |  8   |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|  0   |  0   |  0   |  0   |  1   |  0   |  0   |  1   |  1   |  1   |  1   |  1   |  0   |  0   |

地址翻译

|   参数    |  值  |
| :-------: | :--: |
|    VPN    | 0x9  |
|  TLB索引  | 0x1  |
|  TLB标记  | 0x2  |
| TLB命中？ |  是  |
|  缺页？   |  是  |
|    PPN    | ---- |

## 9.12

虚拟地址格式

|  13  |  12  |  11  |  10  |  9   |  8   |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|  0   |  0   |  0   |  0   |  1   |  1   |  1   |  0   |  1   |  0   |  1   |  0   |  0   |  1   |

地址翻译

|   参数   |  值  |
| :------: | :--: |
|   VPN    | 0x0E |
| TLB索引  | 0x2  |
| TLB标记  | 0x3  |
| TLB命中? |  是  |
|  缺页?   |  是  |
|   PPN    | ---- |

## 9.13

虚拟地址格式

|  13  |  12  |  11  |  10  |  9   |  8   |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|  0   |  0   |  0   |  0   |  0   |  0   |  0   |  1   |  0   |  0   |  0   |  0   |  0   |  0   |

地址翻译

|   参数   |  值  |
| :------: | :--: |
|   VPN    | 0x1  |
| TLB索引  | 0x1  |
| TLB标记  | 0x0  |
| TLB命中? |  否  |
|  缺页?   |  是  |
|   PPN    | ---- |

## 9.14

```c
/* problem914.c */
#include "csapp.h"
  
int main(int argc, char* argv[]) {
        struct stat stat;
        int fd;
        char* bufp;

        /* Copy the input argument */
        fd = Open(argv[1], O_RDONLY, 0);
        fstat(fd, &stat);
        bufp = Mmap(NULL, stat.st_size, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);
        bufp[0] = 'J';
        write(1, bufp, stat.st_size);

        return 0;
}
```

```
fez@papyruszzz:~/Sketch$ cat hello.txt 
Hello, world!
fez@papyruszzz:~/Sketch$ gcc -o prog mmapcopy.c csapp.h csapp.c -lpthread
fez@papyruszzz:~/Sketch$ ./prog hello.txt 
Jello, world!
```

## 9.15

|    请求    | 块大小（十进制字节） | 块头部（十六进制） |
| :--------: | :------------------: | :----------------: |
| malloc(3)  |          8           |        0x9         |
| malloc(11) |          16          |        0x11        |
| malloc(20) |          24          |        0x19        |
| malloc(21) |          32          |        0x21        |

## 9.16

| 对齐要求 |      已分配块      |   空闲块   | 最小块大小（字节） |
| :------: | :----------------: | :--------: | :----------------: |
|   单字   |     头部和脚部     | 头部和脚部 |         16         |
|   单字   | 头部，但是没有脚部 | 头部和脚部 |         16         |
|   双字   |     头部和脚部     | 头部和脚部 |         16         |
|   双字   | 头部，但是没有脚部 | 头部和脚部 |         16         |

## 9.17

```c
/* 
 * Simple, 32-bit and 64-bit clean allocator based on implicit free
 * lists, first-fit placement, and boundary tag coalescing, as described
 * in the CS:APP3e text. Blocks must be aligned to doubleword (8 byte) 
 * boundaries. Minimum block size is 16 bytes. 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mm.h"
#include "memlib.h"

/*
 * If NEXT_FIT defined use next fit search, else use first-fit search 
 */
#define NEXT_FITx

/* $begin mallocmacros */
/* Basic constants and macros */
#define WSIZE       4       /* Word and header/footer size (bytes) */ //line:vm:mm:beginconst
#define DSIZE       8       /* Double word size (bytes) */
#define CHUNKSIZE  (1<<12)  /* Extend heap by this amount (bytes) */  //line:vm:mm:endconst 

#define MAX(x, y) ((x) > (y)? (x) : (y))  

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc)  ((size) | (alloc)) //line:vm:mm:pack

/* Read and write a word at address p */
#define GET(p)       (*(unsigned int *)(p))            //line:vm:mm:get
#define PUT(p, val)  (*(unsigned int *)(p) = (val))    //line:vm:mm:put

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)                   //line:vm:mm:getsize
#define GET_ALLOC(p) (GET(p) & 0x1)                    //line:vm:mm:getalloc

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)       ((char *)(bp) - WSIZE)                      //line:vm:mm:hdrp
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) //line:vm:mm:ftrp

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE))) //line:vm:mm:nextblkp
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE))) //line:vm:mm:prevblkp
/* $end mallocmacros */

/* Global variables */
static char *heap_listp = 0;  /* Pointer to first block */  

#ifdef NEXT_FIT
static char *rover;           /* Next fit rover */
#endif

/* Function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);
static void printblock(void *bp); 
static void checkheap(int verbose);
static void checkblock(void *bp);

/* 
 * mm_init - Initialize the memory manager 
 */
/* $begin mminit */
int mm_init(void) 
{
    /* Create the initial empty heap */
    if ((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1) //line:vm:mm:begininit
        return -1;
    PUT(heap_listp, 0);                          /* Alignment padding */
    PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1)); /* Prologue header */ 
    PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1)); /* Prologue footer */ 
    PUT(heap_listp + (3*WSIZE), PACK(0, 1));     /* Epilogue header */
    heap_listp += (2*WSIZE);                     //line:vm:mm:endinit  
    /* $end mminit */

#ifdef NEXT_FIT
    rover = heap_listp;
#endif
    /* $begin mminit */

    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE/WSIZE) == NULL) 
        return -1;
    return 0;
}
/* $end mminit */

/* 
 * mm_malloc - Allocate a block with at least size bytes of payload 
 */
/* $begin mmmalloc */
void *mm_malloc(size_t size) 
{
    size_t asize;      /* Adjusted block size */
    size_t extendsize; /* Amount to extend heap if no fit */
    char *bp;      

    /* $end mmmalloc */
    if (heap_listp == 0){
        mm_init();
    }
    /* $begin mmmalloc */
    /* Ignore spurious requests */
    if (size == 0)
        return NULL;

    /* Adjust block size to include overhead and alignment reqs. */
    if (size <= DSIZE)                                          //line:vm:mm:sizeadjust1
        asize = 2*DSIZE;                                        //line:vm:mm:sizeadjust2
    else
        asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE); //line:vm:mm:sizeadjust3

    /* Search the free list for a fit */
    if ((bp = find_fit(asize)) != NULL) {  //line:vm:mm:findfitcall
        place(bp, asize);                  //line:vm:mm:findfitplace
        return bp;
    }

    /* No fit found. Get more memory and place the block */
    extendsize = MAX(asize,CHUNKSIZE);                 //line:vm:mm:growheap1
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)  
        return NULL;                                  //line:vm:mm:growheap2
    place(bp, asize);                                 //line:vm:mm:growheap3
    return bp;
} 
/* $end mmmalloc */

/* 
 * mm_free - Free a block 
 */
/* $begin mmfree */
void mm_free(void *bp)
{
    /* $end mmfree */
    if (bp == 0) 
        return;

    /* $begin mmfree */
    size_t size = GET_SIZE(HDRP(bp));
    /* $end mmfree */
    if (heap_listp == 0){
        mm_init();
    }
    /* $begin mmfree */

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}

/* $end mmfree */
/*
 * coalesce - Boundary tag coalescing. Return ptr to coalesced block
 */
/* $begin mmfree */
static void *coalesce(void *bp) 
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) {            /* Case 1 */
        return bp;
    }

    else if (prev_alloc && !next_alloc) {      /* Case 2 */
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size,0));
    }

    else if (!prev_alloc && next_alloc) {      /* Case 3 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    else {                                     /* Case 4 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
            GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    /* $end mmfree */
#ifdef NEXT_FIT
    /* Make sure the rover isn't pointing into the free block */
    /* that we just coalesced */
    if ((rover > (char *)bp) && (rover < NEXT_BLKP(bp))) 
        rover = bp;
#endif
    /* $begin mmfree */
    return bp;
}
/* $end mmfree */

/*
 * mm_realloc - Naive implementation of realloc
 */
void *mm_realloc(void *ptr, size_t size)
{
    size_t oldsize;
    void *newptr;

    /* If size == 0 then this is just free, and we return NULL. */
    if(size == 0) {
        mm_free(ptr);
        return 0;
    }

    /* If oldptr is NULL, then this is just malloc. */
    if(ptr == NULL) {
        return mm_malloc(size);
    }

    newptr = mm_malloc(size);

    /* If realloc() fails the original block is left untouched  */
    if(!newptr) {
        return 0;
    }

    /* Copy the old data. */
    oldsize = GET_SIZE(HDRP(ptr));
    if(size < oldsize) oldsize = size;
    memcpy(newptr, ptr, oldsize);

    /* Free the old block. */
    mm_free(ptr);

    return newptr;
}

/* 
 * mm_checkheap - Check the heap for correctness
 */
void mm_checkheap(int verbose)  
{ 
    checkheap(verbose);
}

/* 
 * The remaining routines are internal helper routines 
 */

/* 
 * extend_heap - Extend heap with free block and return its block pointer
 */
/* $begin mmextendheap */
static void *extend_heap(size_t words) 
{
    char *bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE; //line:vm:mm:beginextend
    if ((long)(bp = mem_sbrk(size)) == -1)  
        return NULL;                                        //line:vm:mm:endextend

    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));         /* Free block header */   //line:vm:mm:freeblockhdr
    PUT(FTRP(bp), PACK(size, 0));         /* Free block footer */   //line:vm:mm:freeblockftr
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */ //line:vm:mm:newepihdr

    /* Coalesce if the previous block was free */
    return coalesce(bp);                                          //line:vm:mm:returnblock
}
/* $end mmextendheap */

/* 
 * place - Place block of asize bytes at start of free block bp 
 *         and split if remainder would be at least minimum block size
 */
/* $begin mmplace */
/* $begin mmplace-proto */
static void place(void *bp, size_t asize)
/* $end mmplace-proto */
{
    size_t csize = GET_SIZE(HDRP(bp));   

    if ((csize - asize) >= (2*DSIZE)) { 
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0));
        PUT(FTRP(bp), PACK(csize-asize, 0));
    }
    else { 
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
}
/* $end mmplace */

/* 
 * find_fit - Find a fit for a block with asize bytes 
 */
/* $begin mmfirstfit */
/* $begin mmfirstfit-proto */
static void *find_fit(size_t asize)
/* $end mmfirstfit-proto */
{
    /* $end mmfirstfit */

#ifdef NEXT_FIT 
    /* Next fit search */
    char *oldrover = rover;

    /* Search from the rover to the end of list */
    for ( ; GET_SIZE(HDRP(rover)) > 0; rover = NEXT_BLKP(rover))
        if (!GET_ALLOC(HDRP(rover)) && (asize <= GET_SIZE(HDRP(rover))))
            return rover;

    /* search from start of list to old rover */
    for (rover = heap_listp; rover < oldrover; rover = NEXT_BLKP(rover))
        if (!GET_ALLOC(HDRP(rover)) && (asize <= GET_SIZE(HDRP(rover))))
            return rover;

    return NULL;  /* no fit found */
#else 
    /* $begin mmfirstfit */
    /* First-fit search */
    void *bp;

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
            return bp;
        }
    }
    return NULL; /* No fit */
#endif
}
/* $end mmfirstfit */

static void printblock(void *bp) 
{
    size_t hsize, halloc, fsize, falloc;

    checkheap(0);
    hsize = GET_SIZE(HDRP(bp));
    halloc = GET_ALLOC(HDRP(bp));  
    fsize = GET_SIZE(FTRP(bp));
    falloc = GET_ALLOC(FTRP(bp));  

    if (hsize == 0) {
        printf("%p: EOL\n", bp);
        return;
    }

    printf("%p: header: [%ld:%c] footer: [%ld:%c]\n", bp, 
           hsize, (halloc ? 'a' : 'f'), 
           fsize, (falloc ? 'a' : 'f')); 
}

static void checkblock(void *bp) 
{
    if ((size_t)bp % 8)
        printf("Error: %p is not doubleword aligned\n", bp);
    if (GET(HDRP(bp)) != GET(FTRP(bp)))
        printf("Error: header does not match footer\n");
}

/* 
 * checkheap - Minimal check of the heap for consistency 
 */
void checkheap(int verbose) 
{
    char *bp = heap_listp;

    if (verbose)
        printf("Heap (%p):\n", heap_listp);

    if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp)))
        printf("Bad prologue header\n");
    checkblock(heap_listp);

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (verbose) 
            printblock(bp);
        checkblock(bp);
    }

    if (verbose)
        printblock(bp);
    if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp))))
        printf("Bad epilogue header\n");
}
```

## 9.18

```c
/* 
 * Simple, 32-bit and 64-bit clean allocator based on implicit free
 * lists, first-fit placement, and boundary tag coalescing, as described
 * in the CS:APP3e text. Blocks must be aligned to doubleword (8 byte) 
 * boundaries. Minimum block size is 16 bytes. 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mm.h"
#include "memlib.h"

/*
 * If NEXT_FIT defined use next fit search, else use first-fit search 
 */
#define NEXT_FITx

/* $begin mallocmacros */
/* Basic constants and macros */
#define WSIZE       4       /* Word and header/footer size (bytes) */ //line:vm:mm:beginconst
#define DSIZE       8       /* Double word size (bytes) */
#define CHUNKSIZE  (1<<12)  /* Extend heap by this amount (bytes) */  //line:vm:mm:endconst 

#define MAX(x, y) ((x) > (y)? (x) : (y))  

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc)  ((size) | (alloc)) //line:vm:mm:pack

/* Read and write a word at address p */
#define GET(p)       (*(unsigned int *)(p))            //line:vm:mm:get
#define PUT(p, val)  (*(unsigned int *)(p) = (val))    //line:vm:mm:put

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)                   //line:vm:mm:getsize
#define GET_ALLOC(p) (GET(p) & 0x1)                    //line:vm:mm:getalloc

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)       ((char *)(bp) - WSIZE)                      //line:vm:mm:hdrp
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) //line:vm:mm:ftrp

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE))) //line:vm:mm:nextblkp
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE))) //line:vm:mm:prevblkp
/* $end mallocmacros */

/* Global variables */
static char *heap_listp = 0;  /* Pointer to first block */  
#ifdef NEXT_FIT
static char *rover;           /* Next fit rover */
#endif

/* Function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);
static void printblock(void *bp); 
static void checkheap(int verbose);
static void checkblock(void *bp);

/* 
 * mm_init - Initialize the memory manager 
 */
/* $begin mminit */
int mm_init(void) 
{
    /* Create the initial empty heap */
    if ((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1) //line:vm:mm:begininit
        return -1;
    PUT(heap_listp, 0);                          /* Alignment padding */
    PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1)); /* Prologue header */ 
    PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1)); /* Alignment padding */ 
    PUT(heap_listp + (3*WSIZE), PACK(0, 1));     /* Epilogue header */
    heap_listp += (2*WSIZE);                     //line:vm:mm:endinit  
    /* $end mminit */

#ifdef NEXT_FIT
    rover = heap_listp;
#endif
    /* $begin mminit */

    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE/WSIZE) == NULL) 
        return -1;
    return 0;
}
/* $end mminit */

/* 
 * mm_malloc - Allocate a block with at least size bytes of payload 
 */
/* $begin mmmalloc */
void *mm_malloc(size_t size) 
{
    size_t asize;      /* Adjusted block size */
    size_t extendsize; /* Amount to extend heap if no fit */
    char *bp;      

    /* $end mmmalloc */
    if (heap_listp == 0){
        mm_init();
    }
    /* $begin mmmalloc */
    /* Ignore spurious requests */
    if (size == 0)
        return NULL;

    /* Adjust block size to include overhead and alignment reqs. */
    if (size <= DSIZE)                                          //line:vm:mm:sizeadjust1
        asize = 2*DSIZE;                                        //line:vm:mm:sizeadjust2
    else
        asize = DSIZE * ((size + (WSIZE) + (DSIZE-1)) / DSIZE); //line:vm:mm:sizeadjust3

    /* Search the free list for a fit */
    if ((bp = find_fit(asize)) != NULL) {  //line:vm:mm:findfitcall
        place(bp, asize);                  //line:vm:mm:findfitplace
        return bp;
    }

    /* No fit found. Get more memory and place the block */
    extendsize = MAX(asize,CHUNKSIZE);                 //line:vm:mm:growheap1
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)  
        return NULL;                                  //line:vm:mm:growheap2
    place(bp, asize);                                 //line:vm:mm:growheap3
    return bp;
} 
/* $end mmmalloc */

/* 
 * mm_free - Free a block 
 */
/* $begin mmfree */
void mm_free(void *bp)
{
    /* $end mmfree */
    if (bp == 0) 
        return;

    /* $begin mmfree */
    size_t size = GET_SIZE(HDRP(bp));
    /* $end mmfree */
    if (heap_listp == 0){
        mm_init();
    }
    /* $begin mmfree */

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}

/* $end mmfree */
/*
 * coalesce - Boundary tag coalescing. Return ptr to coalesced block
 */
/* $begin mmfree */
static void *coalesce(void *bp) 
{
    size_t prev_alloc = GET_ALLOC(HDRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) {            /* Case 1 */
        return bp;
    }

    else if (prev_alloc && !next_alloc) {      /* Case 2 */
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size,0));
    }

    else if (!prev_alloc && next_alloc) {      /* Case 3 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    else {                                     /* Case 4 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
            GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    /* $end mmfree */
#ifdef NEXT_FIT
    /* Make sure the rover isn't pointing into the free block */
    /* that we just coalesced */
    if ((rover > (char *)bp) && (rover < NEXT_BLKP(bp))) 
        rover = bp;
#endif
    /* $begin mmfree */
    return bp;
}
/* $end mmfree */

/*
 * mm_realloc - Naive implementation of realloc
 */
void *mm_realloc(void *ptr, size_t size)
{
    size_t oldsize;
    void *newptr;

    /* If size == 0 then this is just free, and we return NULL. */
    if(size == 0) {
        mm_free(ptr);
        return 0;
    }

    /* If oldptr is NULL, then this is just malloc. */
    if(ptr == NULL) {
        return mm_malloc(size);
    }

    newptr = mm_malloc(size);

    /* If realloc() fails the original block is left untouched  */
    if(!newptr) {
        return 0;
    }

    /* Copy the old data. */
    oldsize = GET_SIZE(HDRP(ptr));
    if(size < oldsize) oldsize = size;
    memcpy(newptr, ptr, oldsize);

    /* Free the old block. */
    mm_free(ptr);

    return newptr;
}

/* 
 * mm_checkheap - Check the heap for correctness
 */
void mm_checkheap(int verbose)  
{ 
    checkheap(verbose);
}

/* 
 * The remaining routines are internal helper routines 
 */

/* 
 * extend_heap - Extend heap with free block and return its block pointer
 */
/* $begin mmextendheap */
static void *extend_heap(size_t words) 
{
    char *bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE; //line:vm:mm:beginextend
    if ((long)(bp = mem_sbrk(size)) == -1)  
        return NULL;                                        //line:vm:mm:endextend

    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));         /* Free block header */   //line:vm:mm:freeblockhdr
    PUT(FTRP(bp), PACK(size, 0));         /* Free block footer */   //line:vm:mm:freeblockftr
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */ //line:vm:mm:newepihdr

    /* Coalesce if the previous block was free */
    return coalesce(bp);                                          //line:vm:mm:returnblock
}
/* $end mmextendheap */

/* 
 * place - Place block of asize bytes at start of free block bp 
 *         and split if remainder would be at least minimum block size
 */
/* $begin mmplace */
/* $begin mmplace-proto */
static void place(void *bp, size_t asize)
/* $end mmplace-proto */
{
    size_t csize = GET_SIZE(HDRP(bp));   

    if ((csize - asize) >= (2*DSIZE)) { 
        PUT(HDRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0));
        PUT(FTRP(bp), PACK(csize-asize, 0));
    }
    else { 
        PUT(HDRP(bp), PACK(csize, 1));
    }
}
/* $end mmplace */

/* 
 * find_fit - Find a fit for a block with asize bytes 
 */
/* $begin mmfirstfit */
/* $begin mmfirstfit-proto */
static void *find_fit(size_t asize)
/* $end mmfirstfit-proto */
{
    /* $end mmfirstfit */

#ifdef NEXT_FIT 
    /* Next fit search */
    char *oldrover = rover;

    /* Search from the rover to the end of list */
    for ( ; GET_SIZE(HDRP(rover)) > 0; rover = NEXT_BLKP(rover))
        if (!GET_ALLOC(HDRP(rover)) && (asize <= GET_SIZE(HDRP(rover))))
            return rover;

    /* search from start of list to old rover */
    for (rover = heap_listp; rover < oldrover; rover = NEXT_BLKP(rover))
        if (!GET_ALLOC(HDRP(rover)) && (asize <= GET_SIZE(HDRP(rover))))
            return rover;

    return NULL;  /* no fit found */
#else 
    /* $begin mmfirstfit */
    /* First-fit search */
    void *bp;

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
            return bp;
        }
    }
    return NULL; /* No fit */
#endif
}
/* $end mmfirstfit */

static void printblock(void *bp) 
{
    size_t hsize, halloc, fsize, falloc;

    checkheap(0);
    hsize = GET_SIZE(HDRP(bp));
    halloc = GET_ALLOC(HDRP(bp));  
    fsize = GET_SIZE(FTRP(bp));
    falloc = GET_ALLOC(FTRP(bp));  

    if (hsize == 0) {
        printf("%p: EOL\n", bp);
        return;
    }

    printf("%p: header: [%ld:%c] footer: [%ld:%c]\n", bp, 
           hsize, (halloc ? 'a' : 'f'), 
           fsize, (falloc ? 'a' : 'f')); 
}

static void checkblock(void *bp) 
{
    if ((size_t)bp % 8)
        printf("Error: %p is not doubleword aligned\n", bp);
    if (GET(HDRP(bp)) != GET(FTRP(bp)))
        printf("Error: header does not match footer\n");
}

/* 
 * checkheap - Minimal check of the heap for consistency 
 */
void checkheap(int verbose) 
{
    char *bp = heap_listp;

    if (verbose)
        printf("Heap (%p):\n", heap_listp);

    if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp)))
        printf("Bad prologue header\n");
    checkblock(heap_listp);

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (verbose) 
            printblock(bp);
        checkblock(bp);
    }

    if (verbose)
        printblock(bp);
    if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp))))
        printf("Bad epilogue header\n");
}
```

## 9.19

```
1) c
2) d
3) b
```

## 9.20

不做，完成Malloc Lab代替之

# Chapter10

## 10.6

```
fd2 = 4
```

## 10.7

```c
#include "csapp.h"
#define MAXBUF 128

int main(int argc, char* argv[]) {
	int n;
	rio_t rio;
	char buf[MAXLINE];
	
	Rio_readinitb(&rio, STDIN_FILENO);
	while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        while (n != 0) {
            int fit_size = n > MAXBUF? MAXBUF : n;
            Rio_writen(STDOUT_FILENO, buf, fit_size);
            n -= fit_size;
        }
    }
}
```

## 10.8

```c
#include "csapp.h"

int main(int argc, char* argv[]) {
    struct stat stat;
    char *type, *readok;
    int fd = atoi(argv[1]);
    
    fstat(fd, &stat);
    if (S_ISREG(stat.st_mode))
        type = "regular";
    else if (S_ISDIR(stat.st_mode))
        type = "directory";
    else
        type = "other";
    if ((stat.st_mode & S_IRUSR))
        readok = "yes";
    else
        readok = "no";
    
    printf("type: %s, read: %s\n", type, readok);
    exit(0);
}
```

## 10.9

不会

看了别人的题解还是不理解

## 10.10

```c
#include "csapp.h"

int main(int argc, char **argv) 
{
    int n;
    rio_t rio;
    char buf[MAXLINE];

    if (argc == 2) /* infile */
    {
        int fd = Open(argv[1], O_RDONLY|O_CREAT);
        Dup2(fd, STDIN_FILENO);
        Close(fd);
    }
    else if (argc > 2)
    {
        printf("usage: %s [--infile]\n", argv[0]);
    }

    Rio_readinitb(&rio, STDIN_FILENO);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) 
	    Rio_writen(STDOUT_FILENO, buf, n);

    return 0;
}
```

# Chapter12

## 12.16

```c
#include "csapp.h"
void *thread(void *vargp);

int main(int argc, char* argv[]) {
    int num, i;
    pthread_t *tid;
    
    if (argc != 2) {
        fprintf(stderr, "usage: %s <num>\n", argv[0]);
        exit(0);
    }
    
    num = atoi(agrv[1]);
    tid = Calloc(num, sizeof(pthread_t));
    for (i = 0; i < num; i++) {
        Pthread_create(&tid[i], NULL, thread, NULL);
    }
    for (i = 0; i < num; i++) {
        Pthread_join(tid, NULL);
    }
    exit(0);
}

void *thread(void *vargp) {
    printf("Hello, world!\n");
    return NULL;
}
```

## 12.17

```
A. 该线程睡眠时，主线程调用exit()函数，所有线程均强制结束，也就没来得及输出
B. Pthread_join()
```

## 12.18

```
A. unsafe
B. safe
C. unsafe
```

## 12.19

```c
int readcnt;					/* Initially = 0 */
sem_t mutex, w, reader_first; 	/* All initially = 1 */

void reader(void) {
    while (1) {
        P(&mutex);
        readcnt++;
        if (readcnt == 1) {
            P(&w);
        }
        V(&mutex);
        
        /* Critical section */
        /* Reading happens  */
        
        P(&mutex);
        readcnt--;
        if (readcnt == 0)
            V(&w);
        V(&mutex);
    }
}

void writer(void) {
    while (1) {
        P(&reader_first);
        P(&w);
        
        /* Critical section */
        /* writing happens  */
        
        V(&w);
        P(&mutex);
        V(&reader_first);
        V(&mutex);
    }
}
```

## 12.20

```c
sem_t mutex, w, readable; 		/* mutex, w initially = 1, readable initally n */

void reader(void) {
    while (1) {
        P(&readable);
        P(&mutex);
        P(&w);
        V(&mutex);
        
        /* Critical section */
        /* Reading happens  */
        
        P(&mutex);
        V(&w);
        V(&mutex);
        V(&readable);
    }
}

void writer(void) {
    while (1) {
        P(&w);
        
        /* Critical section */
        /* writing happens  */
        
        V(&w);
    }
}
```

## 12.21

```c
int writecnt, readcnt;			/* Both initially = 0 */
sem_t wmutex, rmutex, w, read; 		/* All initially = 1  */

void reader(void) {
    while (1) {
        P(&read);
        P(&rmutex);
        readcnt++;
        if (readcnt == 1)
            P(&w);
        V(&rmutex);
        V(&read);
        
        /* Critical section */
        /* Reading happens  */
        
        P(&rmutex);
        readcnt--;
        if (readcnt == 0)
        	V(&w);
        V(&mutex);
    }
}

void writer(void) {
    while (1) {
        P(&wmutex);
        writecnt++;
        if (writecnt == 1) 
            P(&read);
        V(&wmutex);
        
        P(&w);
        /* Critical section */
        /* writing happens  */
        V(&w);
        
        P(&wmutex);
        writecnt--;
        if (writecnt == 0)
            V(&read);
        V(&w);
    }
}
```

