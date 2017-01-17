#include "stdafx.h"
#include "ConfirmButton.h"
#include "QIcon"



ConfirmButton::ConfirmButton(QWidget* parent /*= nullptr*/)
	:Button(parent)
{
	setIcon(QIcon(QPixmap(":/new/image/Resources/Image/confirm_icon.png")));
}
