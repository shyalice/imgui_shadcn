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
    struct CardData
    {
        int rounding = 10;
        bool useBackground = true;
    };

    struct Card
    {
        Card( const std::string& name, const ImVec2& size, const std::optional< CardData >& data = std::nullopt );
        ~Card( );

        void end( );
    };
} // namespace shadcn

#endif // SHADCN_IMGUI_TOGGLE_HPP
