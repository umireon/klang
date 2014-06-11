---
layout: page
---

使用方法
========================================

klang:001:0> のような表示があるので、続けて式を入力すると計算結果が#=> の後に表示される。

新たに変数を定義するときは，変数 = 式 のように入力する。変数が代入された関数以下でスコープが決まる。

```
klang:001:0> a=1+2
#=> 3
```

演算子には+,-,\*,/,%(余剰),\*\*(べき乗)等の算術演算子に加え、=,<,>,<=,>=等の関係演算子，and,or,not等の論理演算子が利用できる。
機能の項目で示すように科学定数、三角関数や組み合わせ関数などが予め定義されている。
また、新たな関数を自ら定義することも可能である。

klangではベクトルや行列の計算にも対応している。次の例では行ベクトルtを定義し，その2乗を計算している。

ベクトルの生成 c(...)
----------------------------------------
```
> t=c(1,2,3)
#=> [ 1 2 3 ]
> t**2
#=> [ 1 4 9 ]
```

※要素がxからyまでの連続する整数値であれば，seq(x,y)のように表すこともできる。
```
> seq(1,3)
#=> [ 1 2 3 ]
```

ベクトルから行列をつくる matrix(c(...),行,列)
----------------------------------------
```
>matrix(c(1,2,3,4,5,6,7,8,9),3,3)
#=> [
1 2 3
4 5 6
7 8 9
]
```


入力にエラーがあった場合、エラーのあった場所を文字単位で指摘する。
```
> +++++4
Unexpected Character; +in line 1
Raised in read_number_signed
+_+_+++4

Unexpected Character; +in line 1
Raised in read_number_signed
++_+_++4

Unexpected Character; +in line 1
Raised in read_number_signed
+++_+_+4

Unexpected Character; +in line 1
Raised in read_number_signed
++++_+_4

#=> 0
```

exitの入力で終了する。



特徴
========================================
1. 文末区切り文字を使用せずに文末を確定できる。
例えば,
```>if k>2 fibo(k-1)+fibo(k-2) else 1```
あるいは、
```>if k>2fibo(k-1)+fibo(k-2)else 1```
　のような書き方ができる。
2. 実行速度が高速
3. メモリ使用量が少なく軽量

文法記法
========================================
```
　Expression :=Assignment

　Assignment := Compare ｛｀=´ Compare｝

　Compare := ArithExpression ｛(｀>´|｀<´)[｀=´] ArithExpression｝

　ArithExpression := Term ｛(｀+´|｀-´) Term｝

　Term := Primary ｛(｀/´|｀*´[｀*´]|｀%´) Term｝

　Primary := Number | Identifier | Invocation | If | Function

　Function := ｀function´ Parameter (Expression|Compound)

　Compound := '{' {Expression} '}'

　Parameter := '(' ({Identifier ','}Identifier|'')')'

　If := ｀if´ Expression (Expression|Compound) {｀elsif´ Expression 　(Expression|　　Compound)}  [｀else´ (Expression|Compound)]

　Paren := '(' Expression ')'

　Number := Integer | Float

　Integer := Octal | Decimal | Hexdecimal

　Octal := [｀+´|｀-´]｀0´[0-7]*

　Decimal := [｀+´|｀-´][0-9]*

　Hexdecimal := [｀+´|｀-´]｀0´[xX][0-9A-Fa-f]*

　Float := [｀+´|｀-´][1-9][0-9]*｀.´[0-9][0-9]*

　Identifier := [A-Za-z]+
```

その他の機能
========================================
リテラル表記に対応した16進数、8進数での計算
----------------------------------------
```
> 0x10
#=> 16
```

科学定数
----------------------------------------
定義されている科学定数を次に示す。

Klang上での識別子|    実際の値
:--------------- |:---------------:
PI               | 円周率π
E                | e（ネイピア数）
C                | 光の速さ
NA               | アボガドロ数
R                | 1molの気体定数
F   　           | ファラデー定数
G                | 万有引力定数
H                | プランク定数
K                | ボルツマン定数
RYDBERG_CONST    | リュードベリ定数
E0               | 真空の誘電率
MU0              | 真空の透磁率
EC               | 電気素量
MACH             | 音速
GRAVITY_EARTH    | 重力加速度
　　

ブール演算
----------------------------------------
and, or, notを組み合わせた論理演算

Σ、Π
----------------------------------------
集合（行列）の直和、直積の計算
```
> Σ => sum(c(1,2,3,4,5))
#=> 15
```

対数
----------------------------------------
log(x),log2(x),log10(x)

```
>log(2)
#=> 0.30103
```

三角関数,逆三角関数,双曲線関数,逆双曲線関数
----------------------------------------
- sin(x),cos(x),tan(x)
- arcsin(x),arccos(x),arctan(x)
- sinh(x),cosh(x),tanh(x)
- arcsinh(x),arccosh(x),arctanh(x)

sin(KInteger x) : KFloat
  　与えられた整数のsin値を浮動小数で返す．
sin(KFloat x) : KFloat
  　与えられた浮動小数のsin値を浮動小数で返す．

平方根
----------------------------------------
sqrt

誤差関数，誤差補関数
----------------------------------------
erf,erfc

切り上げ，切り捨て，四捨五入
----------------------------------------
ceil,floor,round

階乗(x!)
----------------------------------------
fact(KInteger x) : KInteger
与えられた整数の階乗を整数で返す。x<0ならば，1を返す。

perm型関数
----------------------------------------
perm(nPr),comb(nCr),hmpr(nHr)

- perm(KInteger n, KInteger r) : KInteger
　　nPrを整数で返す。
- comb(KInteger n, KInteger r) : KInteger
　　nCrを整数で返す。
- hmpr(KInteger n, KInteger r) : KInteger
　　nHrを整数で返す。

print系
----------------------------------------
print,puts

c(KFloat x,…) : KVector
----------------------------------------
浮動小数をまとめて，数値ベクトルとして返す。

seq(KInteger first, KInteger last) : KVector
----------------------------------------
c(first, first+1, …, last)と同等。
  
sum型
----------------------------------------
sum,prod
- sum(KObject x, ..) : KFloat
  　引数に指定されたすべての数の合計を浮動小数で返す。
- prod(KObject x, ..) : KFloat
  　引数に指定されたすべての数の積を浮動小数で返す。

for(KVector v, KFunction f) : KObject
----------------------------------------
vの要素を1つずつ取り出し，fの第一引数に渡して実行する。
最後のfの実行によって得られた返り値が返される。
例)
```
> sum=0
> for (c(1,2,3,4,5)*2, function(x) sum=sum+x)
#=>30
```

if式
----------------------------------------
例)
```
>a=1
>if a=1 5
#=> 5
>if a=0 5 else 6
#=> 6
```

関数の定義
----------------------------------------
関数を自ら宣言して定義することができる。
再起呼び出しを用いてフィボナッチ数列を求める関数の定義例を示す。
例)
```
> fibo = function(k) if k>2 fibo(k-1)+fibo(k-2) else 1
> fibo(30)
#=> 832040
```

