//
// Created by Kai Tears on 28/02/2026.
//

#ifndef SHADCN_IMGUI_INPUT_TEXT_HPP
#define SHADCN_IMGUI_INPUT_TEXT_HPP

#include "imgui.h"

#include <functional>
#include <string>
#include <unordered_map>

namespace shadcn
{
    struct InputText
    {
        struct InputTextState
        {
            bool focused = false;

            ImVec2 heldOffset;
            float heldSizeMult;

            ImVec4 focus;
            ImVec4 background;
            ImVec4 border;
        };

        struct InputTextData
        {
            ImVec2 size = { 100, 34 };
            ImVec2 pad = { 10, 10 };
            std::string fontVariant = "geist_500_14";
            int rounding = 10;
            ImGuiInputTextFlags imFlags = 0;
            bool isDestructive = false;
            std::function< void( ) > onEnter;
        };

        static bool inputEx( const char* label, const char* hint, char* buf, int buf_size, const ImVec2& size_arg, ImGuiInputTextFlags flags, const InputTextData& data, ImGuiInputTextCallback callback, void* callback_user_data );

        static std::unordered_map< std::string, InputTextState > state;

        InputText( const std::string& label, const std::string& hint, char* buf, size_t buf_size, const InputTextData& data );
        ~InputText( );
    };
} // namespace shadcn

#endif // SHADCN_IMGUI_INPUT_TEXT_HPP
