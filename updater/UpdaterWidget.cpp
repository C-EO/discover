/***************************************************************************
 *   Copyright © 2010 Jonathan Thomas <echidnaman@kubuntu.org>             *
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

#include "UpdaterWidget.h"

// Qt includes
#include <QtGui/QHeaderView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QSplitter>

// KDE includes
#include <KIcon>
#include <KLocale>
#include <KDebug>

// LibQApt includes
#include <LibQApt/Backend>

// Own includes
#include "../libmuon/DetailsWidget.h"
#include "../libmuon/PackageModel/PackageProxyModel.h"
#include "../libmuon/PackageModel/PackageModel.h"
#include "../libmuon/PackageModel/PackageView.h"
#include "../libmuon/PackageModel/PackageDelegate.h"

UpdaterWidget::UpdaterWidget(QWidget *parent)
    : KVBox(parent)
    , m_backend(0)
{
    m_model = new PackageModel(this);
    PackageDelegate *delegate = new PackageDelegate(this);

    m_proxyModel = new PackageProxyModel(this);

    KVBox *topVBox = new KVBox;

    QLabel *browserHeader = new QLabel(topVBox);
    browserHeader->setTextFormat(Qt::RichText);
    browserHeader->setText(i18n("<b>Update Packages</b>"));

    m_packageView = new PackageView(topVBox);
    m_packageView->setModel(m_proxyModel);
    m_packageView->setItemDelegate(delegate);
    connect(m_packageView, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(packageActivated(const QModelIndex &)));
    connect(m_packageView, SIGNAL(currentPackageChanged(const QModelIndex &)),
            this, SLOT(packageActivated(const QModelIndex &)));

    KVBox *bottomVBox = new KVBox;

    m_detailsWidget = new DetailsWidget(bottomVBox);

    QSplitter *splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(topVBox);
    splitter->addWidget(bottomVBox);

    setEnabled(false);
}

UpdaterWidget::~UpdaterWidget()
{
}

void UpdaterWidget::setBackend(QApt::Backend *backend)
{
    m_backend = backend;
    connect(m_backend, SIGNAL(packageChanged()), this, SLOT(refresh()));

    m_detailsWidget->setBackend(backend);
    m_backend->markPackagesForDistUpgrade();
    m_model->setPackages(m_backend->markedPackages());
    m_proxyModel->setSourceModel(m_model);
    m_proxyModel->setBackend(m_backend);
    m_packageView->setSortingEnabled(true);
    m_packageView->header()->setResizeMode(0, QHeaderView::Stretch);

    setEnabled(true);
}

void UpdaterWidget::refresh()
{
    m_detailsWidget->hide();
    m_model->clear();
    m_proxyModel->clear();
    m_proxyModel->setSourceModel(0);
    m_model->setPackages(m_backend->markedPackages());
    m_proxyModel->setSourceModel(m_model);
    m_packageView->header()->setResizeMode(0, QHeaderView::Stretch);
    m_packageView->updateView();
}

void UpdaterWidget::packageActivated(const QModelIndex &index)
{
    QApt::Package *package = m_proxyModel->packageAt(index);
    if (package == 0) {
        m_detailsWidget->hide();
        return;
    }

    m_detailsWidget->setPackage(package);
}

#include "UpdaterWidget.moc"
