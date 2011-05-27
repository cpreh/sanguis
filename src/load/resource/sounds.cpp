#include "sounds.hpp"
#include "map_get_or_create.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include "../../media_path.hpp"
#include <sge/audio/player.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/bad_sound_alloc.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>

sanguis::load::resource::sounds::sounds(
	sge::audio::multi_loader &_ml,
	sge::audio::player &_player
)
:
	ml_(_ml),
	player_(_player)
{
}

sanguis::load::resource::sounds::~sounds()
{
}

sge::audio::file_ptr const
sanguis::load::resource::sounds::load(
	resource::sound_identifier const &_name
) const
{
	return
		resource::map_get_or_create(
			sounds_,
			_name, 
			std::tr1::bind(
				&sounds::do_load,
				this,
				std::tr1::placeholders::_1
			)
		);
}

sge::audio::file_ptr const
sanguis::load::resource::sounds::load_uncached(
	fcppt::filesystem::path const &_path
) const
{
	return
		ml_.load(
			_path
		);
}

sge::audio::sound::base_ptr const
sanguis::load::resource::sounds::make(
	sge::audio::file_ptr const _file,
	sound_type::type const _type
) const
{
	return
		this->make_impl<
			sge::audio::sound::base_ptr
		>(
			_file,
			_type,
			std::tr1::bind(
				&sge::audio::player::create_nonpositional_stream,
				&player_,
				std::tr1::placeholders::_1
			),
			std::tr1::bind(
				&sge::audio::buffer::create_nonpositional,
				std::tr1::placeholders::_1
			)
		);
}

sge::audio::sound::positional_ptr const
sanguis::load::resource::sounds::make_positional(
	sge::audio::file_ptr const _file,
	sge::audio::sound::positional_parameters const &_params,
	sound_type::type const _type
) const
{
	return
		this->make_impl<
			sge::audio::sound::positional_ptr
		>(
			_file,
			_type,
			std::tr1::bind(
				&sge::audio::player::create_positional_stream,
				&player_,
				std::tr1::placeholders::_1,
				_params
			),
			std::tr1::bind(
				&sge::audio::buffer::create_positional,
				std::tr1::placeholders::_1,
				_params
			)
		);
}

template<
	typename Ret
>
Ret const
sanguis::load::resource::sounds::make_impl(
	sge::audio::file_ptr const _file,
	sound_type::type const _type,
	fcppt::function::object<
		Ret (sge::audio::file_ptr)
	> const &_make_normal,
	fcppt::function::object<
		Ret (sge::audio::buffer *)
	> const &_make_buffer
) const
try
{
	switch(
		_type
	) 
	{
	case sanguis::load::sound_type::stream:
		return
			_make_normal(
				_file
			);
	case sanguis::load::sound_type::nonstream:
		return
			_make_buffer(
				resource::map_get_or_create(
					buffers_,
					_file,
					boost::phoenix::bind(
						&sge::audio::player::create_buffer,
						&player_,
						*boost::phoenix::arg_names::arg1
					)
				).get()
			);
	}

	throw sanguis::exception(
		FCPPT_TEXT("Invalid sound type in load!")
	);
}
catch(
	sge::audio::bad_sound_alloc const &_error
)
{
	FCPPT_LOG_WARNING(
		sanguis::load::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Allocation of a sound failed! ")
			<< _error.string()
	);

	return Ret();
}

sge::audio::file_ptr const
sanguis::load::resource::sounds::do_load(
	resource::sound_identifier const &_name
) const
{
	return
		ml_.load(
			sanguis::media_path()
			/ FCPPT_TEXT("sound")
			/ _name
		);
}
