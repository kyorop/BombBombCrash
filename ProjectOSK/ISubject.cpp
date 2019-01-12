#include "ISubject.h"

void SubjectImplementation::AddObserver(const std::shared_ptr<IObserver>& new_observer)
{
	observers_.push_back(new_observer);
}

void SubjectImplementation::DeleteObserver(const std::shared_ptr<IObserver>& delete_observer)
{
	auto itr = find(std::begin(observers_), end(observers_), delete_observer);
	observers_.erase(itr);
}

void SubjectImplementation::Notify()
{
	for (auto& observer : observers_)
		observer->Update();
}