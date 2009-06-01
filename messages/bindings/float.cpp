#include "float.hpp"
#include "pod.hpp"
#include <boost/cstdint.hpp>
#include <cmath>

namespace
{

typedef boost::uint32_t fixed_int;
typedef sanguis::messages::bindings::float_::type float_type;

typedef sanguis::messages::bindings::pod<
	fixed_int
> adapted;

fixed_int const sign_bit(
	0x1
);

float_type const exp(
	static_cast<
		float_type
	>(
		1 << 16
	)
);

fixed_int
make_fixed(
	float_type const f)
{
	return static_cast<fixed_int>(
		std::log(
			f + static_cast<float_type>(1)
		) * exp
	);
}

float_type
unmake_fixed(
	fixed_int const i)
{
	return std::exp(
		static_cast<float_type>(i) / exp
	) - static_cast<float_type>(1);
}

fixed_int
serialize(
	float_type const f)
{
	return f < 0
		? make_fixed(-f) | sign_bit
		: make_fixed(f) & ~sign_bit;
}

float_type
deserialize(
	fixed_int c)
{
	bool const is_signed = c & sign_bit;
	c &= ~sign_bit;

	return is_signed
		? unmake_fixed(c) * static_cast<float_type>(-1)
		: unmake_fixed(c);
}

}

majutsu::size_type
sanguis::messages::bindings::float_::needed_size(
	type const &)
{
	return sizeof(fixed_int);
}

void
sanguis::messages::bindings::float_::place(
	type const &t,
	majutsu::raw_pointer const mem)
{
	adapted::place(
		serialize(t),
		mem
	);
}

sanguis::messages::bindings::float_::type
sanguis::messages::bindings::float_::make(
	majutsu::const_raw_pointer const beg)
{
	return deserialize(
		adapted::make(
			beg
		)
	);
}
