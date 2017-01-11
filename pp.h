#ifndef PP_H
#define PP_H

/*
 * only support gcc 
 *
 * test with 
 * gcc 4.9.3 
 * gcc 6.2.0
 * 
 * test config:
 * 	enable test block __TEST_BLOCK__
 * 
 * test command:
 *      gcc -E pp.h > test.h && sed -i 's/#/\/\//g' test.h && gcc -Wall -O2 -o a.out test.c && ./a.out
 */

/*
 * concate
 */
#define PP_CAT(x, y) PP_CAT_I(x, y)
#define PP_CAT_I(x, y) x ## y

/*
 * stringify
 */
#define PP_STR(x) PP_STR_I(x)
#define PP_STR_I(x) #x

/*
 * expr strigify
 */
#define PP_EXPR(...) PP_EXPR_I(__VA_ARGS__)
#define PP_EXPR_I(...) #__VA_ARGS__

/*
 * varadic size
 */
#define PP_VA_SIZE(...) PP_VA_SIZE_I(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, \
				57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, \
				45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, \
				33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, \
				21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
				9, 8, 7, 6, 5, 4, 3, 2, 1,)

#define PP_VA_SIZE_I(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, \
		e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, \
		e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, \
		e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, \
		e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, \
		e61, e62, e63, size, ...) size

/*
 * evaluate
 */
#define PP_EVAL(...) PP_EVAL1024(__VA_ARGS__)
#define PP_EVAL1024(...) PP_EVAL512(PP_EVAL512(__VA_ARGS__))
#define PP_EVAL512(...) PP_EVAL256(PP_EVAL256(__VA_ARGS__))
#define PP_EVAL256(...) PP_EVAL128(PP_EVAL128(__VA_ARGS__))
#define PP_EVAL128(...) PP_EVAL64(PP_EVAL64(__VA_ARGS__))
#define PP_EVAL64(...) PP_EVAL32(PP_EVAL32(__VA_ARGS__))
#define PP_EVAL32(...) PP_EVAL16(PP_EVAL16(__VA_ARGS__))
#define PP_EVAL16(...) PP_EVAL8(PP_EVAL8(__VA_ARGS__))
#define PP_EVAL8(...) PP_EVAL4(PP_EVAL4(__VA_ARGS__))
#define PP_EVAL4(...) PP_EVAL2(PP_EVAL2(__VA_ARGS__))
#define PP_EVAL2(...) PP_EVAL1(PP_EVAL1(__VA_ARGS__))
#define PP_EVAL1(...) __VA_ARGS__

/*
 * overload 
 *  
 * PP_OVERLOAD(test_, x)(x) -> test_1(x)
 * PP_OVERLOAD(test_, x, y)(x, y) -> test_2(x, y)
 */
#define PP_OVERLOAD(m, ...) PP_CAT(m, PP_VA_SIZE(__VA_ARGS__))

/* 
 * empty 
 */
#define PP_EMPTY()

/*
 * eat
 */
#define PP_EAT(...)

/*
 * expand
 */
#define PP_EXPAND(...) __VA_ARGS__

/*
 * expand to first
 */
#define PP_FIRST(x, ...) x

/*
 * expand to second
 */
#define PP_SECOND(x, y, ...) y

/*
 * defer expand
 */
#define PP_DEFER(x) x PP_EMPTY()
#define PP_DEFER2(x) x PP_EMPTY PP_EMPTY()()

/*
 * probe 
 *  
 * PP_IS_PROBE(x) 0 
 * PP_IS_PROBE(PP_PROBE()) 1
 */
#define PP_IS_PROBE(...) PP_SECOND(__VA_ARGS__, 0)
#define PP_PROBE() ~, 1

/*
 * zero
 */
#define PP_IS_ZERO(x) PP_IS_PROBE(PP_CAT(PP_IS_ZERO_, x))
#define PP_IS_ZERO_0 PP_PROBE()

/*
 * not zero
 */
#define PP_BOOL(x) PP_IS_ZERO(PP_IS_ZERO(x))

/*
 * and
 */
