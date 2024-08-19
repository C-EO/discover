/*
 *   SPDX-FileCopyrightText: 2017 Aleix Pol Gonzalez <aleixpol@blue-systems.com>
 *   SPDX-FileCopyrightText: 2017 Jan Grulich <jgrulich@redhat.com>
 *
 *   SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

#pragma once

#include <QNetworkAccessManager>
#include <QQmlNetworkAccessManagerFactory>

#include "discovercommon_export.h"

class DISCOVERCOMMON_EXPORT CachedNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit CachedNetworkAccessManager(const QString &path, QObject *parent = nullptr);

    QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData = nullptr) override;
};
