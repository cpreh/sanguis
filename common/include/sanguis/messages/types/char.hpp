#ifndef SANGUIS_MESSAGES_TYPES_CHAR_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_CHAR_HPP_INCLUDED

#include <sge/charconv/char_type.hpp>
#include <sge/charconv/encoding.hpp>


namespace sanguis::messages::types
{

using
char_
=
sge::charconv::char_type<
	sge::charconv::encoding::utf8
>;

}

#endif
