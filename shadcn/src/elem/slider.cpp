//
// Created by Kai Tears on 01/03/2026.
//

#include "elem/slider.hpp"

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

using shadcn::Slider;

std::unordered_map< std::string, Slider::SliderState > Slider::state;

bool Slider::exScalar( const SliderData& data, const std::string& id, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags )
{
    ImGuiWindow* window = GetCurrentWindow( );
    if ( window->SkipItems )
        return false;

    auto const inactive = elem::isInactive( );

    if ( inactive )
        BeginDisabled( );

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID imgui_id = window->GetID( id.c_str( ) );

    const ImRect total_bb( window->DC.CursorPos, window->DC.CursorPos + data.size );

    ItemSize( total_bb, 0 );
    if ( !ItemAdd( total_bb, imgui_id ) )
    {
        if ( inactive )
            EndDisabled( );
        return false;
    }

    if ( format == NULL )
        format = DataTypeGetInfo( data_type )->PrintFmt;

    const ImRect frame_bb = total_bb;

    const bool hovered = ItemHoverable( total_bb, imgui_id, g.LastItemData.ItemFlags );
    const bool clicked = hovered && IsMouseClicked( 0, ImGuiInputFlags_None, imgui_id );
    const bool make_active = ( clicked || g.NavActivateId == imgui_id );

    auto& st = state[ id ];

    if ( make_active )
    {
        if ( clicked )
            SetKeyOwner( ImGuiKey_MouseLeft, imgui_id );

        memcpy( &g.ActiveIdValueOnActivation, p_data, DataTypeGetInfo( data_type )->Size );

        SetActiveID( imgui_id, window );
        SetFocusID( imgui_id, window );
        FocusWindow( window );
        g.ActiveIdUsingNavDirMask |= ( 1 << ImGuiDir_Left ) | ( 1 << ImGuiDir_Right );
    }

    ImRect grab_bb;
    const bool value_changed = SliderBehavior( frame_bb, imgui_id, data_type, p_data, p_min, p_max, format, flags, &grab_bb );
    if ( value_changed )
        MarkItemEdited( imgui_id );

    if ( inactive )
        EndDisabled( );

    st.grabHovered = grab_bb.Contains( g.IO.MousePos ) || value_changed || g.ActiveId == imgui_id;

    st.hover = ImLerp( st.hover, ( st.grabHovered && !inactive ) ? colorPalette[ "ring" ].modulate( 0.5f * style.Alpha ).Value : colorPalette[ "ring" ].modulate( 0 ).Value, g.IO.DeltaTime * 20.f );
    st.offset = ImLerp( st.offset, grab_bb.GetCenter( ).x - frame_bb.Min.x, g.IO.DeltaTime * 20.f );

    st.heldOffset = shadcn::g->styles->global.useAdvancedAnimations ? ImLerp( st.heldOffset, ( ( frame_bb.Contains( g.IO.MousePos ) && IsMouseDown( 0 ) || value_changed || g.ActiveId == imgui_id ) && !inactive ) ? ImVec2( 0, 2 ) : ImVec2( 0, 0 ), g.IO.DeltaTime * 20.f ) : ImVec2( 0, 0 );

    window->DrawList->AddRectFilled( frame_bb.Min + ImVec2( 0, static_cast< int >( data.size.y / 3.5f ) ), frame_bb.Max - ImVec2( 0, data.size.y / 3.5f ), colorPalette[ "muted" ].modulate( ), 666 );

    if ( grab_bb.Max.x > grab_bb.Min.x )
    {
        if ( data.style == SliderStyle::Standard || data.style == SliderStyle::Simple )
        {
            window->DrawList->AddRectFilled( frame_bb.Min + ImVec2( 0, data.size.y / 3 ), ImVec2( frame_bb.Min.x + st.offset, frame_bb.Max.y ) - ImVec2( 0, data.size.y / 3 ), inactive ? colorPalette[ "primary" ].modulate( 0.7f * style.Alpha ) : colorPalette[ "primary" ].modulate( ), 666 );

            if ( data.style != SliderStyle::Simple )
            {
                window->DrawList->AddCircleFilled( { frame_bb.Min.x + st.offset, frame_bb.GetCenter( ).y }, data.size.y / 1.8f, Color( st.hover ).modulate( ), 66 );

                window->DrawList->AddCircleFilled( { frame_bb.Min.x + st.offset, frame_bb.GetCenter( ).y }, static_cast< int >( data.size.y / 2.5f ), colorPalette[ "muted" ].modulate( ), 66 );
                window->DrawList->AddCircleFilled( { frame_bb.Min.x + st.offset, frame_bb.GetCenter( ).y }, static_cast< int >( data.size.y / 2.5f ), inactive ? colorPalette[ "primary" ].modulate( 0.7f * style.Alpha ) : colorPalette[ "primary" ].modulate( ), 66 );

                window->DrawList->AddCircle( { frame_bb.Min.x + st.offset, frame_bb.GetCenter( ).y }, static_cast< int >( data.size.y / 2.5f ), colorPalette[ "ring" ].modulate( ), 66 );
            }
        } else
        {
            window->DrawList->AddRectFilled( frame_bb.Min + ImVec2( 0, st.heldOffset.y ), ImVec2( frame_bb.Min.x + st.offset, frame_bb.Max.y ) - ImVec2( 0, st.heldOffset.y ), inactive ? colorPalette[ "primary" ].modulate( 0.7f * style.Alpha ) : colorPalette[ "primary" ].modulate( ), 666 );
        }
    }

    return value_changed;
}

Slider::Slider( const std::string& id, int* v, int v_min, int v_max, const SliderData& data )
{
    exScalar( data, id, ImGuiDataType_S32, v, &v_min, &v_max, nullptr, 0 );
}

Slider::Slider( const std::string& id, float* v, float v_min, float v_max, const SliderData& data )
{
    exScalar( data, id, ImGuiDataType_Float, v, &v_min, &v_max, nullptr, 0 );
}

Slider::~Slider( ) = default;