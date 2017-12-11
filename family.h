#ifndef FAMILY_H
#define FAMILY_H

#include <QObject>
#include <QMap>
#include <QList>

#include "person.h"
#include "treeleaf.h"


class Family : public QObject
{
	Q_OBJECT
public:
	Family(QObject *parent = nullptr);
	void addPerson(Person * nPers) {	personList.append(nPers);}
	void addLeaf(Person * pers, TreeLeaf * leaf) { leavesMap.insert(pers,leaf);}
	int  size() { return personList.size();}
	Person * getPerson(int num) { return personList[num];}
	TreeLeaf * getLeaf(Person * pers) { return leavesMap[pers];}
	TreeLeaf * getLeaf(int num) { return leavesMap[personList[num]];}


signals:

public slots:

private:
	QList<Person *> personList;
	QMap<Person *, TreeLeaf *> leavesMap;

};

#endif // FAMILY_H
