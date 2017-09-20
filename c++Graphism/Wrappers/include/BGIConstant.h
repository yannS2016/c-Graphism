#ifndef BGICONSTANT_H_INCLUDED
#define BGICONSTANT_H_INCLUDED
#include <graphics.h>
#include <iostream>
#define DEBUG std::cout << __FILE__ << " " <<__FUNCTION__ << " line " << __LINE__ << " : "
typedef colors BGIColor;
typedef struct linesettingstype BGILineSettings;
typedef struct fillsettingstype BGIFillSettings;
typedef line_styles BGIPenStyle;
typedef fill_styles BGIBrush;
typedef font_names BGIFonts;
typedef horiz BGIHorAlig;
typedef vertical BGIVerAlign;
enum BGIDir { DIR_HORIZ,DIR_VERT};
enum BGIAlign { TEXT_LEFT = 0, TEXT_CENTER = 1, TEXT_RIGHT = 2,TEXT_BOTTOM = 3	,TEXT_TOP = 4};
enum BGIPaintType { CIRCLE, BAR, TEXT, LINE, ELLIPSE};
enum BGILayouts {LAY_OUT_VERT,LAY_OUT_HORIZ,NO_LAY_OUT};
#endif // BGICONSTANT_H_INCLUDED
