Klangは，定義済み関数や定数を提供し，カスタム関数を定義することができる，拡張可能なプログラム電卓の実装である．

構文解析，実行
====================

Klangは，入力された文字列を解釈するために構文解析器を備えている．
Klangの構文解析器は，再帰下降法を用い，字句解析と構文解析を同時に行っている．
再起降下法は，文法をプログラムの構造として記述するための方法の一種で，非終端記号の出現を関数呼び出しで表現する，という点で特徴付けられる．
Klangの字句解析器は，基本的には1文字を1つの字句としているが，数値や識別子が現れた場合は，その終端までを1つの字句として切り出している．

Klangの構文解析器は，構文解析の結果をAST(Abstract Syntax Tree, 抽象構文木)として保存する．
KlangのASTは，文字列で記述されたプログラムから，空白や行番号といった，意味解析では無視されるものを取り除き，文法にしたがってプログラムを木構造で表現したものである．

Klangは，インタプリタ型の実行モデルを採用している．
Klangは，構文解析の結果得られたASTを，後行順で走査し実行結果を得る，インタプリタ型の実行エンジンを持つ．

文法のEBNF表記
-----
次のリストは，Klangの文法を，空白文字を考慮せずにEBNFで表記したものである．
```
(* 終端文字定義 *)
alphabet = "A" | "B" | "C" | "D" | "E" | "F" | "G"
         | "H" | "I" | "J" | "K" | "L" | "M" | "N"
         | "O" | "P" | "Q" | "R" | "S" | "T" | "U"
         | "V" | "W" | "X" | "Y" | "Z"
         | "a" | "b" | "c" | "d" | "e" | "f" | "g"
         | "h" | "i" | "j" | "k" | "l" | "m" | "n"
         | "o" | "p" | "q" | "r" | "s" | "t" | "u"
         | "v" | "w" | "x" | "y" | "z" ;
octdigit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" ;
decdigit = octdigit | "8" | "9" ;
nonzero = "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
hexdigit = decdigit
         | "a" | "b" | "c" | "d" | "e" | "f"
         | "A" | "B" | "C" | "D" | "E" | "F" ;
alnum = alphabet | decdigit ;

(* 式 *)
Expression = Assignment ;

(* 代入文 *)
Assignment = Compare, { "=", Compare } ;

(* 比較演算子 *)
Compare = ArithExpression, { ( ">" | "<" ), [ "=" ], ArithExpression } ;

(* 算術式 *)
ArithExpression = Term, { ( "+" | "-" ), Term } ;

(* 算術項 *)
Term = Primary, { ( "/" | "*", [ "*" ] | "%" ), Primary } ;

(* 分解不能単位 *)
Primary = Function | Identifier | Invocation | If | Number | Paren ;

(* 関数呼び出し *)
Invocation = Identifier, "(", ( { Expression, ',' }, Expression | "" ), ")" ;

(* 仮引数 *)
Parameter = '(', ( { Identifier, ',' }, Identifier | "" ), ')' ;

(* ブロック *)
Compound = '{', { Expression }, '}' ;

(* 関数式 *)
Function = "function", Parameter, ( Expression | Compound ) ;

(* 識別子 *)
Identifier = alphabet, { alnum } ;

(* if式 *)
If = "if", Expression, ( Expression | Compound ),
   { "elsif", Expression, ( Expression | Compound ) },
   [ "else", ( Expression | Compound ) ] ;

(* 数値 *)
Number = [ "+" | "-" ], ( OctHex | DecFloat ) ;
OctHex = "0", ( Octal | Hexdecimal ) ;
Octal = { octdigit } ;
Hexdecimal = ( "x" | "X" ), hexdigit, { hexdigit } ;
DecFloat = nonzero, { decdigit }, [ Float ] ;
Float = ".", decdigit, { decdigit } ;

(* 括弧 *)
Paren = '(', Expression, ')' ;
```