#define PP_AND(x, y) PP_BITAND(PP_BOOL(x), PP_BOOL(y))
#define PP_BITAND(x, y) PP_BITAND_I(x, y)
#define PP_BITAND_I(x, y) PP_BITAND_ ## x ## y
#define PP_BITAND_00 0
#define PP_BITAND_01 0
#define PP_BITAND_10 0
#define PP_BITAND_11 1

/*
 * or
 */
#define PP_OR(x, y) PP_BITOR(PP_BOOL(x), PP_BOOL(y))
#define PP_BITOR(x, y) PP_BITOR_I(x, y)
#define PP_BITOR_I(x, y) PP_BITOR_ ## x ## y
#define PP_BITOR_00 0
#define PP_BITOR_01 1
#define PP_BITOR_10 1
#define PP_BITOR_11 1

/*
 * nor
 */
#define PP_NOR(x, y) PP_BITNOR(PP_BOOL(x), PP_BOOL(y))
#define PP_BITNOR(x, y) PP_BITNOR_I(x, y)
#define PP_BITNOR_I(x, y) PP_BITNOR_ ## x ## y
#define PP_BITNOR_00 1
#define PP_BITNOR_01 0
#define PP_BITNOR_10 0
#define PP_BITNOR_11 0

/*
 * xor
 */
#define PP_XOR(x, y) PP_BITXOR(PP_BOOL(x), PP_BOOL(y))
#define PP_BITXOR(x, y) PP_BITXOR_I(x, y)
#define PP_BITXOR_I(x, y) PP_BITXOR_ ## x ## y
#define PP_BITXOR_00 0
#define PP_BITXOR_01 1
#define PP_BITXOR_10 1
#define PP_BITXOR_11 0

/* 
 * comp 
 */
#define PP_COMPL(x) PP_COMPL_I(PP_BOOL(x))
#define PP_COMPL_I(x) PP_CAT(PP_COMPL_, x)
#define PP_COMPL_0 1
#define PP_COMPL_1 0

/*
 * has parenthesis
 */
#define PP_HAS_PAREN(x) PP_IS_PROBE(PP_HAS_PAREN_PROBE x)
#define PP_HAS_PAREN_PROBE(...) PP_PROBE()

/*
 * has arguments
 */
#define PP_HAS_ARGS(...) PP_BOOL(PP_FIRST(PP_HAS_ARGS_PROBE __VA_ARGS__)())
#define PP_HAS_ARGS_PROBE() 0

/*
 * has empty
 */
#define PP_HAS_EMPTY(...) PP_IS_ZERO(PP_HAS_ARGS(__VA_ARGS__))

/*
 * has multiple  
 */
#define PP_HAS_MANY(...) PP_BOOL(PP_HAS_MANY_PROBE(__VA_ARGS__))
#define PP_HAS_MANY_PROBE(...) PP_VA_SIZE_I(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, \
					1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
					1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
					1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
					1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
					1, 1, 1, 1, 1, 1, 1, 1, 0,)

/*
 * has unary
 */
#define PP_HAS_UNARY(...) \
	PP_HAS_UNARY_I(PP_OR(PP_HAS_EMPTY(__VA_ARGS__), PP_HAS_MANY(__VA_ARGS__)))
#define PP_HAS_UNARY_I(x) PP_COMPL(x)

/*
 * has comma
 */
#define PP_HAS_COMMA(...) PP_HAS_MANY(__VA_ARGS__)

/*
 * dispatch
 */
#define PP_DISPATCH(x) PP_DISPATCH_I(PP_BOOL(x))
#define PP_DISPATCH_I(x) PP_CAT(PP_DISPATCH_I_, x)
#define PP_DISPATCH_I_1(...) __VA_ARGS__ PP_EAT
#define PP_DISPATCH_I_0(...) PP_EXPAND

/*
 * select
 */
