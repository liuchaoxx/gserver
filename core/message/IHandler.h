#ifndef _IHANDLER_H
#define _IHANDLER_H

#include "ICommand.h"
#include "CMessage.h"

class IHandler : public ICommand
{
public:
	virtual VOID Action() = 0;
	/**
	 * @desc 设置指令消息
	 */
	VOID SetMessage(CMessage msg) { this->_msg = msg;};
	/**
	 * @desc 设置接受者
	 */
	VOID SetParam(VOID* param) {this->_param = param;};
protected:
	//指令消息
	CMessage* _msg;
	//指令接受者
	VOID*	_param;
};

#endif