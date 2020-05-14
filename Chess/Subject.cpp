#include "pch.h"
#include "Subject.h"
#include "IObserver.h"

void Subject::attach(IObserver& observer)
{
	m_Observers.push_back(&observer);
}

void Subject::notify(const InputEvent& event) const
{
	for (const auto& observer : m_Observers)
		observer->update(event);
}
