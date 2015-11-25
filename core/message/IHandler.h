#ifndef _IHANDLER_H
#define _IHANDLER_H

#include "ICommand.h"
#include "CMessage.h"

class IHandler : public ICommand
{
public:
	virtual VOID Action() = 0;
	/**
	 * @desc ����ָ����Ϣ
	 */
	VOID SetMessage(CMessage msg) { this->_msg = msg;};
	/**
	 * @desc ���ý�����
	 */
	VOID SetParam(VOID* param) {this->_param = param;};
protected:
	//ָ����Ϣ
	CMessage* _msg;
	//ָ�������
	VOID*	_param;
};

#endif