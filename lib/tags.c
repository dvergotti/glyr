/***********************************************************
* This file is part of glyr
* + a commnadline tool and library to download various sort of musicrelated metadata.
* + Copyright (C) [2011]  [Christopher Pahl]
* + Hosted at: https://github.com/sahib/glyr
*
* glyr is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* glyr is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with glyr. If not, see <http://www.gnu.org/licenses/>.
**************************************************************/

#include "core.h"
#include "stringlib.h"

/*----------------------------------------------------------------*/

bool vdt_tags(GlyQuery * settings)
{
    if(settings && settings->artist &&
	 !(settings && settings->artist && /* Impossible to get tags of a title without album */
	   settings->album == NULL &&
	   settings->title != NULL
	   )
	  )
    {
		return true;
    }
    return false;
}

/*----------------------------------------------------------------*/

static GList * factory(GlyQuery * s, GList * list) {return NULL;}

/* PlugStruct */
MetaDataFetcher glyrFetcher_tags = {
	.name = "Tag Fetcher",
	.type = GET_TAGS,
	.validate = vdt_tags,
	/* CTor | DTor */
	.init    = NULL,
	.destroy = NULL,
	.finalize = factory
};
