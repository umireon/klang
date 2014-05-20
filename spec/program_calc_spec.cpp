/**
 * @file program_calc_spec.cpp
 * @author 宇田川海斗
 * @author 佐野公章
 * @author 吉里陸
 */

#include <igloo/igloo_alt.h>
using namespace igloo;

#include <string.h>

#include "../src/parser.h"

#define Pending std::cout << "P";return;

int accepts(const char *str)
{
	AstNode *stmt = parse(str);
	return (strlen(stmt->strtail) == 0);
}

Describe(プログラム電卓) {
	It(四則演算を受け入れる) {
		Assert::That(accepts("1+2*3-4/5"));
	}

	It(丸括弧を受け入れる) {
		Assert::That(accepts("2*(3+4)"));
	}

	It(実数を受け入れる) {Pending;
		Assert::That(accepts("1.234"));
	}

	It(べき乗を受け入れる) {Pending;
		Assert::That(accepts("2**3"));
		Assert::That(accepts("10^4"));
	}

	It(剰余を受け入れる) {Pending;
		Assert::That(accepts("4%2"));
	}

	It(対数関数を受け入れる) {Pending;
		Assert::That(accepts("log(1)"));
		Assert::That(accepts("log10(1)"));
	}

	It(代入を受け入れる) {Pending;
		Assert::That(accepts("a=2"));
	}

	It(比較演算子を受け入れる) {Pending;
		Assert::That(accepts("1 <= 2"));
		Assert::That(accepts("1 < 2"));
		Assert::That(accepts("2 > 1"));
		Assert::That(accepts("2 >= 1"));
		Assert::That(accepts("1 == 1"));
		Assert::That(accepts("1 != 2"));
	}

	It(if文を受け入れる) {Pending;
		Assert::That(accepts("if 1 < 2 then 2 elsif 3 <= 4 then 4 else 5 end"));
		Assert::That(accepts("if (1 < 2) {2} elsif (3 <= 4) {4} else {5}"));
	}

	It(三項演算子を受け入れる) {Pending;
		Assert::That(accepts("1<2?2:3"));
	}

	It(総積計算を受け入れる){Pending;
		Assert::That(accepts("product(list)"));
	}

	It(行列を受け入れる){Pending;
		Assert::That(accepts("A={{1,2},{3,4}}"));
	}

	It(行列の計算を受け入れる){Pending;
		Assert::That(accepts("A+B"));
		Assert::That(accepts("A-B"));
		Assert::That(accepts("A*B"));
		Assert::That(accepts("det(A)"));
		Assert::That(accepts("inverse(A)"));
		Assert::That(accepts("trace(A)"));
		Assert::That(accepts("cof(A,1,2)"));
		Assert::That(accepts("cofmat(A)"));
		Assert::That(accepts("abs(A)"));
	}

	It(グラフ描画を受け入れる){Pending;
		Assert::That(accepts("draw(X,Y)"));
	}

	It(最小二乗法を受け入れる){Pending;
		Assert::That(accepts("minsq(X,Y)"));
	}

	It(三角関数を受け入れる) {Pending;
		Assert::That(accepts("sin(1)"));
		Assert::That(accepts("cos(1)"));
		Assert::That(accepts("tan(1)"));
		Assert::That(accepts("sin^2(1)"));
	}

	It(乱数を受け入れる) {Pending;
		Assert::That(accepts("rand(1)"));
		Assert::That(accepts("rand()"));
	}

	It(単位を受け入れる) {Pending;
		Assert::That(accepts("1Y"));
		Assert::That(accepts("1Z"));
		Assert::That(accepts("1E"));
		Assert::That(accepts("1P"));
		Assert::That(accepts("1T"));
		Assert::That(accepts("1G"));
		Assert::That(accepts("1M"));
		Assert::That(accepts("1k"));
		Assert::That(accepts("1h"));
		Assert::That(accepts("1da"));
		Assert::That(accepts("1d"));
		Assert::That(accepts("1m"));
		Assert::That(accepts("1μ"));
		Assert::That(accepts("1n"));
		Assert::That(accepts("1p"));
		Assert::That(accepts("1f"));
		Assert::That(accepts("1a"));
		Assert::That(accepts("1z"));
		Assert::That(accepts("1y"));
		Assert::That(accepts("1s"));
		Assert::That(accepts("1m"));
		Assert::That(accepts("1kg"));
		Assert::That(accepts("1A"));
		Assert::That(accepts("1K"));
		Assert::That(accepts("1mol"));
		Assert::That(accepts("1cd"));
		Assert::That(accepts("1dozen"));
		Assert::That(accepts("1Pa"));
	}

	It(アボガドロ定数を受け入れる) {Pending;
		Assert::That(accepts("NA"));
		Assert::That(accepts("mol"));
	}
	It(気体定数を受け入れる) {Pending;
		Assert::That(accepts("R"));
	}
	It(ファラデー定数を受け入れる) {Pending;
		Assert::That(accepts("F"));
	}
	It(光速を受け入れる) {Pending;
		Assert::That(accepts("c"));
	}
	It(万有引力定数を受け入れる) {Pending;
		Assert::That(accepts("G"));
	}
};
