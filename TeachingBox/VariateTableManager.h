#ifndef _TEACHING_BOX_VARIATE_TABLE_MANAGER_H_
#define _TEACHING_BOX_VARIATE_TABLE_MANAGER_H_

#include "QObject"
#include <memory>
#include "TVariate.h"

class QTableWidget;
class QLineEdit;
class QComboBox;

class TVariate;

namespace VariateWidget{

	class VariateTableManager:public QObject
	{
		Q_OBJECT

	private:
		static const int INIT_ROW_NUM = 3;
		static const int COLUMN_NUM = 2;

	public:
		VariateTableManager(QWidget* parent);

		QTableWidget* GetTableWidget(const QString& scope);
		std::unique_ptr<TVariate> GetVariate();

		void UpdateText();

		bool IsValidVariate();

	public slots:
		void ChangeToType(const QString& type);

	private:
		std::unique_ptr<TVariate> GetInterger(const QString& name, const QString& scope);
		std::unique_ptr<TVariate> GetDouble(const QString& name, const QString& scope);
		std::unique_ptr<TVariate> GetBool(const QString& name, const QString& scope);
		std::unique_ptr<TVariate> GetString(const QString& name, const QString& scope);
		std::unique_ptr<TVariate> GetPosition(const QString& name, const QString& scope);
		std::unique_ptr<TVariate> GetDynamic(const QString& name, const QString& scope);
		std::unique_ptr<TVariate> GetOverlap(const QString& name, const QString& scope);

		void InitIntParameter();
		void InitDoubleParameter();
		void InitBoolParameter();
		void InitStringParameter();
		void InitPositionParameter();
		void InitDynamicParameter();
		void InitOverlapParameter();

		bool IsValidName();

	private:
		QTableWidget* m_tableWidget;

		QLineEdit* m_lineEidtName;
		QComboBox* m_comboBoxScope;
		QComboBox* m_comboBoxType;
	};

}

#endif