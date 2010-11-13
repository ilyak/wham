#! /bin/sh -e

autoreconf --install

args="--enable-developer-warnings \
--enable-debugging-symbols \
--enable-werror \
--enable-stack-protector"

./configure ${args} $@
