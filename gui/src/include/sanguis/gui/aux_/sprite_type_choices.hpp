#ifndef SANGUIS_GUI_AUX__SPRITE_TYPE_CHOICES_HPP_INCLUDED
#define SANGUIS_GUI_AUX__SPRITE_TYPE_CHOICES_HPP_INCLUDED

#include <sge/rucksack/scalar.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/type_choices.hpp>


namespace sanguis
{
namespace gui
{
namespace aux_
{

typedef
sge::sprite::config::type_choices<
	sge::sprite::config::unit_type<
		sge::rucksack::scalar
	>,
	sge::sprite::config::float_type<
		float // don't use
	>
>
sprite_type_choices;

}
}
}

#endif
