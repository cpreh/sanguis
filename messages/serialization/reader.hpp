#ifndef SANGUIS_MESSAGES_SERIALIZATION_READER_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_READER_HPP_INCLUDED

#include "reader_fwd.hpp"
#include "istream.hpp"
#include "../auto_ptr.hpp"
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

class reader
{
	FCPPT_NONASSIGNABLE(
		reader
	)
public:
	explicit reader(
		istream &
	);

	template<
		typename Msg
	>
	auto_ptr operator()() const;
private:
	istream &is_;
};

}
}
}

#endif
