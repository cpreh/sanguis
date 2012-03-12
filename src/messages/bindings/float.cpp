#include <sanguis/messages/bindings/float.hpp>
#include <alda/bindings/fundamental.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/cstdint.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>

namespace
{

typedef boost::uint32_t fixed_int;

typedef sanguis::messages::bindings::float_::type float_type;

typedef alda::bindings::fundamental<
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
	float_type const _val
)
{
	return
		static_cast<
			fixed_int
		>(
			std::log(
				_val
				+
				static_cast<
					float_type
				>(
					1
				)
			)
			* exp
		);
}

float_type
unmake_fixed(
	fixed_int const _val
)
{
	return
		std::exp(
			static_cast<
				float_type
			>(
				_val
			)
			/ exp
		)
		- static_cast<
			float_type
		>(
			1
		);
}

fixed_int
serialize(
	float_type const _val
)
{
	return
		_val < 0
		?
			make_fixed(
				_val
			)
			| sign_bit
		:
			make_fixed(
				_val
			)
			& ~sign_bit;
}

float_type
deserialize(
	fixed_int _val
)
{
	bool const is_signed(
		_val & sign_bit
	);

	_val &= ~sign_bit;

	return
		is_signed
		?
			unmake_fixed(
				_val
			)
			* static_cast<
				float_type
			>(
				-1
			)
		:
			unmake_fixed(
				_val
			);
}

}

majutsu::size_type
sanguis::messages::bindings::needed_size(
	majutsu::concepts::dynamic_memory::tag const *,
	float_ const *,
	float_::type const &
)
{
	return sizeof(fixed_int);
}

void
sanguis::messages::bindings::place(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	float_ const *,
	float_::type const &_val,
	majutsu::raw_pointer const _mem
)
{
	place(
		_tag,
		static_cast<
			adapted const *
		>(0),
		serialize(
			_val
		),
		_mem
	);
}

sanguis::messages::bindings::float_::type
sanguis::messages::bindings::make(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	float_ const *,
	majutsu::const_raw_pointer const _beg
)
{
	return
		deserialize(
			make(
				_tag,
				static_cast<
					adapted const *
				>(0),
				_beg
			)
		);
}
