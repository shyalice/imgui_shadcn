//
// Created by Kai Tears on 27/02/2026.
//

#ifndef SHADCN_IMGUI_BUTTON_HPP
#define SHADCN_IMGUI_BUTTON_HPP

#include "imgui.h"

#include <functional>
#include <string>
#include <unordered_map>

namespace shadcn
{
    enum class ButtonStyle
    {
        Primary,
        Secondary,
        Destructive
    };

    struct Button
    {
        struct ButtonState
        {
            bool focused = false;

            ImVec2 heldOffset;
            float heldSizeMult;

            ImVec4 focus;
            ImVec4 background;
            ImVec4 border;
        };

        struct ButtonData
        {
            ImVec2 size = { 16, 16 };
            std::string fontVariant = "geist_500_18";
            int rounding = 10;
            ButtonStyle style = ButtonStyle::Primary;
            std::function< void( ) > onClick = nullptr;
        };

        static std::unordered_map< std::string, ButtonState > state;

        Button( const std::string& name, const ButtonData& data );
        ~Button( );
    };
} // namespace shadcn

#endif // SHADCN_IMGUI_BUTTON_HPP
