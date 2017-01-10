#include "stdafx.h"
#include "RemoteFeedbackController.h"
#include "IRemoteFeedbackListener.h"
#include "DataStruct.h"


void RemoteFeedbackController::AddListener(IRemoteFeedbackListener* listener)
{
	m_listeners.insert(listener);
}

void RemoteFeedbackController::DeleteListener(IRemoteFeedbackListener* listener)
{
	m_listeners.erase(listener);
}

RemoteFeedbackController* RemoteFeedbackController::GetInstance()
{
	static RemoteFeedbackController controller;
	return &controller;
}

void RemoteFeedbackController::OnReseivePosition(const tAxesAllPositions& position)
{
	for (auto iter:m_listeners)
	{
		iter->OnReseivePosition(position);
	}
}

void RemoteFeedbackController::OnReseivePoseEuler(const tPoseEuler& pose)
{
	for (auto iter : m_listeners)
	{
		iter->OnReseivePose(pose);
	}
}