次のリストは，Klangの文法を，空白文字を考慮してEBNFで表記したものである．
```
(* 終端文字定義 *)
alphabet = "A" | "B" | "C" | "D" | "E" | "F" | "G"
         | "H" | "I" | "J" | "K" | "L" | "M" | "N"
         | "O" | "P" | "Q" | "R" | "S" | "T" | "U"
         | "V" | "W" | "X" | "Y" | "Z"
         | "a" | "b" | "c" | "d" | "e" | "f" | "g"
         | "h" | "i" | "j" | "k" | "l" | "m" | "n"
         | "o" | "p" | "q" | "r" | "s" | "t" | "u"
         | "v" | "w" | "x" | "y" | "z" ;
octdigit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" ;
decdigit = octdigit | "8" | "9" ;
nonzero = "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
hexdigit = decdigit
         | "a" | "b" | "c" | "d" | "e" | "f"
         | "A" | "B" | "C" | "D" | "E" | "F" ;
alnum = alphabet | decdigit ;
whitespace = " " | "\n" | "\r" ;
w = { whitespace } ;

(* 入力 *)
Input = w, Expression ;

(* 式 *)
Expression = Assignment ;

(* 代入文 *)
Assignment = Compare, { w, "=", Compare } ;

(* 比較演算子 *)
Compare = ArithExpression, { w, ( ">" | "<" ), [ "=" ], w, ArithExpression } ;

(* 算術式 *)
ArithExpression = Term, { w, ( "+" | "-" ), w, Term } ;

(* 算術項 *)
Term = Primary, { w, ( "/" | "*", [ "*" ] | "%" ), w, Primary } ;

(* 分解不能単位 *)
Primary = Function | Identifier | Invocation | If | Number | Paren ;

(* 関数呼び出し *)
Invocation = Identifier, w, "(", [ { w, Expression, ',' }, w, Expression ], w, ")" ;

(* 仮引数 *)
Parameter = '(', [ { w, Identifier, ',' }, w, Identifier ], w, ')' ;

(* ブロック *)
Compound = '{', { w, Expression }, w, '}' ;

(* 関数式 *)
Function = "function", w, Parameter, w, ( Expression | Compound ) ;

(* 識別子 *)
Identifier = alphabet, { alnum } ;

(* if式 *)
If = "if", w, Expression, w, ( Expression | Compound ),
   { w, "elsif", w, Expression, w, ( Expression | Compound ) },
   [ w, "else", w, ( Expression | Compound ) ] ;

(* 数値 *)
Number = [ "+" | "-" ], ( OctHex | DecFloat ) ;
OctHex = "0", ( Octal | Hexdecimal ) ;
Octal = { octdigit } ;
Hexdecimal = ( "x" | "X" ), hexdigit, { hexdigit } ;
DecFloat = nonzero, { decdigit }, [ Float ] ;
Float = ".", decdigit, { decdigit } ;

(* 括弧 *)
Paren = '(', w, Expression, w, ')' ;
```

型システム
====================
Klangは，計算結果をKObject，KNumber，KInteger，KFloat，KVector，KNilといった，6つの型で区別している．

KObjectは，Klangのすべてのオブジェクトの元となる型で，以下のいずれの型もKObjectと見なすことができる．

KNumberは，数値全般を表す型で，KIntegerやKFloatは，KNumberの具体的な実装であると考えられる．
KNumberは，四則演算，剰余や冪乗の演算子を用いて，計算式を書くことが可能な型である．

KIntegerは，整数を表す型である．
KIntegerは，整数リテラルによって生成される．
整数リテラルは，8進数リテラル，10進数リテラル，16進数リテラルで構成される．
8進数リテラルは，```0```，```-012```や```+012```というように表記される．
10進数リテラルは，```12```，```-12```や```+12```というように表記される．
16進数リテラルは，```0xa0```，```+0xa0```や```-0XA0```というように表記される．
KIntegerは，浮動小数として評価されると，小数点以下を0とした値を返す．

KFloatは，浮動小数を表す型である．
KFloatは，浮動小数リテラルによって生成される．
浮動小数リテラルは，```0.2```，```-1.2```や```+1.2```というように表記される．
KFloatは，整数として評価されると，小数点以下を切り捨てた値を返す．

KVectorは，浮動小数を複数集めたベクトルを表す型である．
KVectorは，後述する```c```関数によって，生成される．
KVectorは，四則演算，剰余や冪乗の演算子を用いて，計算式を書くことが可能な型である．

KNilは，関数に計算不能な値を与えたときに，計算値の代わりに返す値である．
KNilは，数値として評価すると，0と見なされる．

KInteger，KFloatとKVectorは，演算子を用いて演算可能な型である．
演算可能な型は，演算結果の型を一意に決定するため，優先順位を持っている．
演算可能な型の優先順位は，KVectorが最も高く，次いでKFloat，KIntegerというようになっている．

演算子
====================
Klangは，2項演算子を用いて計算をする機能を備えている．
次のリストは，Klangが受け入れる演算子を，結合優先度が高い順に並べ，結合の方向を付したものである．
- 右結合 =
- 右結合 **
- 左結合 * / %
- 左結合 + -
- 左結合 > < >= <=

以上で挙げた演算子は，すべて次のような方法で使用する．
``` 左引数 演算子 右引数 ```

