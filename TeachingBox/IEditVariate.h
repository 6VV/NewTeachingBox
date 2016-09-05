#ifndef _TEACHING_BOX_I_EDIT_VARIATE_H_
#define _TEACHING_BOX_I_EDIT_VARIATE_H_

class TVariate;

class IEditVariate
{
public:
	virtual void OnNewVariate(TVariate& variate)=0;
};

#endif