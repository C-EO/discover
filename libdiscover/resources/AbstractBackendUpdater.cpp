/*
 *   SPDX-FileCopyrightText: 2012 Aleix Pol Gonzalez <aleixpol@blue-systems.com>
 *
 *   SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

#include "AbstractBackendUpdater.h"
#include "AbstractResource.h"

AbstractBackendUpdater::AbstractBackendUpdater(QObject *parent)
    : QObject(parent)
{
}

void AbstractBackendUpdater::cancel()
{
    Q_ASSERT(isCancelable() && "only call cancel when cancelable");
    Q_ASSERT(false && "if it can be canceled, then ::cancel() must be implemented");
}

void AbstractBackendUpdater::fetchChangelog() const
{
    const auto toUpd = toUpdate();
    for (auto res : toUpd) {
        res->fetchChangelog();
    }
}

void AbstractBackendUpdater::setNeedsReboot(bool enabled)
{
    if (m_needsReboot == enabled) {
        return;
    }
    m_needsReboot = enabled;
    Q_EMIT needsRebootChanged();
}

void AbstractBackendUpdater::enableReadyToReboot()
{
    m_readyToReboot = true;
}

bool AbstractBackendUpdater::needsReboot() const
{
    return m_needsReboot;
}

bool AbstractBackendUpdater::isReadyToReboot() const
{
    return m_readyToReboot;
}

void AbstractBackendUpdater::setOfflineUpdates(bool useOfflineUpdates)
{
    Q_UNUSED(useOfflineUpdates);
}

void AbstractBackendUpdater::setErrorMessage(const QString &errorMessage)
{
    if (errorMessage == m_errorMessage) {
        return;
    }
    m_errorMessage = errorMessage;
    Q_EMIT errorMessageChanged();
}
