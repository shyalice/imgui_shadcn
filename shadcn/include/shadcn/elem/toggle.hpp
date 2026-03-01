//
// Created by Kai Tears on 01/03/2026.
//

#ifndef SHADCN_IMGUI_TOGGLE_HPP
#define SHADCN_IMGUI_TOGGLE_HPP

#include "imgui.h"

#include <functional>
#include <string>
#include <unordered_map>

namespace shadcn
{
    enum class ToggleStyle
    {
        Primary,
        Destructive
    };

    struct Toggle
    {
        struct ToggleState
        {
            bool focused = false;
            float offset = 0;
            float radius = 0;

            ImVec2 heldOffset;
            ImVec4 focus;

            ImVec4 background;
            ImVec4 border;
            ImVec4 pill;
        };

        struct ToggleData
        {
            ImVec2 size = { 26, 16 };
            ToggleStyle style = ToggleStyle::Primary;
            bool* forwardFocus = nullptr;
            std::function< void( ) > onClick;
        };

        static std::unordered_map< std::string, ToggleState > state;

        Toggle( const std::string& id, bool* v, const ToggleData& data );
        ~Toggle( );
    };
} // namespace shadcn

#endif // SHADCN_IMGUI_TOGGLE_HPP
