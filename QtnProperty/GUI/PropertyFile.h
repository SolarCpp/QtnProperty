
#pragma once

#include <QtnProperty/PropertyCore.h>
#include <QtnProperty/PropertyGUI.h>
#include <QFileDialog>
#include <QColor>

class QtnPropertyFile : public QtnPropertyQString {
public:
	QtnPropertyFile() {
		QtnPropertyDelegateInfo info;
		info.name = "SelectFile";
		info.attributes["fileMode"] = QFileDialog::AnyFile;
		info.attributes["invalidColor"] = QColor(Qt::blue);
		this->setDelegateInfo(info);
	}
};