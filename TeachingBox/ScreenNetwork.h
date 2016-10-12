#ifndef _TEACHING_BOX_SCREEN_NETWORK_H_
#define _TEACHING_BOX_SCREEN_NETWORK_H_

#include "InternationalWidget.h"
#include "IScreenNetwork.h"

class QListWidget;
class Button;

class ScreenNetwork:public InternationalWidget,public IScreenNetwork
{
	Q_OBJECT

public:
	ScreenNetwork(QWidget* parent);
	~ScreenNetwork();

private:
	virtual void UpdateText() override;
	virtual void OnNewAddress(const QString& address) override;

	void Init();
	void InitLayout();
	void InitSignalSlot();

	bool IsValidAddress(const QString& address);

private slots:
	void SlotOnAddClicked();
	void SlotOnDeleteClicked();
	void SlotOnConnectClicked();

private:
	QListWidget* m_listWidgetHost;
	Button* m_btnAdd;
	Button* m_btnDelete;
	Button* m_btnConnect;
};

#endif