#define PP_IF(expr, x, y) PP_IF_I(expr, x, y)
#define PP_IF_I(expr, x, y) PP_EVAL(PP_DEFER(PP_IIF)(expr)(x,y))
#define PP_IIF(x) PP_IIF_I(PP_BOOL(x))
#define PP_IIF_I(x) PP_CAT(PP_IIF_I_, x)
#define PP_IIF_I_1 PP_FIRST
#define PP_IIF_I_0 PP_SECOND

/*
 * PP_MAP(@m, @a1, @a2, ... @an) 
 * --> @m(@a1) , @m(@a2) , ... , @m(@an)
 */
#define PP_MAP(m, ...) \
	PP_DISPATCH(PP_HAS_ARGS(__VA_ARGS__)) \
		(PP_EVAL(PP_MAP_I(m, __VA_ARGS__))) \
		()
#define PP_MAP_I(m, x, ...) \
	m(x) \
	PP_DISPATCH(PP_HAS_ARGS(__VA_ARGS__)) \
		(, PP_DEFER2(PP_MAP_II)()(m, __VA_ARGS__)) \
		()
#define PP_MAP_II() PP_MAP_I
/*
 * PP_MAP2(@m, @a1, @b1, @a2, @b2, ..., @an, @bn) 
 * --> @m(@a1, @b1) , @m(@a2, @b2) , ... , @m(@an, @bn)
 */
#define PP_MAP2(m, ...) \
	PP_DISPATCH(PP_HAS_ARGS(__VA_ARGS__)) \
		(PP_EVAL(PP_MAP2_I(m, __VA_ARGS__))) \
		()
#define PP_MAP2_I(m, x, y, ...) \
	m(x, y) \
	PP_DISPATCH(PP_HAS_ARGS(__VA_ARGS__)) \
		(, PP_DEFER2(PP_MAP2_II)()(m, __VA_ARGS__)) \
		()
#define PP_MAP2_II() PP_MAP2_I

/*
 * PP_JOIN(@d, @a1, @a2, ..., @an)
 * --> @a1 @d @a2 @d ... @d @an
 */
#define PP_JOIN(d_, ...) \
	PP_DISPATCH(PP_HAS_ARGS(__VA_ARGS__)) \
		(PP_EVAL(PP_JOIN_I(d_, __VA_ARGS__))) \
		()
#define PP_JOIN_I(d, x, ...) \
	x \
	PP_DISPATCH(PP_HAS_ARGS(__VA_ARGS__)) \
		(d PP_DEFER2(PP_JOIN_II)()(d, __VA_ARGS__)) \
		()
#define PP_JOIN_II() PP_JOIN_I

/*
 * compare
 * object-likc macro is comparable if only if x(a)->a
 */
#define PP_IS_COMPARABLE(x) PP_HAS_PAREN( x (()) )

#define PP_NOT_EQUAL(x, y) \
	PP_IF(PP_AND(PP_IS_COMPARABLE(x), PP_IS_COMPARABLE(y)), \
	      PP_NOT_EQUAL_I, \
	      1 PP_EAT) \
	(x, y)
#define PP_NOT_EQUAL_I(x, y)  PP_HAS_PAREN(x (y)(()))

#define PP_EQUAL(x, y) PP_COMPL(PP_NOT_EQUAL(x, y))

#undef__TEST_BLOCK__
#ifdef __TEST_BLOCK__

#define test_checker(orig, expand, match) { orig, expand, match }
#define TEST_CHECKER(orig, match) test_checker(#orig, PP_EXPR(orig), match)

#define TEST_RECURSE() R PP_DEFER(TEST_RECURSE_I) ()()
#define TEST_RECURSE_I() TEST_RECURSE

#define TEST_MAP1(x) <<x>>
#define TEST_MAP2(x) [[ x
#define TEST_MAP3(x) x ]]

#define TEST_MAP2_1(x, y) x ** y

#define comparable_a(x) x
#define comparable_b(x) x

struct test_info {
       const char *origin;
       const char *expand;
       const char *match;
};

struct test_info test__[] = {
	TEST_CHECKER(PP_VA_SIZE(), "1"),
	TEST_CHECKER(PP_VA_SIZE(a), "1"),
	TEST_CHECKER(PP_VA_SIZE(a, b), "2"),
	TEST_CHECKER(PP_VA_SIZE(a, b, c), "3"),

