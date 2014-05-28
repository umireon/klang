[![Build Status](https://travis-ci.org/umireon/klang.svg?branch=master)](https://travis-ci.org/umireon/klang)

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
bin/calc
```
