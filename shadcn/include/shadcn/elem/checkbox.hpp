//
// Created by Kai Tears on 27/02/2026.
//

#ifndef SHADCN_IMGUI_CHECKBOX_HPP
#define SHADCN_IMGUI_CHECKBOX_HPP

#include "imgui.h"

#include <functional>
#include <string>
#include <unordered_map>

namespace shadcn
{
    struct Checkbox
    {
        struct CheckboxState
        {
            bool focused = false;

            ImVec2 heldOffset;
            ImVec4 focus;
            ImVec4 background;
            ImVec4 border;
            ImVec4 mark;
        };

        struct CheckboxData
        {
            ImVec2 size = { 16, 16 };
            bool isDestructive = false;
            std::function< void( ) > onClick;
        };

        static std::unordered_map< std::string, CheckboxState > state;

        Checkbox( const std::string& id, bool* v, const CheckboxData& data );
        ~Checkbox( );
    };
} // namespace shadcn

#endif // SHADCN_IMGUI_CHECKBOX_HPP
