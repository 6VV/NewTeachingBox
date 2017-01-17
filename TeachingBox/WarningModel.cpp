#include "stdafx.h"
#include "WarningModel.h"
#include "WarningInfo.h"
#include <assert.h>
#include "TeachingBoxBroadcast.h"


const QString WarningModel::CATEFORY_INFO_ICON_PATH = ":/new/image/Resources/Image/info_icon.png";

const QString WarningModel::CATEFORY_WARNING_ICON_PATH = ":/new/image/Resources/Image/warning_icon.png";

const QString WarningModel::CATEFORY_ERROR_ICON_PATH = ":/new/image/Resources/Image/error_icon.png";

const QString WarningModel::STATE_SOLVED_ICON_PATH = ":/new/image/Resources/Image/confirm_icon.png";

const QString WarningModel::STATE_TO_BE_SOLVED_ICON_PATH = ":/new/image/Resources/Image/wrong_icon.png";

const QString WarningModel::STATE_WITHOUT_SOLVE_ICON_PATH = ":/new/image/Resources/Image/without_solve_icon.png";

WarningModel* WarningModel::GetInstance()
{
	static WarningModel model;
	return &model;
}

WarningModel::WarningModel(QWidget* parent /*= nullptr*/)
	:QAbstractTableModel(parent)
	, m_allInfos(std::make_shared<std::deque<std::shared_ptr<WarningInfo>>>())
	, m_currentInfos(std::make_shared<std::deque<std::shared_ptr<WarningInfo>>>())
{
	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::WarningThrowed, [this](const WarningInfo& info){
		PushFront(std::make_shared<WarningInfo>(info));
	});
}

Q_INVOKABLE int WarningModel::rowCount(const QModelIndex &/*parent = QModelIndex()*/) const
{
	return m_currentInfos->size();
}

Q_INVOKABLE int WarningModel::columnCount(const QModelIndex &/*parent = QModelIndex()*/) const
{
	return 4;
}

Q_INVOKABLE QVariant WarningModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
	if (!index.isValid())
	{
		return QVariant{};
	}

	switch (role)
	{
	case Qt::DecorationRole:{
		switch (index.column())
		{
		case 0:{
			auto category = m_currentInfos->at(index.row())->GetCategory();
			QString iconPath{};
			switch (category)
			{
			case WarningInfo::CATEFORY_INFO:{iconPath = CATEFORY_INFO_ICON_PATH; }break;
			case WarningInfo::CATEFORY_WARNING:{iconPath = CATEFORY_WARNING_ICON_PATH; } break;
			case WarningInfo::CATEFORY_ERROR:{iconPath = CATEFORY_ERROR_ICON_PATH; } break;
			default:
				break;
			}
			return QIcon(QPixmap(iconPath));
		}break;
		case 1:{
			auto state = m_currentInfos->at(index.row())->GetState();
			QString iconPath{};
			switch (state)
			{
			case WarningInfo::STATE_TO_BE_SOLVED:{iconPath = STATE_TO_BE_SOLVED_ICON_PATH; }break;
			case WarningInfo::STATE_SOLVED:{iconPath = STATE_SOLVED_ICON_PATH; } break;
			case WarningInfo::STATE_WITHOUT_SOLVE:{iconPath = STATE_WITHOUT_SOLVE_ICON_PATH; } break;
			default:
				break;
			}
			return QIcon(QPixmap(iconPath));
		}break;
		default:
			break;
		}
	}break;
	case Qt::DisplayRole:case Qt::EditRole:{
		switch (index.column())
		{
		case 2:{
			return m_currentInfos->at(index.row())->GetDateTime();
		}break;
		case 3:{
			return m_currentInfos->at(index.row())->GetDescribe();
		}break;
		default:
			break;
		}
	}break;
	case Qt::TextAlignmentRole:{
		return Qt::AlignCenter;
	}break;
	default:
		break;
	}

	return QVariant{};
}

QVariant WarningModel::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		switch (section)
		{
		case 0:{return tr("Category"); }break;
		case 1:{return tr("State"); }break;
		case 2:{return tr("Time"); }break;
		case 3:{return tr("Describe"); }break;
		default:return QVariant{}; break;
		}
	}

	return QVariant{};
}


bool WarningModel::setData(const QModelIndex &index, const QVariant &value, int /*role = Qt::EditRole*/)
{
	if (!index.isValid())
	{
		return false;
	}

	if (index.column()==2)
	{
		m_currentInfos->at(index.row())->SetDateTime(value.toString());

		emit dataChanged(index, index);
		return true;
	}
	else if (index.column()==1)
	{
		if (!IsCouldBeSolved(*m_currentInfos->at(index.row())))
		{
			return false;
		}
		m_currentInfos->at(index.row())->SetState(static_cast<WarningInfo::State>(value.toInt()));

		emit dataChanged(index, index);
		return true;
	}

	return false;
}

Qt::ItemFlags WarningModel::flags(const QModelIndex &index) const
{
	Qt::ItemFlags flags = QAbstractItemModel::flags(index);
	if (index.column()==2)
	{
		flags |= Qt::ItemIsEditable;
	}

	return flags;
}

