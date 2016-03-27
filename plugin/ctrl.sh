#!/bin/bash  

WORK_PATH=$(pwd)
SERVER=${WORK_PATH}
CLIENT=${WORK_PATH}/../client
LOG=${WORK_PATH}/../log
CONF=${WORK_PATH}/../conf

SERVICE_NAME=chat_server

proc=$(basename $0)

function usage(){
	printf "\033[31m \033[05m%s%s%s\033[0m\n" "Uasge: ${proc} ["  "start(-s) | stop(-t) | restart(-r) | status(-u)" "]"
}

function print_log(){
	local _msg="$1"
	local _level="$2"
	local _data=$(date +%Y_%m_%d_%H/%M/%S)
	echo "[${_data}] [${_msg}] [${_level}]" # >> ${LOG}/server.log
}

function server_status(){
	local ret=$(pidof ${SERVICE_NAME})
	if [ -z ${ret} ];then
		print_log "${SERVICE_NAME} status is  close..." "Notice"
		return 1
	else
		print_log "${SERVICE_NAME} status is  running..." "Notice"
		return  0
	fi
}

function server_start(){
	if  server_status ;then 
		print_log "${SERVICE_NAME} is already running..." "Notice"
	else
		local port=$(more ${CONF}/server.conf  | awk -F ':' '{print $2}' | tr -d ' ')
		pushd ${SERVER} >> /tmp/null
		./${SERVICE_NAME} ${port}
		print_log "${SERVICE_NAME}  running success..." "Notice"
	fi
}

function server_stop(){
	if server_status ;then 
		kill -9 `pidof ${SERVICE_NAME}`
		print_log "${SERVICE_NAME}  stop success..." "Notice"
	else
		print_log "${SERVICE_NAME} is already stop..." "Notice"
	fi
}

function server_restart(){
		server_stop
		server_start
}

case $1 in
	'start'|'-s')
		server_start
	;;
	'stop'|'-t')
		server_stop
	;;
	'restat'|'-r')
		server_restart
	;;
	'status'|'-u')
		server_status
	;;
	*)
		usage
	;;
esac
