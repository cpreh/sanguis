#ifndef SANGUIS_MESSAGES_CONCRETE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONCRETE_HPP_INCLUDED

#include "base.hpp"

namespace sanguis
{
namespace messages
{

template<
	typename T
>
class concrete
:
	public base
{
public:
	explicit concrete(
		T const &
	);
	
	T const &
	value() const;
private:
	types::message::type
	type() const;

	majutsu::const_raw_pointer
	data() const;

	majutsu::size_type
	size() const;

	T value_;
};

}
}

#endif
