/*
 *   SPDX-FileCopyrightText: 2013 Lukas Appelhans <l.appelhans@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */
#pragma once

#include <BackendNotifierModule.h>

class DummyNotifier : public BackendNotifierModule
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DISCOVER_NOTIFIER_IID)
    Q_INTERFACES(BackendNotifierModule)
public:
    explicit DummyNotifier(QObject *parent = nullptr);
    ~DummyNotifier() override;

    void recheckSystemUpdateNeeded() override;
    bool hasSecurityUpdates() override
    {
        return false;
    }

    bool hasUpdates() override
    {
        return false;
    }

    bool needsReboot() const override
    {
        return false;
    }
};
