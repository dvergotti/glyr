#!/usr/bin/env python
# encoding: utf-8

"""#################################################################
# This file is part of glyr
# + a command-line tool and library to download various sort of musicrelated metadata.
# + Copyright (C) [2011-2016]  [Christopher Pahl]
# + Hosted at: https://github.com/sahib/glyr
#
# glyr is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# glyr is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with glyr. If not, see <http://www.gnu.org/licenses/>.
#################################################################
"""

import sys

if __name__ == '__main__':
    for source in sys.argv[1:]:
        with open(source, 'r') as handle:
            content = __doc__ + handle.read()

        with open(source, 'w') as handle:
            handle.write(content)

    print(sys.argv)
