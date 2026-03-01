//
// Created by Kai Tears on 01/03/2026.
//

#ifndef SHADCN_IMGUI_CARD_HPP
#define SHADCN_IMGUI_CARD_HPP

#include "imgui.h"

#include <functional>
#include <string>
#include <unordered_map>

namespace shadcn
{
    enum class CardBackgroundStyle
    {
        Muted,
        Standard
    };

    struct Card
    {
        struct CardData
        {
            std::optional< CardBackgroundStyle > backgroundStyle = std::nullopt;
            ImVec2 padding = { 10, 10 };
            int rounding = 10;
        };

        Card( const std::string& name, const ImVec2& size, const std::optional< CardData >& data = std::nullopt );
        ~Card( );

        void end( );
    };
} // namespace shadcn

#endif // SHADCN_IMGUI_TOGGLE_HPP