	TEST_CHECKER(PP_EMPTY(), ""),
	TEST_CHECKER(PP_CAT(a, b), "ab"),

	TEST_CHECKER(PP_FIRST(a), "a"),
	TEST_CHECKER(PP_FIRST(a, b), "a"),
	TEST_CHECKER(PP_FIRST(a, b, c), "a"),

	TEST_CHECKER(PP_SECOND(a, b), "b"),
	TEST_CHECKER(PP_SECOND(a, b, c), "b"),

	TEST_CHECKER(PP_IS_ZERO(0), "1"),
	TEST_CHECKER(PP_IS_ZERO(1), "0"),
	TEST_CHECKER(PP_IS_ZERO(123), "0"),
	TEST_CHECKER(PP_IS_ZERO(abc), "0"),

	TEST_CHECKER(PP_BOOL(0), "0"),
	TEST_CHECKER(PP_BOOL(1), "1"),
	TEST_CHECKER(PP_BOOL(123), "1"),
	TEST_CHECKER(PP_BOOL(abc), "1"),

	TEST_CHECKER(PP_HAS_ARGS(), "0"),
	TEST_CHECKER(PP_HAS_ARGS(0), "1"),
	TEST_CHECKER(PP_HAS_ARGS(a, b, c), "1"),

	TEST_CHECKER(PP_AND(0,0), "0"),
	TEST_CHECKER(PP_AND(0,1), "0"),
	TEST_CHECKER(PP_AND(1,0), "0"),
	TEST_CHECKER(PP_AND(1,1), "1"),

	TEST_CHECKER(PP_OR(0,0), "0"),
	TEST_CHECKER(PP_OR(0,1), "1"),
	TEST_CHECKER(PP_OR(1,0), "1"),
	TEST_CHECKER(PP_OR(1,1), "1"),

	TEST_CHECKER(PP_NOR(0,0), "1"),
	TEST_CHECKER(PP_NOR(0,1), "0"),
	TEST_CHECKER(PP_NOR(1,0), "0"),
	TEST_CHECKER(PP_NOR(1,1), "0"),

	TEST_CHECKER(PP_XOR(0,0), "0"),
	TEST_CHECKER(PP_XOR(0,1), "1"),
	TEST_CHECKER(PP_XOR(1,0), "1"),
	TEST_CHECKER(PP_XOR(1,1), "0"),

	TEST_CHECKER(PP_COMPL(0), "1"),
	TEST_CHECKER(PP_COMPL(1), "0"),
	TEST_CHECKER(PP_COMPL(not zero), "0"),

	TEST_CHECKER(PP_HAS_EMPTY(), "1"),
	TEST_CHECKER(PP_HAS_EMPTY(0), "0"),
	TEST_CHECKER(PP_HAS_EMPTY(a, b, c), "0"),

	TEST_CHECKER(PP_HAS_MANY(), "0"),
	TEST_CHECKER(PP_HAS_MANY(a), "0"),
	TEST_CHECKER(PP_HAS_MANY(a, b), "1"),

	TEST_CHECKER(PP_HAS_UNARY(), "0"),
	TEST_CHECKER(PP_HAS_UNARY(a), "1"),
	TEST_CHECKER(PP_HAS_UNARY(a, b), "0"),

	TEST_CHECKER(PP_HAS_COMMA(), "0"),
	TEST_CHECKER(PP_HAS_COMMA(0), "0"),
	TEST_CHECKER(PP_HAS_COMMA(a, b), "1"),
	TEST_CHECKER(PP_HAS_COMMA(, b), "1"),
	TEST_CHECKER(PP_HAS_COMMA(a, ), "1"),
	TEST_CHECKER(PP_HAS_COMMA(,), "1"),

	TEST_CHECKER(PP_HAS_PAREN(), "0"),
	TEST_CHECKER(PP_HAS_PAREN(a), "0"),
	TEST_CHECKER(PP_HAS_PAREN(()), "1"),
	TEST_CHECKER(PP_HAS_PAREN((a)), "1"),
	TEST_CHECKER(PP_HAS_PAREN((a, b)), "1"),

