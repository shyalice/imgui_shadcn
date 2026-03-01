//
// Created by Kai Tears on 01/03/2026.
//

#include "elem/toggle.hpp"

#include "imgui.h"
#include "imgui_internal.h"
#include "shadcn.hpp"
#include "color/color.hpp"
#include "elem/elem.hpp"
#include "styles/styles.hpp"

#include <iostream>
#include <ostream>

using namespace ImGui;

using shadcn::Toggle;

std::unordered_map< std::string, Toggle::ToggleState > Toggle::state;

Toggle::Toggle( const std::string& id, bool* v, const ToggleData& data )
{
    ImGuiWindow* window = GetCurrentWindow( );
    if ( window->SkipItems )
        return;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    const auto imgui_id = window->GetID( id.c_str( ) );

    const ImVec2 pos = window->DC.CursorPos;
    const ImRect total_bb( pos, pos + data.size );
    ItemSize( total_bb, 0 );
    if ( !ItemAdd( total_bb, imgui_id ) )
        return;

    bool hovered, held;
    bool pressed = ButtonBehavior( total_bb, imgui_id, &hovered, &held );

    auto& st = state[ id ];

    elem::unfocusWhenInactive( g.IO.MousePos, total_bb, ( elem::DataSkeleton* ) &st );

    // FIXME: make it better?
    if ( data.forwardFocus )
    {
        if ( *data.forwardFocus )
        {
            st.focused = true;
            *data.forwardFocus = false;
        }
    }

    auto const inactive = elem::isInactive( );

    if ( pressed && !inactive )
    {
        if ( data.onClick )
            data.onClick( );

        MarkItemEdited( imgui_id );

        st.focused = true;

        *v = !*v;
    }

    ImColor bg, border, focus = { };

    switch ( data.style )
    {
    case ToggleStyle::Primary:
        bg = !( *v ) ? colorPalette[ "background" ].value : ( inactive ? colorPalette[ "primary" ].modulate( 0.7f * style.Alpha ).Value : colorPalette[ "primary" ].value );
        border = !( *v ) ? ( st.focused ? colorPalette[ "ring" ].value : colorPalette[ "border" ].value ) : colorPalette[ "border" ].modulate( 0 ).Value;
        focus = st.focused ? colorPalette[ "ring" ].modulate( 0.5f * style.Alpha ).Value : colorPalette[ "ring" ].modulate( 0 ).Value;
        break;
    case ToggleStyle::Destructive:
        bg = !( *v ) ? colorPalette[ "destructive" ].modulate( 0.05f * style.Alpha ).Value : ( inactive ? colorPalette[ "destructive" ].modulate( 0.7f * style.Alpha ).Value : colorPalette[ "destructive" ].value );
        border = !( *v ) ? ( st.focused ? colorPalette[ "ring_destructive" ].value : colorPalette[ "destructive" ].modulate( 0.1f * style.Alpha ).Value ) : colorPalette[ "destructive" ].modulate( 0 ).Value;
        focus = st.focused ? colorPalette[ "ring_destructive" ].modulate( 0.5f * style.Alpha ).Value : colorPalette[ "ring_destructive" ].modulate( 0 ).Value;
        break;
    default:
        break;
    }

    //window->DrawList->PushClipRectFullScreen( );

    st.heldOffset = shadcn::g->styles->global.useAdvancedAnimations ? ImLerp( st.heldOffset, ( held && !inactive ) ? ImVec2( 2, 2 ) : ImVec2( 0, 0 ), g.IO.DeltaTime * 20.f ) : ImVec2( 0, 0 );

    st.background = ImLerp( st.background, bg, g.IO.DeltaTime * 20.f );
    st.border = ImLerp( st.border, border, g.IO.DeltaTime * 20.f );
    st.pill = ImLerp( st.pill, !( *v ) ? st.border : colorPalette[ "primary_foreground" ].value, g.IO.DeltaTime * 20.f );
    st.focus = ImLerp( st.focus, focus, g.IO.DeltaTime * 20.f );

    window->DrawList->AddRect( total_bb.Min - ImVec2( 1, 1 ) + st.heldOffset, total_bb.Max + ImVec2( 1, 1 ) - st.heldOffset, Color( st.focus ).modulate( ), 999, 0, 4 );

    window->DrawList->AddRectFilled( total_bb.Min + st.heldOffset, total_bb.Max - st.heldOffset, Color( st.background ).modulate( ), 999 );
    window->DrawList->AddRect( total_bb.Min + st.heldOffset, total_bb.Max - st.heldOffset, Color( st.border ).modulate( ), 999 );

    st.radius = ImLerp( st.radius, !(*v) ? 1.f : 0.f, g.IO.DeltaTime * 20.f );

    auto const radius = (total_bb.GetHeight( ) / 2 - 2 - st.radius) - st.heldOffset.y;
    auto const padding = 2 + radius + st.radius + st.heldOffset.y;

    st.offset = ImLerp( st.offset, *v ? total_bb.GetWidth( ) - padding * 2 : 0, g.IO.DeltaTime * 20.f );

    window->DrawList->AddCircleFilled( total_bb.Min + ImVec2( padding + st.offset, padding ), radius, Color( st.pill ).modulate( ), 66 );

    //window->DrawList->PopClipRect( );
}

Toggle::~Toggle( ) = default;