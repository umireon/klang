[![Build Status](https://travis-ci.org/umireon/klang.svg?branch=master)](https://travis-ci.org/umireon/klang)
[![Coverage Status](https://img.shields.io/coveralls/umireon/klang.svg)](https://coveralls.io/r/umireon/klang?branch=master)

# 依存ライブラリ
- Boost
- libedit
- CMake

# TDD
```
bundle install
CC=clang CXX=clang++ bundle exec guard
```

# ビルド方法
```
mkdir build
cd build
CC=clang CXX=clang++ cmake -DTEST=ON ..
make
make test
```

# 実行
```
./ast_calc
```
