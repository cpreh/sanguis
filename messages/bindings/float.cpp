#include "float.hpp"
#include "pod.hpp"
#include <sge/math/compare.hpp>
#include <boost/cstdint.hpp>
#include <cmath>

namespace
{

typedef boost::int32_t fixed_int;
typedef sanguis::messages::bindings::float_::type float_type;

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
	return static_cast<fixed_int>(std::log(f) * exp);
}

fixed_int
serialize(
	float_type const f)
{
	if(sge::math::almost_zero(f))
		return 0;
	
	return f < 0
		? make_fixed(-f) | sign_bit
		: make_fixed(f) & ~sign_bit;
}

float_type
deserialize(
	fixed_int c)
{
	if(c == 0)
		return 0;
	
	bool const is_signed = c & sign_bit;
	c &= ~sign_bit;

	return
		std::exp(static_cast<float_type>(c) / exp)
		* (is_signed
		? static_cast<float_type>(-1)
		: static_cast<float_type>(1));
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
	fixed_int const fi = serialize(t);

	pod<fixed_int>::place(
		fi,
		mem
	);
}

sanguis::messages::bindings::float_::type
sanguis::messages::bindings::float_::make(
	majutsu::const_raw_pointer const beg,
	majutsu::size_type const sz)
{
	fixed_int const fi = pod<fixed_int>::make(
		beg,
		sz
	);

	return deserialize(fi);
}
