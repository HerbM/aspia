//
// Aspia Project
// Copyright (C) 2019 Dmitry Chapyshev <dmitry@aspia.ru>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef HOST__SCREEN_CONTROLS_H
#define HOST__SCREEN_CONTROLS_H

#include "desktop/desktop_geometry.h"

namespace host {

class ScreenControls
{
public:
    virtual ~ScreenControls() = default;

    virtual void setScreenResolution(const desktop::Size& resolution) = 0;
    virtual void setEffectsState(bool enable) = 0;
    virtual void setWallpaperState(bool enable) = 0;
};

} // namespace host

#endif // HOST__SCREEN_CONTROLS_H
