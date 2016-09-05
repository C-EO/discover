/***************************************************************************
 *   Copyright © 2012 Aleix Pol Gonzalez <aleixpol@blue-systems.com>       *
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

#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H

#include <QAbstractListModel>
#include <QQmlParserStatus>
#include "Category.h"

#include "discovercommon_export.h"

class DISCOVERCOMMON_EXPORT CategoryModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QVariantList categories READ categories WRITE setCategories NOTIFY categoryChanged)
    public:
        enum CategoryModelRole {
            CategoryRole = Qt::UserRole + 1
        };

        explicit CategoryModel(QObject* parent = nullptr);

        Category* categoryForRow(int row);

        QHash< int, QByteArray > roleNames() const override;

        Q_SCRIPTABLE static Category* findCategoryByName(const QString& name);
        static void blacklistPlugin(const QString& name);
        static QList<Category*> rootCategories();

        void setCategories(const QList<Category *> &categoryList);
        void setCategories(const QVariantList &categoryList);
        QVariantList categories() const;
        Q_SCRIPTABLE void resetCategories();

        QVariant data(const QModelIndex & index, int role) const override;
        int rowCount(const QModelIndex & parent) const override;

    Q_SIGNALS:
        void categoryChanged();

    private:
        void categoryDeleted(QObject* cat);

        QList<Category*> m_categories;
};

#endif // CATEGORYMODEL_H
