#!/bin/bash
ROOT=`pwd`
BIN=${ROOT}/chat_server

service iptables stop
${BIN} 8080
