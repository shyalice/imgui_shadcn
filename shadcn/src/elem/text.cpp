//
// Created by Kai Tears on 28/02/2026.
//

#include "elem/text.hpp"

#include "imgui.h"
#include "imgui_internal.h"
#include "shadcn.hpp"
#include "color/color.hpp"
#include "elem/elem.hpp"
#include "fonts/fonts.hpp"
#include "styles/styles.hpp"

#include <iostream>
#include <ostream>

using namespace ImGui;

using shadcn::Text;

Text::Text( const std::string& value, const TextData& data )
{
    auto const inactive = elem::isInactive( );

    PushFont( g->fonts->get( data.fontVariant ).data.first );
    TextColored( inactive ? colorPalette[ data.color ].modulate( 0.7f * GetStyle( ).Alpha ).Value : colorPalette[ data.color ].modulate( ).Value, "%s", value.c_str( ) );
    PopFont( );

    if ( IsItemClicked( ) && data.onClick && !inactive )
        data.onClick( );
}

Text::~Text( ) = default;