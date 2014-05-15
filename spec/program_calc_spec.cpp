#include <igloo/igloo_alt.h>
using namespace igloo;

#define Pending printf("P");return

bool accepts(const char *str)
{
	printf("P");
	return true;
}

Describe(プログラム電卓) {
	It(四則演算を受け入れる) {Pending;
		Assert::That(accepts("1+2*3-4/5"));
	}
	It(丸括弧を受け入れる) {Pending;
		Assert::That(accepts("2*(3+4)"));
	}
	It(実数を受け入れる) {Pending;
		Assert::That(accepts("1.234"));
	}
	It(べき乗を受け入れる) {Pending;
		Assert::That(accepts("2**3"));
	}
	It(剰余を受け入れる) {Pending;
		Assert::That(accepts("4%2"));
	}
	It(三角関数を受け入れる) {Pending;
		Assert::That(accepts("sin(1)"));
	}
	It(対数関数を受け入れる) {Pending;
		Assert::That(accepts("log(1)"));
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
};
