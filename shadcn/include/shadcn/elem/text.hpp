//
// Created by Kai Tears on 28/02/2026.
//

#ifndef SHADCN_IMGUI_TEXT_HPP
#define SHADCN_IMGUI_TEXT_HPP

#include "imgui.h"

#include <functional>
#include <string>
#include <unordered_map>

namespace shadcn
{
    struct Text
    {
        struct TextData
        {
            std::string fontVariant = "geist_500_14";
            std::string color = "text";
            std::function< void( ) > onClick = nullptr;
        };

        Text( const std::string& value, const TextData& data );
        ~Text( );
    };
} // namespace shadcn

#endif // SHADCN_IMGUI_TEXT_HPP
