/*
 *   SPDX-FileCopyrightText: 2022 Suhaas Joshi <joshiesuhaas0@gmail.com>
 *
 *   SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

#pragma once

#include <QAbstractListModel>
#include <QString>
#include <QVariant>
#include <QVector>

class FlatpakPermission
{
public:
    FlatpakPermission(QString brief, QString description, QString icon);
    QString icon() const;
    QString brief() const;
    QString description() const;

private:
    QString m_brief;
    QString m_description;
    QString m_icon;
};

class FlatpakPermissionsModel : public QAbstractListModel
{
public:
    FlatpakPermissionsModel(QVector<FlatpakPermission> permissions);

    enum Roles {
        BriefRole = Qt::UserRole + 1,
        DescriptionRole,
        ListRole,
        IconRole,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    QVector<FlatpakPermission> m_permissions;
};
