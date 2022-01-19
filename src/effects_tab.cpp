// This file is part of Heimer.
// Copyright (C) 2022 Jussi Lind <jussi.lind@iki.fi>
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

#include "effects_tab.hpp"
#include "settings_proxy.hpp"
#include "widget_factory.hpp"

#include <QGroupBox>
#include <QVBoxLayout>

EffectsTab::EffectsTab(QWidget * parent)
  : QWidget(parent)
{
    initWidgets();
}

void EffectsTab::apply()
{
}

void EffectsTab::initWidgets()
{
    const auto mainLayout = new QVBoxLayout;
    const auto shadowsGroup = WidgetFactory::buildGroupBoxWithVLayout(tr("Shadows"), *mainLayout);

    setLayout(mainLayout);

    setActiveSettings();
}

void EffectsTab::setActiveSettings()
{
}
