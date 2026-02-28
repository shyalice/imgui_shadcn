//
// Created by Kai Tears on 27/02/2026.
//

#ifndef SHADCN_IMGUI_COLOR_HPP
#define SHADCN_IMGUI_COLOR_HPP

#include "imgui.h"

namespace shadcn
{
    struct Color
    {
        ImVec4 value;

        constexpr Color( ) {}
        constexpr Color( float r, float g, float b, float a = 1.0f )
            : value( r, g, b, a )
        {
        }
        constexpr Color( const ImVec4& col )
            : value( col )
        {
        }
        constexpr Color( const ImColor& col )
            : value( col.Value )
        {
        }
        constexpr Color( int r, int g, int b, int a = 255 )
            : value( ( float ) r * ( 1.0f / 255.0f ), ( float ) g * ( 1.0f / 255.0f ), ( float ) b * ( 1.0f / 255.0f ), ( float ) a * ( 1.0f / 255.0f ) )
        {
        }
        constexpr Color( ImU32 rgba )
            : value( ( float ) ( ( rgba >> IM_COL32_R_SHIFT ) & 0xFF ) * ( 1.0f / 255.0f ), ( float ) ( ( rgba >> IM_COL32_G_SHIFT ) & 0xFF ) * ( 1.0f / 255.0f ), ( float ) ( ( rgba >> IM_COL32_B_SHIFT ) & 0xFF ) * ( 1.0f / 255.0f ), ( float ) ( ( rgba >> IM_COL32_A_SHIFT ) & 0xFF ) * ( 1.0f / 255.0f ) )
        {
        }

        ImColor modulate( float alpha = ImGui::GetStyle( ).Alpha ) const
        {
            return { value.x, value.y, value.z, value.w * alpha };
        }

        ImColor u32( ) const
        {
            return value;
        }
    };
} // namespace shadcn

#endif // SHADCN_IMGUI_COLOR_HPP
