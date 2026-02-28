//
// Created by Kai Tears on 27/02/2026.
//

#include "elem/elem.hpp"

#include "imgui.h"
#include "imgui_internal.h"

void shadcn::elem::unfocusWhenInactive( const ImVec2& mouse_pos, const ImRect& rect, DataSkeleton* data )
{
    if ( !data || !data->focused )
        return;

    if ( ImGui::IsMouseClicked( 0 ) && !rect.Contains( mouse_pos ) )
        data->focused = false;
}

bool inactive;

void shadcn::elem::pushInactiveFlag( )
{
    inactive = true;
}

bool shadcn::elem::isInactive( )
{
    return inactive;
}

void shadcn::elem::popInactiveFlag( )
{
    inactive = false;
}