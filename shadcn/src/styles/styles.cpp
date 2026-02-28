//
// Created by Kai Tears on 27/02/2026.
//

#include "styles/styles.hpp"

#include "color/color.hpp"

using shadcn::Color;
using shadcn::CStyles;

CStyles::~CStyles( ) = default;

CStyles::CStyles( )
{
    setDarkNeutral( );
}

std::unordered_map< std::string, Color > shadcn::colorPalette;

void CStyles::setDarkNeutral( )
{
    colorPalette[ "background" ] = ImColor( 10, 10, 10, 255 );    // #0A0A0A
    colorPalette[ "foreground" ] = ImColor( 250, 250, 250, 255 ); // #FAFAFA

    colorPalette[ "card" ] = ImColor( 23, 23, 23, 255 );               // #171717
    colorPalette[ "card_foreground" ] = ImColor( 250, 250, 250, 255 ); // #FAFAFA

    colorPalette[ "popover" ] = ImColor( 23, 23, 23, 255 );               // #171717
    colorPalette[ "popover_foreground" ] = ImColor( 250, 250, 250, 255 ); // #FAFAFA

    colorPalette[ "primary" ] = ImColor( 212, 212, 212, 255 );         // #D4D4D4
    colorPalette[ "primary_foreground" ] = ImColor( 23, 23, 23, 255 ); // #171717

    colorPalette[ "secondary" ] = ImColor( 38, 38, 38, 255 );               // #262626
    colorPalette[ "secondary_foreground" ] = ImColor( 250, 250, 250, 255 ); // #FAFAFA

    colorPalette[ "muted" ] = ImColor( 38, 38, 38, 255 );               // #262626
    colorPalette[ "muted_foreground" ] = ImColor( 161, 161, 161, 255 ); // #A1A1A1

    colorPalette[ "accent" ] = ImColor( 64, 64, 64, 255 );               // #404040
    colorPalette[ "accent_foreground" ] = ImColor( 250, 250, 250, 255 ); // #FAFAFA

    colorPalette[ "destructive" ] = ImColor( 255, 100, 103, 255 ); // #FF6467
    colorPalette[ "ring" ] = ImColor( 115, 115, 115, 255 );        // #737373

    // Important: in CSS these have alpha (10% / 15%)
    colorPalette[ "border" ] = ImColor( 255, 255, 255, 26 ); // white @ 10%
    colorPalette[ "input" ] = ImColor( 255, 255, 255, 38 );  // white @ 15%

    // Sidebar
    colorPalette[ "sidebar" ] = ImColor( 23, 23, 23, 255 );               // #171717
    colorPalette[ "sidebar_foreground" ] = ImColor( 250, 250, 250, 255 ); // #FAFAFA
    colorPalette[ "sidebar_primary" ] = ImColor( 20, 71, 230, 255 );      // #1447E6
    colorPalette[ "sidebar_primary_foreground" ] = ImColor( 250, 250, 250, 255 );
    colorPalette[ "sidebar_accent" ] = ImColor( 38, 38, 38, 255 ); // #262626
    colorPalette[ "sidebar_accent_foreground" ] = ImColor( 250, 250, 250, 255 );
    colorPalette[ "sidebar_border" ] = ImColor( 255, 255, 255, 26 ); // white @ 10%
    colorPalette[ "sidebar_ring" ] = ImColor( 115, 115, 115, 255 );  // #737373

    // Charts
    colorPalette[ "chart_1" ] = ImColor( 142, 197, 255, 255 ); // #8EC5FF
    colorPalette[ "chart_2" ] = ImColor( 43, 127, 255, 255 );  // #2B7FFF
    colorPalette[ "chart_3" ] = ImColor( 21, 93, 252, 255 );   // #155DFC
    colorPalette[ "chart_4" ] = ImColor( 20, 71, 230, 255 );   // #1447E6
    colorPalette[ "chart_5" ] = ImColor( 25, 60, 184, 255 );   // #193CB8

    // Text semantics
    colorPalette[ "text" ] = colorPalette[ "foreground" ];              // #FAFAFA
    colorPalette[ "text_muted" ] = colorPalette[ "muted_foreground" ];  // #A1A1A1
    colorPalette[ "text_destructive" ] = colorPalette[ "destructive" ]; // #FF6467

    colorPalette[ "text_on_primary" ] = colorPalette[ "primary_foreground" ];     // #171717
    colorPalette[ "text_on_secondary" ] = colorPalette[ "secondary_foreground" ]; // #FAFAFA
    colorPalette[ "text_on_accent" ] = colorPalette[ "accent_foreground" ];       // #FAFAFA
    colorPalette[ "text_on_card" ] = colorPalette[ "card_foreground" ];           // #FAFAFA
    colorPalette[ "text_on_popover" ] = colorPalette[ "popover_foreground" ];     // #FAFAFA
    colorPalette[ "text_on_sidebar" ] = colorPalette[ "sidebar_foreground" ];     // #FAFAFA
    colorPalette[ "text_on_sidebar_primary" ] = colorPalette[ "sidebar_primary_foreground" ];

    colorPalette[ "ring" ] = ImColor( 115, 115, 115, 255 );             // #737373
    colorPalette[ "ring_destructive" ] = ImColor( 255, 100, 103 ); // #FF6467
}
