#!/bin/bash

PATH=libfibre/apps:$PATH

numcon=2

if [[ $# > 0 ]]; then
	numcon=$1
fi

echotest -a 0.0.0.0 -c $numcon -p 8888 -s &
sleep 0.01
echotest -a 0.0.0.0 -c $numcon -p 8888

