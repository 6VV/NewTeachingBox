#ifndef _TEACHING_BOX_VARIATE_TABLE_MANAGER_H_
#define _TEACHING_BOX_VARIATE_TABLE_MANAGER_H_

#include "QObject"
#include "TVariate.h"

class QTableWidget;
class QLineEdit;
class QComboBox;

class TVariate;

namespace VariateWidget{
	class WidgetManagerNewVariate;

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
		std::unique_ptr<WidgetManagerNewVariate> GetWidgetManager(const QString& type) const;

		bool IsValidName();
	private:
		std::unique_ptr<WidgetManagerNewVariate> m_currentWidgetManager;

		QTableWidget* m_tableWidget;

		QLineEdit* m_lineEidtName;
		QComboBox* m_comboBoxScope;
		QComboBox* m_comboBoxType;
	};

}

#endif