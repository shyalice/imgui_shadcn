//
// Created by Kai Tears on 01/03/2026.
//

#include "elem/card.hpp"

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

using shadcn::Card;

Card::Card( const std::string& name, const ImVec2& size, const std::optional< CardData >& data )
{
    auto const card_data = data.value_or( CardData { } );

    PushStyleVar( ImGuiStyleVar_WindowPadding, card_data.padding );

    BeginChild( name.c_str( ), size, 0, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysUseWindowPadding );
    auto* window = GetCurrentWindow( );
    auto const style = GetStyle( );

    window->DrawList->PushClipRectFullScreen( );

    window->DrawList->AddRectFilled( window->Pos, window->Pos + window->Size, colorPalette[ "background" ].modulate( ), card_data.rounding );

    if ( card_data.backgroundStyle.has_value( ) )
    {
        switch ( card_data.backgroundStyle.value( ) )
        {
        case CardBackgroundStyle::Muted:
            window->DrawList->AddRectFilled( window->Pos, window->Pos + window->Size, colorPalette[ "muted" ].modulate( 0.3f * style.Alpha ), card_data.rounding );
        case CardBackgroundStyle::Standard:
            window->DrawList->AddRectFilled( window->Pos, window->Pos + window->Size, colorPalette[ "card" ].modulate( ), card_data.rounding );
        default:
            break;
        }
    }

    window->DrawList->AddRect( window->Pos, window->Pos + window->Size, colorPalette[ "border" ].modulate( ), card_data.rounding );

    window->DrawList->PopClipRect( );

    PopStyleVar( );
}

void Card::end( )
{
    EndChild( );
}

Card::~Card( ) = default;
