//
// Created by Kai Tears on 27/02/2026.
//

#ifndef SHADCN_IMGUI_ELEM_HPP
#define SHADCN_IMGUI_ELEM_HPP

#include "imgui.h"
#include "imgui_internal.h"

namespace shadcn::elem
{
    struct DataSkeleton
    {
        bool focused = false;
    };

    extern void unfocusWhenInactive( const ImVec2& mouse_pos, const ImRect& rect, DataSkeleton* data );

    extern void pushInactiveFlag( );
    extern bool isInactive( );
    extern void popInactiveFlag( );
} // namespace shadcn::elem

#endif // SHADCN_IMGUI_ELEM_HPP
