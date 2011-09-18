#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_HPP_INCLUDED

#include <sanguis/messages/serialization/reader_fwd.hpp>
#include <sanguis/messages/serialization/dispatcher_base.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

template<
	typename T
>
class dispatcher
:
	public serialization::dispatcher_base
{
	FCPPT_NONCOPYABLE(
		dispatcher
	);
public:
	dispatcher();

	~dispatcher();

	messages::auto_ptr
	on_dispatch(
		serialization::reader const &
	) const;
};

}
}
}

#endif
