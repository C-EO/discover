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

#ifndef APPLICATIONBACKEND_H
#define APPLICATIONBACKEND_H

#include <QtCore/QList>
#include <QtCore/QObject>

#include <LibQApt/Globals>

namespace QApt {
    class Backend;
}

class Application;

enum TransactionState {
    InvalidState = 0,
    QueuedState = 1,
	RunningState = 2
};

struct Transaction {
    Application *application;
    int action;
	TransactionState state;
};

class ApplicationBackend : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationBackend(QObject *parent);
    ~ApplicationBackend();

    QList<Application *> applicationList() const;
    QPair<QApt::WorkerEvent, Application *> workerState() const;
    Transaction currentTransaction() const;
    int maxPopconScore() const;

    void addTransaction(Transaction transaction);
    void runNextTransaction();

private:
    QApt::Backend *m_backend;

    QList<Application *> m_appList;
    QList<Transaction> m_queue;
    QPair<QApt::WorkerEvent, Application *> m_workerState;
    int m_maxPopconScore;

public Q_SLOTS:
    void setBackend(QApt::Backend *backend);
    void reload();

private Q_SLOTS:
    void init();
    void workerEvent(QApt::WorkerEvent event);
    void errorOccurred();
    void updateDownloadProgress(int percentage);
    void updateCommitProgress(const QString &text, int percentage);

Q_SIGNALS:
    void reloaded();
    void workerEvent(QApt::WorkerEvent event, Application *app);
    void progress(Application *app, int progress);
};

#endif
