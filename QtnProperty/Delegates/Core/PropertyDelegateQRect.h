/*******************************************************************************
Copyright 2012-2015 Alex Zhondin <qtinuum.team@gmail.com>
Copyright 2015-2017 Alexandra Cherdantseva <neluhus.vagus@gmail.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#ifndef PROPERTY_DELEGATE_QRECT_H
#define PROPERTY_DELEGATE_QRECT_H

#include "QtnProperty/Delegates/PropertyDelegate.h"

class QtnPropertyQRectBase;

class QTN_IMPORT_EXPORT QtnPropertyDelegateQRect
	: public QtnPropertyDelegateTypedEx<QtnPropertyQRectBase>
{
	Q_DISABLE_COPY(QtnPropertyDelegateQRect)

	bool coordinates;

public:
	QtnPropertyDelegateQRect(QtnPropertyQRectBase &owner);

	static bool Register();

protected:
	virtual QWidget *createValueEditorImpl(QWidget *parent, const QRect &rect,
		QtnInplaceInfo *inplaceInfo = nullptr) override;

	virtual bool propertyValueToStr(QString &strValue) const override;
};

#endif // PROPERTY_DELEGATE_QRECT_H
