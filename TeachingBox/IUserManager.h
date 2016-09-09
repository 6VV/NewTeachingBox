#ifndef _TEACHIGN_BOX_I_USER_MANAGER_H_
#define _TEACHIGN_BOX_I_USER_MANAGER_H_

class IUserManager
{
public:
	virtual ~IUserManager(){};
	virtual void OnUpdate() = 0;
};

#endif