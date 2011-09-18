#include <sanguis/messages/serialization/reader.hpp>

sanguis::messages::serialization::reader::reader(
	istream &_is
)
:
	is_(_is)
{}
