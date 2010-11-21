#!/bin/sh

WHAM=../src/wham

if [ ! -e ${WHAM} ] ; then
	exit 1
fi

# Butane test

${WHAM} -v -p 6.28 -i butane > butane.out

exit 0
