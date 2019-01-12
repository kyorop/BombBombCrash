#pragma once
#include "IObserver.h"

class ISubject
{
public:
	virtual ~ISubject() = default;
	virtual void AddObserver(const std::shared_ptr<IObserver>& observer) = 0;
	virtual void DeleteObserver(const std::shared_ptr<IObserver>& observer) = 0;
	virtual void Notify() = 0;
};


class SubjectImplementation
{
	std::list<std::shared_ptr<IObserver>> observers_;
public:
	void AddObserver(const std::shared_ptr<IObserver>& new_observer);

	void DeleteObserver(const std::shared_ptr<IObserver>& delete_observer);

	void Notify();
};