	TEST_CHECKER(PP_DISPATCH(0)(abc)(def), "def"),
	TEST_CHECKER(PP_DISPATCH(1)(abc)(def), "abc"),
	TEST_CHECKER(PP_DISPATCH(not zero)(abc)(def), "abc"),

	TEST_CHECKER(TEST_RECURSE(), "R R TEST_RECURSE_I ()()"),
	TEST_CHECKER(PP_EVAL1(TEST_RECURSE()), "R R R TEST_RECURSE_I ()()"),
	TEST_CHECKER(PP_EVAL2(TEST_RECURSE()), "R R R R R TEST_RECURSE_I ()()"),

	TEST_CHECKER(PP_MAP(TEST_MAP1), ""),
	TEST_CHECKER(PP_MAP(TEST_MAP1, a), "<<a>>"),
	TEST_CHECKER(PP_MAP(TEST_MAP1, a, b), "<<a>> , <<b>>"),
	TEST_CHECKER(PP_MAP(TEST_MAP1, a, b, c), "<<a>> , <<b>> , <<c>>"),

	TEST_CHECKER(PP_MAP2(TEST_MAP2_1), ""),
	TEST_CHECKER(PP_MAP2(TEST_MAP2_1, a, 1), "a ** 1"),
	TEST_CHECKER(PP_MAP2(TEST_MAP2_1, a, 1, b, 2), "a ** 1 , b ** 2"),

	TEST_CHECKER(PP_JOIN(;), ""),
	TEST_CHECKER(PP_JOIN(;, a), "a"),
	TEST_CHECKER(PP_JOIN(;, a, b), "a ; b"),
	TEST_CHECKER(PP_JOIN(;, a, b, c), "a ; b ; c"),

	TEST_CHECKER(PP_MAP(TEST_MAP2, PP_MAP(TEST_MAP3)), ""),
	TEST_CHECKER(PP_MAP(TEST_MAP2, PP_MAP(TEST_MAP3, a)), "[[ a ]]"),
	TEST_CHECKER(PP_MAP(TEST_MAP2, PP_MAP(TEST_MAP3, a, b)),
	       "[[ a ]] , [[ b ]]"),
	TEST_CHECKER(PP_MAP(TEST_MAP2, PP_MAP(TEST_MAP3, a, b, c)),
	       "[[ a ]] , [[ b ]] , [[ c ]]"),

	TEST_CHECKER(PP_IF(1, a, b), "a"),
	TEST_CHECKER(PP_IF(0, a, b), "b"),
	TEST_CHECKER(PP_IF(not zero, a, b), "a"),

	TEST_CHECKER(PP_OVERLOAD(f,a)(a), "f1(a)"),
	TEST_CHECKER(PP_OVERLOAD(f,a,b)(a,b), "f2(a,b)"),

	TEST_CHECKER(PP_NOT_EQUAL(comparable_a, comparable_b), "1"),
	TEST_CHECKER(PP_NOT_EQUAL(comparable_a, comparable_a), "0"),
	TEST_CHECKER(PP_NOT_EQUAL(comparable_b, comparable_b), "0"),
	TEST_CHECKER(PP_NOT_EQUAL(comparable_a, not comparable), "1"),
	TEST_CHECKER(PP_NOT_EQUAL(not comparable, comparable_b), "1"),

	TEST_CHECKER(PP_EQUAL(comparable_a, comparable_b), "0"),
	TEST_CHECKER(PP_EQUAL(comparable_a, comparable_a), "1"),
	TEST_CHECKER(PP_EQUAL(comparable_b, comparable_b), "1"),
	TEST_CHECKER(PP_EQUAL(comparable_a, not comparable), "0"),
	TEST_CHECKER(PP_EQUAL(not comparable, comparable_b), "0"),

	{0, 0, 0},
};
#endif /* __TEST_BLOCK__ */

#endif /* PP_H */
