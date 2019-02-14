
#pragma once

#include <QtnProperty/PropertyCore.h>

class QtnPropertyGroup : public QtnPropertySet {
public:
	QtnPropertyGroup(QObject * parent = nullptr) 
		: QtnPropertySet(parent) {
		;
	}

	virtual QtnPropertyBase *clone(QObject *parent) override
	{
		return createCopyImpl(parent);
	}

protected:
	// cloning implementation
	virtual QtnPropertyGroup *createNewImpl(QObject *parentForNew) const {
		return createCopyImpl(parentForNew);
	}

	//deep copy
	virtual QtnPropertyGroup *createCopyImpl(QObject *parentForCopy) const {
		auto chs = this->childProperties();
		auto g = new QtnPropertyGroup();
		g->clonePropertyFrome(*this);
		for (auto c : chs) {
			g->addChildProperty(c->clone(nullptr), true);
		}
		return g;
	}

	QtnPropertyGroup & operator=(const QtnPropertyGroup & group) {
		auto in = group.childProperties();
		auto me = this->childProperties();
		Q_ASSERT(in.size() == me.size());
		for (int i = 0; i < in.size(); i++) {
			QString str;
			in.at(i)->toStr(str);
			me.at(i)->fromStr(str, false);
		}
		return *this;
	}

	// copy values
	virtual bool copyValuesImpl(
		QtnPropertySet *propertySetCopyFrom, QtnPropertyState ignoreMask) {
		auto in = propertySetCopyFrom->childProperties();
		auto me = this->childProperties();
		Q_ASSERT(in.size() == me.size());
		for (int i = 0; i < in.size(); i++) {
			if (!(in.at(i)->state() & ignoreMask)) {
				QVariant str;
				in.at(i)->toVariant(str);
				me.at(i)->fromVariant(str, false);
				//QByteArray data;
				//QDataStream out(&data, QIODevice::WriteOnly);
				//in.at(i)->save(out);
				//me.at(i)->load(QDataStream(data));
			}
		}
		return true;
	}
};