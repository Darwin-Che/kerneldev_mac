#!/bin/bash

patch_name=''
rtdir=$(pwd)

if [[ $# -ne 0 ]]; then
	patch_name=$1
fi

if [[ $patch_name = 'lx' ]]; then
	patch_name='epoll_memo'
	patch_dir='linux'
elif [[ $patch_name = 'fb' ]]; then
	patch_name='libfibre'
	patch_dir='apps/libfibre'	
else
	echo "no patch available"
	exit 1
fi

echo "patch_name : $patch_name"
echo "patch_dir : $patch_dir"
read

pushd $patch_dir 

patch $2 -p1 < $rtdir/patch/$patch_name.patch

popd
