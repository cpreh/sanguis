#ifndef SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED

#include "../serialization/endianness.hpp"
#include <fcppt/endianness/copy_n_from_host.hpp>
#include <fcppt/endianness/copy_n_to_host.hpp>
#include <fcppt/truncation_check_cast.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/raw_pointer.hpp>
#include <boost/cstdint.hpp>
#include <boost/foreach.hpp>

namespace sanguis
{
namespace messages
{
namespace bindings
{

template<
	typename Type,
	typename Adapted
>
struct dynamic_len {
	typedef Type type;

	typedef boost::uint16_t length_type;
};

template<
	typename Type,
	typename Adapted
>
majutsu::size_type
needed_size(
	majutsu::concepts::dynamic_memory::tag const *const tag_,
	dynamic_len<
		Type,
		Adapted
	> const *,
	Type const &value_
)
{
	majutsu::size_type ret(
		sizeof(
			typename dynamic_len<
				Type,
				Adapted
			>::length_type
		)
	);

	BOOST_FOREACH(
		typename Type::const_reference elem,
		value_
	)
		ret +=
			needed_size(
				tag_,
				static_cast<
					Adapted const *
				>(0),
				elem
			);

	return ret;
}

template<
	typename Type,
	typename Adapted
>
void
place(
	majutsu::concepts::dynamic_memory::tag const *const tag_,
	dynamic_len<
		Type,
		Adapted
	> const *const concept_,
	Type const &value_,
	majutsu::raw_pointer mem
)
{
	typedef typename dynamic_len<
		Type,
		Adapted
	>::length_type length_type;

	length_type const sz(
		fcppt::truncation_check_cast<
			length_type
		>(
			needed_size(
				tag_,
				concept_,
				value_
			)
		)
	);

	fcppt::endianness::copy_n_from_host(
		reinterpret_cast<
			majutsu::const_raw_pointer
		>(
			&sz
		),
		sizeof(length_type),
		mem,
		sizeof(length_type),
		sanguis::messages::serialization::endianness()
	);

	mem += sizeof(length_type);
	
	for(
		typename Type::const_iterator it(
			value_.begin()
		);
		it != value_.end();
		mem +=
			needed_size(
				tag_,
				static_cast<
					Adapted const *
				>(0),
				*it
			),
		++it
	)
		place(
			tag_,
			static_cast<
				Adapted const *
			>(0),
			*it,
			mem
		);
}

template<
	typename Type,
	typename Adapted
>
Type 
make(
	majutsu::concepts::dynamic_memory::tag const *const tag_,
	dynamic_len<
		Type,
		Adapted
	> const *,
	majutsu::const_raw_pointer const mem
)
{
	typedef typename dynamic_len<
		Type,
		Adapted
	>::length_type length_type;

	length_type my_size;
		
	fcppt::endianness::copy_n_to_host(
		mem,
		sizeof(length_type),
		reinterpret_cast<
			majutsu::raw_pointer
		>(
			&my_size
		),
		sizeof(length_type),
		sanguis::messages::serialization::endianness()
	);
		
	Type ret;

	for(
		majutsu::const_raw_pointer cur_mem(
			mem + sizeof(length_type)
		);
		cur_mem != mem + my_size;
	)
	{
		typename Type::value_type elem(
			make(
				tag_,
				static_cast<
					Adapted const *
				>(0),
				cur_mem
			)
		);

		ret.push_back(
			elem
		);

		cur_mem +=
			needed_size(
				tag_,
				static_cast<
					Adapted const *
				>(0),
				elem
			);
	}

	return ret;
}

}
}
}

#endif
