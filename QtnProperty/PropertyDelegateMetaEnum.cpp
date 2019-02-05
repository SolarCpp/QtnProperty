#include "PropertyDelegateMetaEnum.h"

#include "Delegates/PropertyEditorHandler.h"
#include "Property.h"

#include <QCoreApplication>
#include <QComboBox>
#include <QLineEdit>

class QtnPropertyDelegateMetaEnum::EditorHandler
	: public QtnPropertyEditorHandlerBase
{
	QtnPropertyDelegateMetaEnum *mOwner;

public:
	EditorHandler(QtnPropertyDelegateMetaEnum *owner, QComboBox &editor);

	QComboBox &comboBox() const;

protected:
	virtual void updateEditor() override;
	void updateValue(int value);

private:
	void onCurrentIndexChanged(int index);

	unsigned updating;
};

QtnPropertyDelegateMetaEnum::QtnPropertyDelegateMetaEnum(
	const QMetaEnum &metaEnum, QtnProperty *property)
	: QtnPropertyDelegate(property)
	, mMetaEnum(metaEnum)
{
}

int QtnPropertyDelegateMetaEnum::currentValue() const
{
	QVariant v;
	ownerProperty->toVariant(v);
	qint64 value = v.toLongLong();
	if (value < std::numeric_limits<int>::min())
		return std::numeric_limits<int>::min();

	if (value > std::numeric_limits<int>::max())
		return std::numeric_limits<int>::max();

	return int(value);
}

bool QtnPropertyDelegateMetaEnum::propertyValueToStr(QString &strValue) const
{
	strValue = valueToStr(currentValue());
	return !strValue.isNull();
}

QString QtnPropertyDelegateMetaEnum::valueToStr(int value) const
{
	auto key = mMetaEnum.valueToKey(value);
	if (!key)
		return QString();

	return keyToStr(key);
}

QString QtnPropertyDelegateMetaEnum::keyToStr(const char *key) const
{
	return QCoreApplication::translate(mMetaEnum.scope(), key);
}

QWidget *QtnPropertyDelegateMetaEnum::createValueEditorImpl(
	QWidget *parent, const QRect &rect, QtnInplaceInfo *inplaceInfo)
{
	if (ownerProperty->isEditableByUser())
	{
		QComboBox *combo = new QComboBox(parent);
		for (int i = 0, count = mMetaEnum.keyCount(); i < count; i++)
		{
			combo->addItem(
				keyToStr(mMetaEnum.key(i)), QVariant(mMetaEnum.value(i)));
		}

		combo->setGeometry(rect);

		new EditorHandler(this, *combo);

		if (inplaceInfo)
			combo->showPopup();

		return combo;
	}

	return createValueEditorLineEdit(parent, rect, true, inplaceInfo);
}

QtnPropertyDelegateMetaEnum::EditorHandler::EditorHandler(
	QtnPropertyDelegateMetaEnum *owner, QComboBox &editor)
	: QtnPropertyEditorHandlerBase(*owner->ownerProperty, editor)
	, mOwner(owner)
	, updating(0)
{
	updateEditor();

	QObject::connect(&editor,
		static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
		this, &EditorHandler::onCurrentIndexChanged);
}

QComboBox &QtnPropertyDelegateMetaEnum::EditorHandler::comboBox() const
{
	return *static_cast<QComboBox *>(m_editor);
}

void QtnPropertyDelegateMetaEnum::EditorHandler::updateEditor()
{
	++updating;

	if (m_property->valueIsHidden())
		comboBox().setCurrentIndex(-1);
	else
	{
		int index = comboBox().findData(mOwner->currentValue());

		if (index >= 0)
			comboBox().setCurrentIndex(index);
	}

	--updating;
}

void QtnPropertyDelegateMetaEnum::EditorHandler::updateValue(int value)
{
	if (updating > 0)
		return;

	if (m_property)
		m_property->fromVariant(value, true);
}

void QtnPropertyDelegateMetaEnum::EditorHandler::onCurrentIndexChanged(
	int index)
{
	if (index < 0)
		return;

	QVariant data = comboBox().itemData(index);

	if (data.canConvert<int>())
		updateValue(data.toInt());
}