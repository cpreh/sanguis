#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_BASE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_BASE_HPP_INCLUDED

#include <sanguis/messages/serialization/dispatcher_base_fwd.hpp>
#include <sanguis/messages/serialization/reader_fwd.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

class dispatcher_base
{
	FCPPT_NONCOPYABLE(
		dispatcher_base
	);
protected:
	dispatcher_base();
public:
	virtual messages::auto_ptr
	on_dispatch(
		serialization::reader const &
	) const = 0;

	virtual ~dispatcher_base() = 0;
};

}
}
}

#endif
