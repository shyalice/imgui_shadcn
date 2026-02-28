//
// Created by Kai Tears on 27/02/2026.
//

#include "elem/button.hpp"

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

using shadcn::Button;

std::unordered_map< std::string, Button::ButtonState > Button::state;

Button::Button( const std::string& name, const ButtonData& data )
{
    ImGuiWindow* window = GetCurrentWindow( );
    if ( window->SkipItems )
        return;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    const auto imgui_id = window->GetID( name.c_str( ) );

    const ImVec2 pos = window->DC.CursorPos;
    const ImRect total_bb( pos, pos + data.size );
    auto const font = shadcn::g->fonts->get( data.fontVariant );
    auto const text_size = font.calculateSize( name );
    ItemSize( total_bb, style.FramePadding.y );
    if ( !ItemAdd( total_bb, imgui_id ) )
        return;

    bool hovered, held;
    bool pressed = ButtonBehavior( total_bb, imgui_id, &hovered, &held );

    auto& st = state[ name ];

    elem::unfocusWhenInactive( g.IO.MousePos, total_bb, ( elem::DataSkeleton* ) &st );

    if ( pressed && !elem::isInactive( ) )
    {
        if ( data.onClick )
            data.onClick( );

        MarkItemEdited( imgui_id );

        st.focused = true;
    }

    window->DrawList->PushClipRectFullScreen( );

    ImColor bg_idle, bg_pressed, text = { };

    switch ( data.style )
    {
    case ButtonStyle::Primary:
        if ( elem::isInactive( ) )
            bg_idle = colorPalette[ "primary" ].modulate( 0.7f );
        else
            bg_idle = colorPalette[ "primary" ].value;
        bg_pressed = colorPalette[ "primary" ].modulate( 0.8f );
        text = colorPalette[ "text_on_primary" ].value;
        break;

    case ButtonStyle::Secondary:
        bg_idle = colorPalette[ "secondary" ].value;
        bg_pressed = colorPalette[ "secondary" ].modulate( 0.8f );
        text = colorPalette[ "text_on_secondary" ].value;
        break;

    case ButtonStyle::Destructive:
        bg_idle = colorPalette[ "destructive" ].modulate( 0.10f );
        bg_pressed = colorPalette[ "destructive" ].modulate( 0.20f );
        text = colorPalette[ "text_destructive" ].value;
        break;
    }

    st.heldSizeMult = ImLerp( st.heldSizeMult, ( held && !elem::isInactive( ) ) ? 0.9f : 1.f, g.IO.DeltaTime * 20.f );
    st.heldOffset = ImLerp( st.heldOffset, ( held && !elem::isInactive( ) ) ? ImVec2( 2, 2 ) : ImVec2( 0, 0 ), g.IO.DeltaTime * 20.f );

    st.background = ImLerp( st.background, !pressed ? bg_idle.Value : bg_pressed.Value, g.IO.DeltaTime * 20.f );
    st.border = ImLerp( st.border, st.focused ? colorPalette[ "ring" ].value : colorPalette[ "ring" ].modulate( 0 ).Value, g.IO.DeltaTime * 20.f );
    st.focus = ImLerp( st.focus, st.focused ? colorPalette[ "ring" ].modulate( 0.5f * style.Alpha ).Value : colorPalette[ "ring" ].modulate( 0 ).Value, g.IO.DeltaTime * 20.f );

    // window->DrawList->AddRect( total_bb.Min - ImVec2( 1, 1 ), total_bb.Max + ImVec2( 1, 1 ), Color( st.focus ).modulate( ), 4, 0, 4 );

    window->DrawList->AddRectFilled( total_bb.Min + st.heldOffset, total_bb.Max - st.heldOffset, Color( st.background ).modulate( ), data.rounding );

    window->DrawList->AddText( font.data.first, static_cast< float >( font.data.second ) * st.heldSizeMult, total_bb.GetCenter( ) - ( text_size * st.heldSizeMult ) / 2, Color( text ).modulate( ), name.c_str( ) );

    window->DrawList->PopClipRect( );
}

Button::~Button( ) = default;