
#pragma once

#include <QtnProperty/PropertyCore.h>
#include <QtnProperty/PropertyGUI.h>
#include <QFileDialog>
#include <QColor>

class QtnPropertyFolder : public QtnPropertyQString {
public:
	QtnPropertyFolder() {
		QtnPropertyDelegateInfo info;
		info.name = "SelectFile";
		info.attributes["fileMode"] = QFileDialog::DirectoryOnly;
		info.attributes["invalidColor"] = QColor(Qt::blue);
		this->setDelegateInfo(info);
	}
};