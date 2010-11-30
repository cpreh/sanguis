#ifndef SANGUIS_MESSAGES_SERIALIZATION_READ_ELEMENT_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_READ_ELEMENT_HPP_INCLUDED

#include "istream.hpp"
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

template<
	typename Class
>
class read_element
{
	FCPPT_NONASSIGNABLE(
		read_element
	)
public:
	read_element(
		std::istream &,
		Class &
	);

	template<
		typename Role
	>
	void
	operator()(
		Role &
	) const;
private:
	istream &is_;

	Class &obj_;
};

}
}
}

#endif
