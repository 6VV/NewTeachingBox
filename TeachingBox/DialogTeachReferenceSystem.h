#ifndef _TEACHING_BOX_DIALOG_TEACH_REFERENCE_SYSTEM_H_
#define _TEACHING_BOX_DIALOG_TEACH_REFERENCE_SYSTEM_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenTeachReferenceSystem.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/14
//  Description:	用于生成参考坐标系示教界面，该界面以对话框的形式出现。
		共包括三种示教方法：1、3点（含原点）示教法；2、三点（无原点）示教法；3、一点（保持姿态）示教法。
		对于每种方法的每一步骤，都提供指导界面及示意图进行操作。
		可在任意步骤下停止操作。

//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/14
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "DialogParent.h"
#include "QMap"
#include "QVector"
#include "IRemoteFeedbackListener.h"

class TRefSys;
class ICoordinate;
struct tPoseEuler;

class DialogTeachReferenceSystem :public DialogParent
{
	Q_OBJECT

private:
	using FunctionCreateStepWidget = QWidget*(DialogTeachReferenceSystem::*)();

public:
	DialogTeachReferenceSystem(TRefSys* oldVariate, ICoordinate* iCoor = nullptr, QWidget* parent = nullptr);

	virtual void UpdateText() override;

private:
	QWidget* GetReferenceSystemWidget();
	QWidget* GetTeachMethodWidget();
	QWidget* GetTeachToolWidget();
	QWidget* GetIllustrationWidget();
	QLayout* GetButtonLayout();

	QWidget* GetEndWidget();

	void Init();

	QWidget* OnePointKeepOrientationStep1();
	QWidget* OriginWidget();

	QWidget* PointWidget();

	QWidget* ThreePointsWithOriginWidgetStep1();
	QWidget* ThreePointsWithOriginWidgetStep2();
	QWidget* ThreePointsWithOriginWidgetStep3();

	QWidget* ThreePointsWithoutOriginWidgetStep1();
	QWidget* ThreePointsWithoutOriginWidgetStep2();
	QWidget* ThreePointsWithoutOriginWidgetStep3();

	void UpdatePoseEuler(const tPoseEuler& point);


private:
/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  class name: 	Controller
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/15
//  Description:	私有嵌入类，用于保存并控制坐标系示教过程的状态及步骤
	包含以下内容：
		原始变量的内容
		选择的示教方法
		当前示教步骤
		各示教方法中的示教步骤控件的生成函数
	提供一些功能：
		进入下一步骤
		进入上一步骤
		是否还有下一步骤
		是否还有上一步骤
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/15
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/
	class Controller:public IRemoteFeedbackListener
	{
	public:
		/*示教方法*/
		enum TeachMethod
		{
			THREE_POINTS_WITH_ORIGIN,	/*三点（含原点）*/
			THREE_POINTS_WITHOUT_ORIGIN,	/*三点（不含原点）*/
			ONE_POINT_KEEP_ORIENTATION,	/*一点（保持姿态）*/
		};

	public:
		Controller(DialogTeachReferenceSystem* screenTeachReferenceSystem,TRefSys* variate);
		~Controller();

		void NextStep();
		void PreStep();

		bool HaveNextStep();
		bool HavePreStep();

		tPoseEuler GetDesPoseEuler() const;

	private:
		virtual void OnReseivePose(const tPoseEuler& pose) override;

		bool IsTeached();

	public:
		TRefSys* m_oldVariate;	/*原变量*/
		TeachMethod m_teachMethod{ THREE_POINTS_WITH_ORIGIN };	/*当前示教方法*/

	private:
		DialogTeachReferenceSystem* m_screenTeachReferenceSystem;	/*示教窗口父控件*/
		int m_step = -1;	/*当前步骤，-1表示示教方法选择过程*/
		bool m_isTeached = false;
		QMap<TeachMethod, QVector<DialogTeachReferenceSystem::FunctionCreateStepWidget>> m_stepMap;	/*记录各示教方法中的示教步骤控件的生成函数*/

		std::shared_ptr<tPoseEuler> m_poseEuler = nullptr;	/*当前坐标系*/
		std::vector<std::shared_ptr<tPoseEuler>> m_poses{};	/*已记录坐标系*/
		tPoseEuler m_desPoseEuler{};	/*目标坐标系*/
	};

	/*************************************************
	//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
	//  class name:	    RefSysWidget
	//  Author:			刘巍      
	//  Version: 		1.0     
	//  Date: 			2016/12/26
	//  Description:    用于生成坐标控件，并监听远程返回的坐标信息
	//  Others:         
	//  Function List:  
	//  History:
	//    <author>      刘巍 
	//    <time>        2016/12/26
	//    <version>     1.0 
	//    <desc>        build this moudle     
	*************************************************/
	class RefSysWidget :public QWidget,IRemoteFeedbackListener
	{
	public:
		RefSysWidget(QWidget* parent = 0);
		~RefSysWidget();

	private:
		virtual void OnReseivePose(const tPoseEuler& pose) override;

	private:
		QLineEdit* m_lbX;
		QLineEdit* m_lbY;
		QLineEdit* m_lbZ;
	};

	/*示教完成界面*/
	class EndWidget :public QWidget
	{
	public:
		EndWidget(QWidget* parent = 0);

		void Update(const tPoseEuler& poseEuler);
	private:
		QLineEdit* m_ltX;
		QLineEdit* m_ltY;
		QLineEdit* m_ltZ;
		QLineEdit* m_ltA;
		QLineEdit* m_ltB;
		QLineEdit* m_ltC;
	};

	Controller m_controller;
	QWidget* m_currentWidget = nullptr;
	QGridLayout* m_mainLayout = nullptr;
	QLabel* m_lbIllustration=nullptr;
	ICoordinate* m_iCoor=nullptr;
};

#endif