``` = ```は，代入演算子である．
``` ** ```は，算術演算子の1つであり，冪乗を表す．
``` * ```は，算術演算子の1つであり，乗算を表す．
``` / ```は，算術演算子の1つであり，除算を表す．
``` % ```は，算術演算子の1つであり，剰余を表す．
``` + ```は，算術演算子の1つであり，加算を表す．
``` - ```は，算術演算子の1つであり，減算を表す．
``` > ```は，比較演算子の1つであり，左引数が右引数より大きいかどうかを判定する．
``` < ```は，比較演算子の1つであり，左引数が右引数より小さいかどうかを判定する．
``` >= ```は，比較演算子の1つであり，左引数が右引数以上かどうかを判定する．
``` >= ```は，比較演算子の1つであり，左引数が右引数以下かどうかを判定する．


算術演算子
--------------------
算術演算子の返り値の型は，引数のうち最も優先順位が高いものになる．
例えば，算術演算子は，KIntegerとKIntegerを与えると，KIntegerを返すが，KIntegerとKFloatを与えると，KFloatを返す．
また，算術演算子は，KNumberとKVectorを与えたり，KVectorとKVectorを与えたりすると，KVectorを返す．

算術演算子に与える引数が，2つともKNumberであれば，算術演算子，一般的な意味での計算を行う．
引数がKNumberとKVectorであれば，算術演算子は，KVectorの全要素にKNumberを作用させる．
引数が2つともKVectorであれば，算術演算子は，2つの引数のKVectorの，同じ位置にある要素同士を作用させ，結果をKVector型で返す．
ただし，剰余演算子は，浮動小数に対して定義できないので，KFloatをすべてKIntegerに変換した上で処理を行い，返り値もKFloatの代わりにKIntegerを返す．

比較演算子
--------------------
比較演算子は，引数としてKNumberのみをとり，それ以外を与えると，必ず真となる．
比較演算子は，条件が真であればKInteger(1)を返し，偽であればKInteger(0)を返す．
この値は，論理関数やif式で使用可能である．

if式
====================
if式は，次のような形式の式である．
```
if 条件式 真の場合
if 条件式 真の場合 else 偽の場合
if 条件式 真の場合 elsif 条件式 真の場合 else 偽の場合
```
条件式が真の場合は，条件式の直後の式が評価され，その値が返る．
条件式が偽で，後ろにelseがない場合は，KNilが返る．
条件式が偽で，後ろにelseがある場合は，elseの直後の式が評価され，その値が返る．
条件式が偽で，後ろにelsifがある場合は，elsifをifと読み替え，同じことを繰り返す．


変数
====================
代入
--------------------
代入演算子は，Klangで変数を扱うことを可能にする．
関数宣言は，代入演算子を用いて行われる．
以下のリストは，関数宣言の例である．
```
fibo = function(x) if k>2 fibo(k-1)+fibo(k-2) else 1
```

スコープ
--------------------
Klangの変数は，必ずどこかのスコープに所属している．
Klangのスコープは，グローバルスコープと関数スコープの2つで構成される．
関数の外側で代入された変数は，グローバルスコープに所属する．
グローバルスコープの変数は，プログラムが終了するまで保持される．
関数の内側で代入された変数は，関数スコープに所属する．
関数スコープの変数は，関数の終了とともに破棄される．

グローバルスコープであらかじめ変数を定義しておくことによって，関数終了後にも破棄されない変数を作ることが可能である．
後述のfor関数は，この性質を活用している．

組み込み関数
====================
関数のプロトタイプ宣言は，以下のような形式であると定義する．
```
func1(A x, B y) : C
func2(D z, ...) : E
```
このとき，```func1```関数は，A型の引数```x```とB型の引数```y```を取り，C型の値を返す．
また，```func2```関数は，D型の引数```z```を任意の数だけ取り，E型の値を返す．

数学関数については，ユーザマニュアルを参照のこと．

c関数
--------------------
``` c ```関数は，KVectorを生成するための関数である．
関数のプロトタイプは，以下のようになる．
```
c(KNumber x, ...) : KVector
```
引数には，任意の数の引数を指定することが可能である．

次のリストは，```c```関数の使用例である．
```
c(1,2,3)
```

seq関数
--------------------
``` seq ```関数は，数列を生成するための関数である．
関数のプロトタイプは，以下のようになる．
```
seq(KInteger first, KInteger last) : KVector
```
引数には，任意の数の引数を指定することが可能である．

次のリストは，```c```関数の使用例である．
```
c(1,2,3)
```

for関数
--------------------
``` for ```関数は，繰り返しを行うための関数である．
関数のプロトタイプは，以下のようになる．
```
for(KVector list, KFunction func) : KObject
```

for関数は，listに含まれる浮動小数を1つずつ取り出し，funcの第一引数に渡して，funcを実行する．
for関数の返り値は，最後に実行されたfuncの返り値となる．

次のリストは，```for```関数の使用例である．
```
sum = 0
for(seq(1,10), function(x) sum = sum + x)
```
変数``` sum ```は，関数の外側で宣言されているので，関数実行が完了しても消去されない．
したがって，```sum```には，1から10までの総和が格納されることになる．

