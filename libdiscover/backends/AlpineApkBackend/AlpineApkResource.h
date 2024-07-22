/***************************************************************************
 *   Copyright © 2020 Alexey Min <alexey.min@gmail.com>                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of        *
 *   the License or (at your option) version 3 or any later version        *
 *   accepted by the membership of KDE e.V. (or its successor approved     *
 *   by the membership of KDE e.V.), which shall act as a proxy            *
 *   defined in Section 14 of version 3 of the license.                    *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#ifndef ALPINEAPKRESOURCE_H
#define ALPINEAPKRESOURCE_H

#include <resources/AbstractResource.h>
#include <QtApkPackage.h>
#include <AppStreamQt/component.h>

class AddonList;

class AlpineApkResource : public AbstractResource
{
    Q_OBJECT

public:
    explicit AlpineApkResource(const QtApk::Package &apkPkg,
                               AppStream::Component &component,
                               AbstractResource::Type typ,
                               AbstractResourcesBackend *parent);

    QList<PackageState> addonsInformation() override;
    QString section() override;
    QString origin() const override;
    QString longDescription() override;
    QString availableVersion() const override;
    QString installedVersion() const override;
    QJsonArray licenses() override;
    int size() override;
    QUrl homepage() override;
    QUrl helpURL() override;
    QUrl bugURL() override;
    QUrl donationURL() override;
    QStringList categories() override;
    AbstractResource::State state() override;
    QVariant icon() const override;
    QString comment() override;
    QString name() const override;
    QString packageName() const override;
    AbstractResource::Type type() const override { return m_type; }
    bool canExecute() const override;
    void invokeApplication() const override;
    void fetchChangelog() override;
    void fetchScreenshots() override;
    QString appstreamId() const override;
    QUrl url() const override;
    QString author() const override;
    QString sourceIcon() const override;
    QDate releaseDate() const override;

    void setState(State state);
    void setCategoryName(const QString &categoryName);
    void setOriginSource(const QString &originSource);
    void setSection(const QString &sectionName);
    void setAddons(const AddonList &addons);
    void setAddonInstalled(const QString &addon, bool installed);
    void setAvailableVersion(const QString &av);

private:
    bool hasAppStreamData() const;

public:
    AbstractResource::State m_state;
    const AbstractResource::Type m_type;
    QtApk::Package m_pkg;
    QString m_availableVersion;
    QString m_category;
    QString m_originSoruce;
    QString m_sectionName;
    QList<PackageState> m_addons;
    AppStream::Component m_appsC;
};

#endif // ALPINEAPKRESOURCE_H
