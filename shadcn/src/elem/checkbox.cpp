//
// Created by Kai Tears on 27/02/2026.
//

#include "elem/checkbox.hpp"

#include "imgui.h"
#include "imgui_internal.h"
#include "shadcn.hpp"
#include "color/color.hpp"
#include "elem/elem.hpp"
#include "styles/styles.hpp"

#include <iostream>
#include <ostream>

using namespace ImGui;

using shadcn::Checkbox;

std::unordered_map< std::string, Checkbox::CheckboxState > Checkbox::state;

Checkbox::Checkbox( const std::string& id, bool* v, const CheckboxData& data )
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
    case CheckboxStyle::Primary:
        bg = !( *v ) ? colorPalette[ "background" ].value : ( inactive ? colorPalette[ "primary" ].modulate( 0.7f * style.Alpha ).Value : colorPalette[ "primary" ].value );
        border = !( *v ) ? ( st.focused ? colorPalette[ "ring" ].value : colorPalette[ "border" ].value ) : colorPalette[ "border" ].modulate( 0 ).Value;
        focus = st.focused ? colorPalette[ "ring" ].modulate( 0.5f * style.Alpha ).Value : colorPalette[ "ring" ].modulate( 0 ).Value;
        break;
    case CheckboxStyle::Destructive:
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
    st.mark = ImLerp( st.mark, !( *v ) ? colorPalette[ "primary_foreground" ].modulate( 0 ).Value : colorPalette[ "primary_foreground" ].value, g.IO.DeltaTime * 20.f );
    st.focus = ImLerp( st.focus, focus, g.IO.DeltaTime * 20.f );

    window->DrawList->AddRect( total_bb.Min - ImVec2( 1, 1 ) + st.heldOffset, total_bb.Max + ImVec2( 1, 1 ) - st.heldOffset, Color( st.focus ).modulate( ), 4, 0, 4 );

    window->DrawList->AddRectFilled( total_bb.Min + st.heldOffset, total_bb.Max - st.heldOffset, Color( st.background ).modulate( ), 4 );
    window->DrawList->AddRect( total_bb.Min + st.heldOffset, total_bb.Max - st.heldOffset, Color( st.border ).modulate( ), 4 );

    // const float pad = ImMax( 1.0f, IM_TRUNC( ( data.size.y - st.heldOffset.y ) / 5.0f ) );
    // RenderCheckMark( window->DrawList, total_bb.Min + ImVec2( pad, pad ) + st.heldOffset, Color( st.mark ).modulate( ), ( data.size.y - st.heldOffset.y * 2 ) - pad * 2.0f );

    const float check_sz = total_bb.GetHeight( ) - ( st.heldOffset.y * 2 );
    const float pad = ImMax( 1.0f, ( float ) ( int ) ( check_sz / 6.0f ) );
    // window->DrawList->AddRectFilled(check_bb.Min+ImVec2(pad,pad), check_bb.Max-ImVec2(pad,pad), GetColorU32(ImGuiCol_CheckMark), style.FrameRounding);
    const ImRect check_mark_bb( total_bb.Min + ImVec2( pad, pad ) + st.heldOffset + ImVec2( 1, 1 ), total_bb.Max - ImVec2( pad, pad ) - st.heldOffset - ImVec2( 1, 1 ) );
    const ImVec2 points[ 3 ] = { ImVec2( check_mark_bb.Min.x, check_mark_bb.GetCenter( ).y ), ImVec2( check_mark_bb.Min.x + static_cast< int >( check_mark_bb.GetWidth( ) / 3 ), check_mark_bb.Max.y - 1 ), ImVec2( check_mark_bb.GetTR( ) + ImVec2( 0, 1 ) ) };
    window->DrawList->AddPolyline( points, 3, Color( st.mark ).modulate( ), 0, 1.0f );

    //window->DrawList->PopClipRect( );
}

Checkbox::~Checkbox( ) = default;