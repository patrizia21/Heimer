// This file is part of Heimer.
// Copyright (C) 2020 Jussi Lind <jussi.lind@iki.fi>
//
// Heimer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Heimer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Heimer. If not, see <http://www.gnu.org/licenses/>.

#include "settings.hpp"
#include "constants.hpp"

#include <QSettings>
#include <QStandardPaths>
#include <QTimer>

#include <memory>

namespace {

const auto settingsGroupApplication = "Application";

const auto settingsGroupDefaults = "Defaults";

const auto settingsGroupEditing = "Editing";

const auto settingsGroupMainWindow = "MainWindow";

const auto recentImagePathKey = "recentImagePath";

const auto autosaveKey = "autosave";

const auto autoSnapStateKey = "autoSnap";

const auto edgeArrowModeKey = "edgeArrowMode";

const auto gridSizeKey = "gridSize";

const auto gridVisibleStateKey = "gridVisibleState";

const auto recentPathKey = "recentPath";

const auto reversedEdgeDirectionKey = "reversedEdgeDirection";

const auto selectNodeGroupByIntersectionKey = "selectNodeGroupByIntersection";

const auto windowFullScreenKey = "fullScreen";

const auto windowSizeKey = "size";

} // namespace

namespace Settings {

namespace V1 {

bool loadAutosave()
{
    QSettings settings;
    settings.beginGroup(settingsGroupEditing);
    const auto autosave = settings.value(autosaveKey, false).toBool();
    settings.endGroup();
    return autosave;
}

void saveAutosave(bool autosave)
{
    QSettings settings;
    settings.beginGroup(settingsGroupEditing);
    settings.setValue(autosaveKey, autosave);
    settings.endGroup();
}

Qt::CheckState loadAutoSnapState()
{
    QSettings settings;
    settings.beginGroup(settingsGroupMainWindow);
    const auto gridState = settings.value(autoSnapStateKey, Qt::Unchecked).toInt();
    settings.endGroup();
    return static_cast<Qt::CheckState>(gridState);
}

void saveAutoSnapState(int state)
{
    QSettings settings;
    settings.beginGroup(settingsGroupMainWindow);
    settings.setValue(autoSnapStateKey, state);
    settings.endGroup();
}

Edge::ArrowMode loadEdgeArrowMode(Edge::ArrowMode defaultMode)
{
    QSettings settings;
    settings.beginGroup(settingsGroupDefaults);
    const auto mode = static_cast<Edge::ArrowMode>(settings.value(edgeArrowModeKey, static_cast<int>(defaultMode)).toInt());
    settings.endGroup();
    return mode;
}

void saveEdgeArrowMode(Edge::ArrowMode mode)
{
    QSettings settings;
    settings.beginGroup(settingsGroupDefaults);
    settings.setValue(edgeArrowModeKey, static_cast<int>(mode));
    settings.endGroup();
}

bool loadReversedEdgeDirection(bool defaultDirection)
{
    QSettings settings;
    settings.beginGroup(settingsGroupDefaults);
    const auto direction = settings.value(reversedEdgeDirectionKey, defaultDirection).toBool();
    settings.endGroup();
    return direction;
}

void saveReversedEdgeDirection(bool reversed)
{
    QSettings settings;
    settings.beginGroup(settingsGroupDefaults);
    settings.setValue(reversedEdgeDirectionKey, reversed);
    settings.endGroup();
}

int loadGridSize()
{
    QSettings settings;
    settings.beginGroup(settingsGroupMainWindow);
    const auto gridSize = settings.value(gridSizeKey, 0).toInt();
    settings.endGroup();
    return gridSize;
}

void saveGridSize(int value)
{
    static std::unique_ptr<QTimer> gridSizeTimer;
    static int sGridSizeValue;
    sGridSizeValue = value;
    if (!gridSizeTimer) {
        gridSizeTimer = std::make_unique<QTimer>();
        gridSizeTimer->setSingleShot(true);
        gridSizeTimer->setInterval(Constants::View::TOO_QUICK_ACTION_DELAY_MS);
        gridSizeTimer->connect(gridSizeTimer.get(), &QTimer::timeout, [&]() {
            QSettings settings;
            settings.beginGroup(settingsGroupMainWindow);
            settings.setValue(gridSizeKey, sGridSizeValue);
            settings.endGroup();
        });
    }
    if (gridSizeTimer->isActive()) {
        gridSizeTimer->stop();
    }
    gridSizeTimer->start();
}

Qt::CheckState loadGridVisibleState()
{
    QSettings settings;
    settings.beginGroup(settingsGroupMainWindow);
    const auto gridState = settings.value(gridVisibleStateKey, Qt::Unchecked).toInt();
    settings.endGroup();
    return static_cast<Qt::CheckState>(gridState);
}

void saveGridVisibleState(int state)
{
    QSettings settings;
    settings.beginGroup(settingsGroupMainWindow);
    settings.setValue(gridVisibleStateKey, state);
    settings.endGroup();
}

QString loadRecentPath()
{
    QSettings settings;
    settings.beginGroup(settingsGroupApplication);
    const auto path = settings.value(recentPathKey, QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).toString();
    settings.endGroup();
    return path;
}

void saveRecentPath(QString path)
{
    QSettings settings;
    settings.beginGroup(settingsGroupApplication);
    settings.setValue(recentPathKey, path);
    settings.endGroup();
}

QString loadRecentImagePath()
{
    QSettings settings;
    settings.beginGroup(settingsGroupApplication);
    const QString path = settings.value(recentImagePathKey, QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).toString();
    settings.endGroup();
    return path;
}

void saveRecentImagePath(QString path)
{
    QSettings settings;
    settings.beginGroup(settingsGroupApplication);
    settings.setValue(recentImagePathKey, path);
    settings.endGroup();
}

QSize loadWindowSize(QSize defaultSize)
{
    QSettings settings;
    settings.beginGroup(settingsGroupMainWindow);
    const auto size = settings.value(windowSizeKey, defaultSize).toSize();
    settings.endGroup();
    return size;
}

void saveWindowSize(QSize size)
{
    QSettings settings;
    settings.beginGroup(settingsGroupMainWindow);
    settings.setValue(windowSizeKey, size);
    settings.endGroup();
}

bool loadFullScreen()
{
    QSettings settings;
    settings.beginGroup(settingsGroupMainWindow);
    const auto fullScreen = settings.value(windowFullScreenKey, false).toBool();
    settings.endGroup();
    return fullScreen;
}

void saveFullScreen(bool fullScreen)
{
    QSettings settings;
    settings.beginGroup(settingsGroupMainWindow);
    settings.setValue(windowFullScreenKey, fullScreen);
    settings.endGroup();
}

bool loadSelectNodeGroupByIntersection()
{
    QSettings settings;
    settings.beginGroup(settingsGroupDefaults);
    const auto fullScreen = settings.value(selectNodeGroupByIntersectionKey, false).toBool();
    settings.endGroup();
    return fullScreen;
}

void saveSelectNodeGroupByIntersection(bool selectNodeGroupByIntersection)
{
    QSettings settings;
    settings.beginGroup(settingsGroupDefaults);
    settings.setValue(selectNodeGroupByIntersectionKey, selectNodeGroupByIntersection);
    settings.endGroup();
}

} // namespace V1

namespace V2 {

bool getGenericBoolean(QString group, QString key, bool defaultValue)
{
    QSettings settings;
    settings.beginGroup(group);
    const auto val = settings.value(key, defaultValue).toBool();
    settings.endGroup();
    return val;
}

void setGenericBoolean(QString group, QString key, bool value)
{
    QSettings settings;
    settings.beginGroup(group);
    settings.setValue(key, value);
    settings.endGroup();
}

} // namespace V2

} // namespace Settings
