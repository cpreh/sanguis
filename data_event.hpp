#ifndef SANGUIS_DATA_EVENT_HPP_INCLUDED
#define SANGUIS_DATA_EVENT_HPP_INCLUDED

#include <boost/statechart/event.hpp>

namespace sanguis
{
template<typename T>
struct data_event : public boost::statechart::event< data_event<T> >
{
	T data;
	data_event(const T &data) : data(data) {}
};
}

#endif
