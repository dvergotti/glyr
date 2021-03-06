/***********************************************************
 * This file is part of glyr
 * + a commnadline tool and library to download various sort of music related metadata.
 * + Copyright (C) [2011]  [Christopher Pahl]
 * + Hosted at: https://github.com/sahib/glyr
 *
 * glyr is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * glyr is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with glyr. If not, see <http://www.gnu.org/licenses/>.
 **************************************************************/

#ifndef GLYRC_COLORPRINT_H
#define GLYRC_COLORPRINT_H



#include "../../lib/types.h"

typedef enum
{
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    DEFAULT
} termcolor;

/////////////////////////////

void enable_color (bool enable);

/////////////////////////////

void cprint (termcolor col,int verbosity, GlyrQuery * s, const char * fmt, ...);

#define cvprint(col,fmt, ...) cprint(col,-1,NULL,fmt,##__VA_ARGS__)

#endif /* end of include guard: GLYRC_COLORPRINT_H */