void WarningModel::ChangeMode(WarningInfo::Category category)
{
	m_category = category;

	beginResetModel();

	switch (category)
	{
	case WarningInfo::CATEGORY_ALL:{
		m_currentInfos->clear();
		for (auto info : *m_allInfos)
		{
			m_currentInfos->push_back(info);
		}
	}
		break;
	case WarningInfo::CATEFORY_INFO:
	case WarningInfo::CATEFORY_WARNING :
	case WarningInfo::CATEFORY_ERROR:{
		m_currentInfos->clear();
		for (auto info : *m_allInfos)
		{
			if (info->GetCategory()==category)
			{
				m_currentInfos->push_back(info);
			}
		}
	}
	default:
		break;
	}

	endResetModel();
}

WarningInfo WarningModel::GetWarningInfo(int index) const
{
	assert(static_cast<size_t>(index) < m_allInfos->size());

	return *(m_allInfos->at(index));
}

bool WarningModel::IsCouldRemove(const WarningInfo& info) const
{
	return info.GetCategory() == WarningInfo::CATEFORY_INFO || info.GetState() == WarningInfo::STATE_SOLVED;
}

bool WarningModel::IsCouldBeSolved(const WarningInfo& info) const
{
	//return info.GetState() == WarningInfo::STATE_TO_BE_SOLVED;
	return info.GetState() != WarningInfo::STATE_SOLVED;
}

bool WarningModel::RemoveAll()
{
	if (m_currentInfos->size() == 0)
	{
		return false;
	}

	beginResetModel();

	m_allInfos->erase(std::remove_if(m_allInfos->begin(), m_allInfos->end(), [this](std::shared_ptr<WarningInfo> info){
		return IsCouldRemove(*info) && (info->GetCategory() == m_category || m_category==WarningInfo::CATEGORY_ALL);
	}), m_allInfos->end());

	auto iter = std::remove_if(m_currentInfos->begin(), m_currentInfos->end(), [this](std::shared_ptr<WarningInfo> info){
		return IsCouldRemove(*info);
	});

	/*若未删除元素*/
	if (iter==m_currentInfos->end()){
		return false;
	}

	m_currentInfos->erase(iter, m_currentInfos->end());

	endResetModel();

	return true;
}

bool WarningModel::RemoveRow(int row)
{
	/*若为普通信息或已解决信息，则删除该信息*/
	if (IsCouldRemove(*(m_currentInfos->at(row))))
	{
		beginRemoveRows(QModelIndex(), row, row);
		m_allInfos->erase(std::remove(m_allInfos->begin(), m_allInfos->end(), *(m_currentInfos->begin() + row)),m_allInfos->end());
		m_currentInfos->erase(m_currentInfos->begin() + row);
		endRemoveRows();

		return true;
	}

	return false;
}

bool WarningModel::RemoveBack()
{
	if (m_currentInfos->size() == 0)
	{
		return false;
	}

	int index = m_currentInfos->size() - 1;
	for (auto iter = m_currentInfos->rbegin(); iter != m_currentInfos->rend(); ++iter)
	{
		/*若为普通信息或已解决信息，则删除该信息*/
		if (IsCouldRemove(**iter))
		{
			return RemoveRow(index);
		}
		--index;
	}

	return false;
}

int WarningModel::NextToBeSolved() const
{
	return NextToBeSolved(m_allInfos);
}

int WarningModel::NextToBeSolved(ModelMapType map) const
{
	size_t i = 0;
	while (i < map->size() && !IsCouldBeSolved(*map->at(i)))
	{
		++i;
	}

	if (i == map->size())
	{
		return -1;
	}

	return i;
}

void WarningModel::PushFront(std::shared_ptr<WarningInfo> warningInfo)
{
	m_allInfos->push_front(warningInfo);

	switch (m_category)
	{
	case WarningInfo::CATEGORY_ALL:{
		beginInsertRows(QModelIndex(), 0, 0);
		m_currentInfos->push_front(warningInfo);
		endInsertRows();
	}break;
	case WarningInfo::CATEFORY_INFO:
	case WarningInfo::CATEFORY_WARNING:
	case WarningInfo::CATEFORY_ERROR:{
		if (warningInfo->GetCategory()==m_category)
		{
			beginInsertRows(QModelIndex(), 0, 0);
			m_currentInfos->push_front(warningInfo);
			endInsertRows();
		}
	}break;
	default:
		break;
	}
}

void WarningModel::SolveAllAtCurrentCategory()
{
	beginResetModel();
	for (size_t i = 0; i < m_currentInfos->size(); i++)
	{
		if (IsCouldBeSolved(*m_currentInfos->at(i)))
		{
			m_currentInfos->at(i)->SetState(WarningInfo::STATE_SOLVED);
		}
	}
	endResetModel();
}

void WarningModel::SolveRow(int row)
{
	auto iter = std::find(m_currentInfos->begin(), m_currentInfos->end(), m_allInfos->at(row));
	if (iter != m_currentInfos->end())
	{
		SolveRowAtCurrentCategory(iter - m_currentInfos->begin());
		return;
	}

	m_allInfos->at(row)->SetState(WarningInfo::STATE_SOLVED);
}

void WarningModel::SolveRowAtCurrentCategory(int row)
{
	setData(createIndex(row, 1), WarningInfo::STATE_SOLVED);
}

int WarningModel::NextToBeSolvedAtCurrentCategory() const
{
	return NextToBeSolved(m_currentInfos);
}
