#ifndef SANGUIS_MESSAGES_SERIALIZATION_READER_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_READER_HPP_INCLUDED

#include "istream.hpp"
#include "../auto_ptr.hpp"

namespace sanguis
{
namespace messages
{
namespace serialization
{

struct reader {
	explicit reader(
		istream &);

	template<
		typename Msg
	>
	auto_ptr operator()() const;
private:
	istream &is;
};

}
}
}

#endif
